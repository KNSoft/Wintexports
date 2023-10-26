#include "Demo.h"

#include <winioctl.h>

HANDLE IO_OpenDevice(_In_ PUNICODE_STRING DeviceName, _In_ ACCESS_MASK DesiredAccess)
{
    OBJECT_ATTRIBUTES ObjectAttribute;
    NTSTATUS Status;
    HANDLE DeviceHandle;
    IO_STATUS_BLOCK IoStatusBlock;

    InitializeObjectAttributes(&ObjectAttribute, DeviceName, OBJ_CASE_INSENSITIVE, NULL, NULL);
    Status = NtOpenFile(&DeviceHandle,
                        DesiredAccess,
                        &ObjectAttribute,
                        &IoStatusBlock,
                        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                        FILE_NON_DIRECTORY_FILE);
    if (!NT_SUCCESS(Status))
    {
        WIE_SetLastStatus(Status);
        return NULL;
    }

    return DeviceHandle;
}

PVOID IO_QueryStorageProperty(
    _In_ HANDLE DeviceHandle,
    _In_ PSTORAGE_PROPERTY_QUERY Query,
    _In_ ULONG QuerySize)
{
    NTSTATUS Status;
    IO_STATUS_BLOCK IoStatusBlock;
    STORAGE_DESCRIPTOR_HEADER sdh;
    PVOID Buffer;

    /* Query header for size */
    Status = NtDeviceIoControlFile(DeviceHandle,
                                   NULL,
                                   NULL,
                                   NULL,
                                   &IoStatusBlock,
                                   IOCTL_STORAGE_QUERY_PROPERTY,
                                   Query,
                                   QuerySize,
                                   &sdh,
                                   sizeof(sdh));
    if (!NT_SUCCESS(Status))
    {
        goto _fail_0;
    }

    /* Allocate buffer to receive data */
    Buffer = RtlAllocateHeap(CURRENT_PROCESS_HEAP, 0, sdh.Size);
    if (Buffer == NULL)
    {
        return NULL;
    }
    Status = NtDeviceIoControlFile(DeviceHandle,
                                   NULL,
                                   NULL,
                                   NULL,
                                   &IoStatusBlock,
                                   IOCTL_STORAGE_QUERY_PROPERTY,
                                   Query,
                                   QuerySize,
                                   Buffer,
                                   sdh.Size);
    if (!NT_SUCCESS(Status))
    {
        goto _fail_1;
    }

    return Buffer;

_fail_1:
    RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, Buffer);
_fail_0:
    WIE_SetLastStatus(Status);
    return NULL;
}

VOID IO_FreeStorageProperty(PVOID Buffer)
{
    RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, Buffer);
}

BOOL Demo_QueryStorageProperty()
{
    UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\Device\\HarddiskVolume1");
    HANDLE DeviceHandle;
    PSTORAGE_DEVICE_DESCRIPTOR psdd;
    STORAGE_PROPERTY_QUERY spq = {
        .PropertyId = StorageDeviceProperty,
        .QueryType = PropertyStandardQuery
    };

    /* Open Device */
    DeviceHandle = IO_OpenDevice(&DeviceName, FILE_READ_ATTRIBUTES | SYNCHRONIZE);
    if (!DeviceHandle)
    {
        DbgPrint("IO_OpenDevice failed with: 0x%08lX\n", WIE_GetLastStatus());
        return FALSE;
    }

    /* Query Property */
    psdd = IO_QueryStorageProperty(DeviceHandle, &spq, sizeof(spq));
    if (!psdd)
    {
        DbgPrint("IO_QueryStorageProperty failed with: 0x%08lX\n", WIE_GetLastStatus());
        NtClose(DeviceHandle);
        return FALSE;
    }

    IO_FreeStorageProperty(psdd);
    NtClose(DeviceHandle);
    return TRUE;
}
