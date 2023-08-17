#define WIE_INCLUDE_HASH
#define WIE_INCLUDE_WIEEXT

#include "..\Include\Wintexports.h"

#pragma comment(lib, "WinAPI.lib")

#pragma comment(lib, "ntdll.lib")

#pragma comment(lib, "WIE_CRT.lib")

#define _NO_CRT_STDIO_INLINE
#include <stdio.h>

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
    if (!RtlDosPathNameToNtPathName_U(Path, ObjectName, NULL, RelativeName))
    {
        WIE_SetLastStatus(STATUS_OBJECT_PATH_INVALID);
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
        WIE_SetLastStatus(Status);
        return FALSE;
    }

    FindData->Buffer = VirtualAlloc(NULL, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!FindData->Buffer)
    {
        NtClose(DirectoryHandle);
        WIE_SetLastStatus(STATUS_NO_MEMORY);
        return FALSE;
    }

    FindData->Length = 0x100;
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
    NtClose(FindData->DirectoryHandle);
    VirtualFree(FindData->Buffer, 0, MEM_RELEASE);
    RtlReleaseRelativeName(&FindData->RelativePath);
}

int wmain()
{
    FILE_FIND FindData;
    BOOL b;
    PFILE_FULL_DIR_INFORMATION pData;

    b = File_FindInitialize(&FindData, L"..\\x64", NULL, FileFullDirectoryInformation);

    if (!b)
    {
        return 1;
    }

    do
    {
        b = File_Find(&FindData);
        if (!b || (b && !FindData.HasData))
        {
            break;
        }

        pData = FindData.Buffer;
        do
        {
            WCHAR szFileName[MAX_PATH];
            RtlCopyMemory(szFileName, pData->FileName, pData->FileNameLength);
            szFileName[pData->FileNameLength / sizeof(WCHAR)] = UNICODE_NULL;
            
            DbgPrint("%ws", szFileName);

            if (!pData->NextEntryOffset)
            {
                break;
            }

            pData = Add2Ptr(pData, pData->NextEntryOffset);
        } while (TRUE);

    } while (TRUE);

    File_FindUninitialize(&FindData);

    return 0;
}
