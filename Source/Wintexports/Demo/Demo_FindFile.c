﻿#include "Demo.h"

_Success_(return != FALSE)
BOOL NTAPI NT_InitializePathObjectEx(
    _In_z_ PCWSTR Path,
    _In_opt_ HANDLE RootDirectory,
    _In_ ULONG Attributes,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ POBJECT_ATTRIBUTES Object,
    _Out_ PUNICODE_STRING ObjectName,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName)
{
    NTSTATUS Status;

    Status = RtlDosPathNameToNtPathName_U_WithStatus(Path, ObjectName, NULL, RelativeName);
    if (!NT_SUCCESS(Status))
    {
        WIE_SetLastStatus(Status);
        return FALSE;
    }

    InitializeObjectAttributes(Object, ObjectName, Attributes, RootDirectory, SecurityDescriptor);

    return TRUE;
}

_Success_(return != FALSE)
BOOL NTAPI NT_InitializePathObject(_In_z_ PCWSTR Path, _In_ BOOL InheritHandle, _Out_ POBJECT_ATTRIBUTES Object, _Out_ PUNICODE_STRING ObjectName, _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName)
{
    ULONG Attributes = OBJ_CASE_INSENSITIVE;

    if (InheritHandle)
    {
        Attributes |= OBJ_INHERIT;
    }

    return NT_InitializePathObjectEx(Path, NULL, Attributes, NULL, Object, ObjectName, RelativeName);
}

typedef struct _FILE_FIND
{
    /* Initialize parameters */
    BOOL RestartScan;
    PCWSTR Path;
    PUNICODE_STRING SearchFilter;
    FILE_INFORMATION_CLASS FileInformationClass;

    /* Runtime data */
    HANDLE DirectoryHandle;
    UNICODE_STRING NtPath;
    RTL_RELATIVE_NAME_U RelativePath;

    /* Output data */
    BOOL HasData;
    DECLSPEC_ALIGN(4) PVOID Buffer;
    ULONG Length;
} FILE_FIND, *PFILE_FIND;

#define FILE_FIND_BUFFER_SIZE 0x1000

BOOL File_FindInitialize(
    _Out_ PFILE_FIND FindData,
    _In_z_ PCWSTR Path,
    _In_opt_ PUNICODE_STRING SearchFilter,
    _In_ FILE_INFORMATION_CLASS FileInformationClass)
{
    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    HANDLE DirectoryHandle;

    FindData->RestartScan = TRUE;
    FindData->Path = Path;
    FindData->SearchFilter = SearchFilter;
    FindData->FileInformationClass = FileInformationClass;

    if (!NT_InitializePathObject(FindData->Path, FALSE, &ObjectAttributes, &FindData->NtPath, &FindData->RelativePath))
    {
        return FALSE;
    }

    Status = NtOpenFile(&DirectoryHandle,
                        FILE_LIST_DIRECTORY | SYNCHRONIZE,
                        &ObjectAttributes,
                        &IoStatusBlock,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT);
    if (!NT_SUCCESS(Status))
    {
        RtlReleaseRelativeName(&FindData->RelativePath);
        WIE_SetLastStatus(Status);
        return FALSE;
    }

    FindData->Buffer = RtlAllocateHeap(CURRENT_PROCESS_HEAP, 0, FILE_FIND_BUFFER_SIZE);
    if (!FindData->Buffer)
    {
        NtClose(DirectoryHandle);
        RtlReleaseRelativeName(&FindData->RelativePath);
        WIE_SetLastStatus(STATUS_NO_MEMORY);
        return FALSE;
    }

    FindData->Length = FILE_FIND_BUFFER_SIZE;
    FindData->DirectoryHandle = DirectoryHandle;
    return TRUE;
}

BOOL File_Find(_Inout_ PFILE_FIND FindData)
{
    NTSTATUS Status;
    IO_STATUS_BLOCK IoStatusBlock;

    Status = NtQueryDirectoryFile(FindData->DirectoryHandle,
                                  NULL,
                                  NULL,
                                  NULL,
                                  &IoStatusBlock,
                                  FindData->Buffer,
                                  FindData->Length,
                                  FindData->FileInformationClass,
                                  FALSE,
                                  FindData->SearchFilter,
                                  FindData->RestartScan);
    if (Status == STATUS_NO_MORE_FILES)
    {
        FindData->HasData = FALSE;
        return TRUE;
    } else if (Status == STATUS_BUFFER_OVERFLOW || NT_SUCCESS(Status))
    {
        FindData->RestartScan = FALSE;
        FindData->HasData = TRUE;
        return TRUE;
    } else
    {
        WIE_SetLastStatus(Status);
        return FALSE;
    }
}

VOID File_FindUninitialize(_In_ PFILE_FIND FindData)
{
    RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, FindData->Buffer);
    NtClose(FindData->DirectoryHandle);
    RtlReleaseRelativeName(&FindData->RelativePath);
}

BOOL Demo_FindFile()
{
    FILE_FIND FindData;
    BOOL bRet;
    PFILE_FULL_DIR_INFORMATION pData;
    UNICODE_STRING FileName;

    /* Initialize the enumeration */
    bRet = File_FindInitialize(&FindData, L".", NULL, FileFullDirectoryInformation);
    if (!bRet)
    {
        DbgPrint("File_FindInitialize failed with 0x%08lX\n", WIE_GetLastStatus());
        return FALSE;
    }

    /* Enumerate files */
    while (TRUE)
    {
        /* Break if an error occurred or no more data */
        bRet = File_Find(&FindData);
        if (!bRet || (bRet && !FindData.HasData))
        {
            break;
        }

        /* Read data from the return buffer */
        pData = (PFILE_FULL_DIR_INFORMATION)FindData.Buffer;
        while (TRUE)
        {
            /* Print file name */
            FileName.Buffer = pData->FileName;
            FileName.MaximumLength = FileName.Length = pData->FileNameLength;
            DbgPrint("Found file: %wZ\n", &FileName);

            /* Go to the next entry */
            if (!pData->NextEntryOffset)
            {
                break;
            }
            pData = (PFILE_FULL_DIR_INFORMATION)Add2Ptr(pData, pData->NextEntryOffset);
        };
    };
    if (!bRet)
    {
        DbgPrint("File_Find failed with 0x%08lX\n", WIE_GetLastStatus());
    }

    /* Release resources used by the enumeration */
    File_FindUninitialize(&FindData);

    return bRet;
}
