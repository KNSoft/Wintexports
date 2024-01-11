#include "Demo.h"

typedef BOOL CALLBACK FN_DemoSMBIOSTableStringCallback(_In_ BYTE Index, _In_z_ PCSTR String, _In_opt_ PVOID Context);

typedef struct _DEMO_SMBIOS_STRING_FIELD
{
    DWORD Offset;
    PCWSTR Name;
} DEMO_SMBIOS_STRING_FIELD, *PDEMO_SMBIOS_STRING_FIELD;

typedef struct _DEMO_SMBIOS_TABLE_INFO
{
    BYTE Type;
    PCWSTR Name;
    PDEMO_SMBIOS_STRING_FIELD StringField;
    ULONG StringFieldCount;
} DEMO_SMBIOS_TABLE_INFO, *PDEMO_SMBIOS_TABLE_INFO;

#define DEFINE_DMI_STRING(Type, Field) { UFIELD_OFFSET(SMBIOS_TABLE, Type.Field), _A2W(#Field) }

DEMO_SMBIOS_STRING_FIELD g_Type0StringFields[] = {
    DEFINE_DMI_STRING(BIOS_INFO_TYPE_0, Vendor),
    DEFINE_DMI_STRING(BIOS_INFO_TYPE_0, Version),
    DEFINE_DMI_STRING(BIOS_INFO_TYPE_0, ReleaseDate),
};

DEMO_SMBIOS_STRING_FIELD g_Type1StringFields[] = {
    DEFINE_DMI_STRING(SYSTEM_INFO_TYPE_1, Manufacturer),
    DEFINE_DMI_STRING(SYSTEM_INFO_TYPE_1, ProductName),
    DEFINE_DMI_STRING(SYSTEM_INFO_TYPE_1, Version),
    DEFINE_DMI_STRING(SYSTEM_INFO_TYPE_1, SerialNumber),
    DEFINE_DMI_STRING(SYSTEM_INFO_TYPE_1, SKUNumber),
    DEFINE_DMI_STRING(SYSTEM_INFO_TYPE_1, Famliy),
};

DEMO_SMBIOS_STRING_FIELD g_Type2StringFields[] = {
    DEFINE_DMI_STRING(BASEBOARD_INFO_TYPE_2, Manufacturer),
    DEFINE_DMI_STRING(BASEBOARD_INFO_TYPE_2, Product),
    DEFINE_DMI_STRING(BASEBOARD_INFO_TYPE_2, Version),
    DEFINE_DMI_STRING(BASEBOARD_INFO_TYPE_2, SerialNumber),
    DEFINE_DMI_STRING(BASEBOARD_INFO_TYPE_2, AssetTag),
};

DEMO_SMBIOS_STRING_FIELD g_Type3StringFields[] = {
    DEFINE_DMI_STRING(SYSTEM_ENCLOSURE_OR_CHASSIS_TYPE_3, Manufacturer),
    DEFINE_DMI_STRING(SYSTEM_ENCLOSURE_OR_CHASSIS_TYPE_3, Version),
    DEFINE_DMI_STRING(SYSTEM_ENCLOSURE_OR_CHASSIS_TYPE_3, SerialNumber),
    DEFINE_DMI_STRING(SYSTEM_ENCLOSURE_OR_CHASSIS_TYPE_3, AssetTagNumber),
};

DEMO_SMBIOS_STRING_FIELD g_Type4StringFields[] = {
    DEFINE_DMI_STRING(PROCESSOR_INFO_TYPE_4, SocketDesignation),
    DEFINE_DMI_STRING(PROCESSOR_INFO_TYPE_4, Manufacturer),
    DEFINE_DMI_STRING(PROCESSOR_INFO_TYPE_4, Version),
    DEFINE_DMI_STRING(PROCESSOR_INFO_TYPE_4, SerialNumber),
    DEFINE_DMI_STRING(PROCESSOR_INFO_TYPE_4, AssetTag),
    DEFINE_DMI_STRING(PROCESSOR_INFO_TYPE_4, PartNumber),
};

DEMO_SMBIOS_STRING_FIELD g_Type7StringFields[] = {
    DEFINE_DMI_STRING(CACHE_INFO_TYPE_7, SocketDesignation),
};

DEMO_SMBIOS_STRING_FIELD g_Type8StringFields[] = {
    DEFINE_DMI_STRING(PORT_CONNECTOR_INFO_TYPE_8, InternalReferenceDesignator),
    DEFINE_DMI_STRING(PORT_CONNECTOR_INFO_TYPE_8, ExternalReferenceDesignator),
};

DEMO_SMBIOS_STRING_FIELD g_Type9StringFields[] = {
    DEFINE_DMI_STRING(SYSTEM_SLOTS_TYPE_9, Designation),
};

DEMO_SMBIOS_STRING_FIELD g_Type13StringFields[] = {
    DEFINE_DMI_STRING(BIOS_LANGUAGE_INFO_TYPE_13, CurrentLanguage),
};

DEMO_SMBIOS_STRING_FIELD g_Type14StringFields[] = {
    DEFINE_DMI_STRING(GROUP_ASSOCIATIONS_TYPE_14, GroupName),
};

DEMO_SMBIOS_STRING_FIELD g_Type17StringFields[] = {
    DEFINE_DMI_STRING(MEMORY_DEVICE_TYPE_17, DeviceLocator),
    DEFINE_DMI_STRING(MEMORY_DEVICE_TYPE_17, BankLocator),
    DEFINE_DMI_STRING(MEMORY_DEVICE_TYPE_17, Manufacturer),
    DEFINE_DMI_STRING(MEMORY_DEVICE_TYPE_17, SerialNumber),
    DEFINE_DMI_STRING(MEMORY_DEVICE_TYPE_17, AssetTag),
    DEFINE_DMI_STRING(MEMORY_DEVICE_TYPE_17, PartNumber),
    DEFINE_DMI_STRING(MEMORY_DEVICE_TYPE_17, FirmwareVersion),
};

DEMO_SMBIOS_STRING_FIELD g_Type26StringFields[] = {
    DEFINE_DMI_STRING(VOLTAGE_PROBE_TYPE_26, Description),
};

DEMO_SMBIOS_STRING_FIELD g_Type27StringFields[] = {
    DEFINE_DMI_STRING(COOLING_DEVICE_TYPE_27, Description),
};

DEMO_SMBIOS_STRING_FIELD g_Type28StringFields[] = {
    DEFINE_DMI_STRING(TEMPERATURE_PROBE_TYPE_28, Description),
};

DEMO_SMBIOS_STRING_FIELD g_Type29StringFields[] = {
    DEFINE_DMI_STRING(ELECTRICAL_CURRENT_PROBE_TYPE_29, Description),
};

DEMO_SMBIOS_STRING_FIELD g_Type30StringFields[] = {
    DEFINE_DMI_STRING(OUT_OF_BAND_REMOTE_ACCESS_TYPE_30, ManufacturerName),
};

DEMO_SMBIOS_STRING_FIELD g_Type34StringFields[] = {
    DEFINE_DMI_STRING(MANAGEMENT_DEVICE_TYPE_34, Description),
};

DEMO_SMBIOS_STRING_FIELD g_Type35StringFields[] = {
    DEFINE_DMI_STRING(MANAGEMENT_DEVICE_COMPONENT_TYPE_35, Description),
};

DEMO_SMBIOS_STRING_FIELD g_Type39StringFields[] = {
    DEFINE_DMI_STRING(SYSTEM_POWER_SUPPLY_TYPE_39, Location),
    DEFINE_DMI_STRING(SYSTEM_POWER_SUPPLY_TYPE_39, DeviceName),
    DEFINE_DMI_STRING(SYSTEM_POWER_SUPPLY_TYPE_39, Manufacturer),
    DEFINE_DMI_STRING(SYSTEM_POWER_SUPPLY_TYPE_39, SerialNumber),
    DEFINE_DMI_STRING(SYSTEM_POWER_SUPPLY_TYPE_39, AssetTagNumber),
    DEFINE_DMI_STRING(SYSTEM_POWER_SUPPLY_TYPE_39, ModelPartNumber),
    DEFINE_DMI_STRING(SYSTEM_POWER_SUPPLY_TYPE_39, RevisionLevel),
};

DEMO_SMBIOS_STRING_FIELD g_Type41StringFields[] = {
    DEFINE_DMI_STRING(ONBOARD_DEVICES_EXTENDED_INFORMATION_TYPE_41, ReferenceDesignation),
};

DEMO_SMBIOS_STRING_FIELD g_Type43StringFields[] = {
    DEFINE_DMI_STRING(TPM_DEVICE_TYPE_43, Description),
};

DEMO_SMBIOS_STRING_FIELD g_Type45StringFields[] = {
    DEFINE_DMI_STRING(FIRMWARE_INVENTORY_INFO_TYPE_45, ComponentName),
    DEFINE_DMI_STRING(FIRMWARE_INVENTORY_INFO_TYPE_45, Version),
    DEFINE_DMI_STRING(FIRMWARE_INVENTORY_INFO_TYPE_45, ID),
    DEFINE_DMI_STRING(FIRMWARE_INVENTORY_INFO_TYPE_45, ReleaseDate),
    DEFINE_DMI_STRING(FIRMWARE_INVENTORY_INFO_TYPE_45, Manufacturer),
    DEFINE_DMI_STRING(FIRMWARE_INVENTORY_INFO_TYPE_45, LowestSupportedFirmwareVersion),
};

DEMO_SMBIOS_TABLE_INFO g_Tables[] = {
    { 0, L"BIOS Information", g_Type0StringFields, ARRAYSIZE(g_Type0StringFields) },
    { 1, L"System Information", g_Type1StringFields, ARRAYSIZE(g_Type1StringFields) },
    { 2, L"Baseboard Information", g_Type2StringFields, ARRAYSIZE(g_Type2StringFields) },
    { 3, L"System Enclosure or Chassis", g_Type3StringFields, ARRAYSIZE(g_Type3StringFields) },
    { 4, L"Processor Information", g_Type4StringFields, ARRAYSIZE(g_Type4StringFields) },
    { 7, L"Cache Information", g_Type7StringFields, ARRAYSIZE(g_Type7StringFields) },
    { 8, L"Port Connector Information", g_Type8StringFields, ARRAYSIZE(g_Type8StringFields) },
    { 9, L"System Slots", g_Type9StringFields, ARRAYSIZE(g_Type9StringFields) },
    { 10, L"On Board Devices Information (Obsolete)", NULL, 0 },
    { 11, L"OEM Strings", NULL, 0 },
    { 12, L"System Configuration Options", NULL, 0 },
    { 13, L"BIOS Language Information", g_Type13StringFields, ARRAYSIZE(g_Type13StringFields) },
    { 14, L"Group Associations", g_Type14StringFields, ARRAYSIZE(g_Type14StringFields) },
    { 16, L"Physical Memory Array", NULL, 0 },
    { 17, L"Memory Device", g_Type17StringFields, ARRAYSIZE(g_Type17StringFields) },
    { 19, L"Memory Array Mapped Address", NULL, 0 },
    { 20, L"Memory Device Mapped Address", NULL, 0 },
    { 23, L"System Reset", NULL, 0 },
    { 24, L"Hardware Security", NULL, 0 },
    { 25, L"System Power Controls", NULL, 0 },
    { 26, L"Voltage Probe", g_Type26StringFields, ARRAYSIZE(g_Type26StringFields) },
    { 27, L"Cooling Device", g_Type27StringFields, ARRAYSIZE(g_Type27StringFields) },
    { 28, L"Temperature Probe", g_Type28StringFields, ARRAYSIZE(g_Type28StringFields) },
    { 29, L"Electrical Current Probe", g_Type29StringFields, ARRAYSIZE(g_Type29StringFields) },
    { 30, L"Out-of-Band Remote Access", g_Type30StringFields, ARRAYSIZE(g_Type30StringFields) },
    { 32, L"System Boot Information", NULL, 0 },
    { 34, L"Management Device", g_Type34StringFields, ARRAYSIZE(g_Type34StringFields) },
    { 35, L"Management Device Component", g_Type35StringFields, ARRAYSIZE(g_Type35StringFields) },
    { 39, L"System Power Supply", g_Type39StringFields, ARRAYSIZE(g_Type39StringFields) },
    { 41, L"Onboard Devices Extended Information", g_Type41StringFields, ARRAYSIZE(g_Type41StringFields) },
    { 43, L"TPM Device", g_Type43StringFields, ARRAYSIZE(g_Type43StringFields) },
    { 44, L"Processor Additional Information", NULL, 0 },
    { 45, L"Firmware Inventory Information", g_Type45StringFields, ARRAYSIZE(g_Type45StringFields) },
    { 127, L"End-of-Table", NULL, 0 },
};

_Ret_maybenull_
PSYSTEM_FIRMWARE_TABLE_INFORMATION NT_GetFirmwareTable(
    ULONG ProviderSignature,
    ULONG TableID,
    SYSTEM_FIRMWARE_TABLE_ACTION Action)
{
    NTSTATUS Status;
    ULONG Length;
    SYSTEM_FIRMWARE_TABLE_INFORMATION FirmwareInfo;
    PSYSTEM_FIRMWARE_TABLE_INFORMATION Buffer;

    FirmwareInfo.ProviderSignature = ProviderSignature;
    FirmwareInfo.Action = Action;
    FirmwareInfo.TableID = TableID;
    FirmwareInfo.TableBufferLength = 0;

    Status = NtQuerySystemInformation(SystemFirmwareTableInformation, &FirmwareInfo, sizeof(FirmwareInfo), &Length);
    if (Status != STATUS_BUFFER_TOO_SMALL)
    {
        WIE_SetLastStatus(Status);
        return NULL;
    }

    _Analysis_assume_(Length >= sizeof(FirmwareInfo));
    Buffer = RtlAllocateHeap(CURRENT_PROCESS_HEAP, 0, Length);
    if (Buffer == NULL)
    {
        return NULL;
    }

    RtlCopyMemory(Buffer, &FirmwareInfo, sizeof(FirmwareInfo));
    Status = NtQuerySystemInformation(SystemFirmwareTableInformation, Buffer, Length, &Length);
    if (!NT_SUCCESS(Status))
    {
        RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, Buffer);
        return NULL;
    }

    return Buffer;
}

BOOL CALLBACK SMBIOSTableStringCallback(_In_ BYTE Index, _In_z_ PCSTR String, _In_opt_ PVOID Context)
{
    PSMBIOS_TABLE SMBIOSTable;
    ULONG i, j;

    if (Context == NULL)
    {
        return FALSE;
    }

    SMBIOSTable = Context;
    for (i = 0; i < ARRAYSIZE(g_Tables); i++)
    {
        if (g_Tables[i].Type == SMBIOSTable->Header.Type)
        {
            break;
        }
    }
    if (i >= ARRAYSIZE(g_Tables))
    {
        return TRUE;
    }
    if (g_Tables[i].StringFieldCount > 0)
    {
        for (j = 0; j < g_Tables[i].StringFieldCount; j++)
        {
            if (g_Tables[i].StringField[j].Offset < SMBIOSTable->Header.Length &&
                *((PBYTE)SMBIOSTable + g_Tables[i].StringField[j].Offset) == Index)
            {
                DbgPrint("\t%ls: %hs\n", g_Tables[i].StringField[j].Name, String);
            }
        }
    } else if (SMBIOSTable->Header.Type == 10 ||
               SMBIOSTable->Header.Type == 11 ||
               SMBIOSTable->Header.Type == 12)
    {
        DbgPrint("\t%hs\n", String);
    }

    return TRUE;
}

_Ret_maybenull_
PSMBIOS_TABLE EnumSMBIOSString(
    _In_ PSMBIOS_RAWDATA SMBIOSData,
    _In_ PSMBIOS_TABLE Table,
    _In_opt_ FN_DemoSMBIOSTableStringCallback* Callback,
    _In_opt_ PVOID Context)
{
    PCSTR psz;
    BYTE i;
    BOOL Continue;
    PVOID pEnd;
    SIZE_T sMaxCount, sLen;

    pEnd = Add2Ptr(SMBIOSData->SMBIOSTableData, SMBIOSData->Length);
    psz = (PCSTR)Add2Ptr(Table, Table->Header.Length);
    if (*(PWORD)psz == 0)
    {
        return (PSMBIOS_TABLE)Add2Ptr(psz, sizeof(WORD));
    }

    i = 1;
    Continue = TRUE;
    while (psz + sizeof(WORD) < (PCSTR)pEnd)
    {
        sMaxCount = PtrOffset(psz, pEnd);
        sLen = strnlen(psz, sMaxCount);
        if (sLen == sMaxCount)
        {
            break;
        }

        if (Continue && Callback != NULL)
        {
            Continue = Callback(i, psz, Context);
        }

        psz += sLen + 1;
        if (psz[0] == 0)
        {
            return (PSMBIOS_TABLE)(psz + 1);
        }
        i++;
    };

    return NULL;
}

VOID PrintSMBIOSTableInfo(_In_ PSMBIOS_TABLE Table)
{
    if (Table->Header.Type == 0)
    {
        DbgPrint("\tRelease Version: %u.%u\n",
                 Table->BIOS_INFO_TYPE_0.MajorRelease,
                 Table->BIOS_INFO_TYPE_0.MinorRelease);
        DbgPrint("\tEC Firmware Release Version: %u.%u\n",
                 Table->BIOS_INFO_TYPE_0.ECFirmwareMajorRelease,
                 Table->BIOS_INFO_TYPE_0.ECFirmwareMinorRelease);
    } else if (Table->Header.Type == 4)
    {
        DbgPrint("\tID: 0x%016llX\n", Table->PROCESSOR_INFO_TYPE_4.ID);
        if (Table->PROCESSOR_INFO_TYPE_4.MaxSpeed != 0)
        {
            DbgPrint("\tMaxSpeed: %u MHz\n", Table->PROCESSOR_INFO_TYPE_4.MaxSpeed);
        }
        if (Table->PROCESSOR_INFO_TYPE_4.CurrentSpeed != 0)
        {
            DbgPrint("\tCurrentSpeed: %u MHz\n", Table->PROCESSOR_INFO_TYPE_4.CurrentSpeed);
        }
        if (Table->PROCESSOR_INFO_TYPE_4.CoreCount != 0)
        {
            DbgPrint("\tCoreCount: %u\n", Table->PROCESSOR_INFO_TYPE_4.CoreCount);
        }
        if (Table->PROCESSOR_INFO_TYPE_4.ThreadCount != 0)
        {
            DbgPrint("\tThreadCount: %u\n", Table->PROCESSOR_INFO_TYPE_4.ThreadCount);
        }
    } else if (Table->Header.Type == 16)
    {
        if (Table->PHYSICAL_MEMORY_ARRAY_TYPE_16.MaximumCapacity != 0x80000000)
        {
            DbgPrint("\tMaximumCapacity: %u KB\n", Table->PHYSICAL_MEMORY_ARRAY_TYPE_16.MaximumCapacity);
        }
    } else if (Table->Header.Type == 17)
    {
        DbgPrint("\tSpeed: %u MT/s\n", Table->MEMORY_DEVICE_TYPE_17.Speed);
        if (Table->MEMORY_DEVICE_TYPE_17.ConfiguredMemorySpeed != 0x0000 &&
            Table->MEMORY_DEVICE_TYPE_17.ConfiguredMemorySpeed != 0xFFFF)
        {
            DbgPrint("\tConfiguredMemorySpeed: %u MT/s\n", Table->MEMORY_DEVICE_TYPE_17.ConfiguredMemorySpeed);
        }
        if (Table->MEMORY_DEVICE_TYPE_17.MinimumVoltage != 0)
        {
            DbgPrint("\tMinimumVoltage: %u mV\n", Table->MEMORY_DEVICE_TYPE_17.MinimumVoltage);
        }
        if (Table->MEMORY_DEVICE_TYPE_17.MaximumVoltage != 0)
        {
            DbgPrint("\tMaximumVoltage: %u mV\n", Table->MEMORY_DEVICE_TYPE_17.MaximumVoltage);
        }
        if (Table->MEMORY_DEVICE_TYPE_17.ConfiguredVoltage != 0)
        {
            DbgPrint("\tConfiguredVoltage: %u mV\n", Table->MEMORY_DEVICE_TYPE_17.ConfiguredVoltage);
        }
    } else if (Table->Header.Type == 39)
    {
        if (Table->SYSTEM_POWER_SUPPLY_TYPE_39.MaxPowerCapacity != 0x8000)
        {
            DbgPrint("\tMaxPowerCapacity: %u mW\n", Table->SYSTEM_POWER_SUPPLY_TYPE_39.MaxPowerCapacity);
        }
    } else if (Table->Header.Type == 43)
    {
        DbgPrint("\tVendorID: %c%c%c%c\n",
                 Table->TPM_DEVICE_TYPE_43.VendorID[0],
                 Table->TPM_DEVICE_TYPE_43.VendorID[1],
                 Table->TPM_DEVICE_TYPE_43.VendorID[2],
                 Table->TPM_DEVICE_TYPE_43.VendorID[3]);
        DbgPrint("\tSpecVersion: %u.%u\n",
                 Table->TPM_DEVICE_TYPE_43.MajorSpecVersion,
                 Table->TPM_DEVICE_TYPE_43.MinorSpecVersion);
        DbgPrint("\tOEMDefined: 0x%08lX\n", Table->TPM_DEVICE_TYPE_43.OEMDefined);
    } else if (Table->Header.Type == 45)
    {
        DbgPrint("\tImageSize: 0x%016llX\n", Table->FIRMWARE_INVENTORY_INFO_TYPE_45.ImageSize);
    }
}

BOOL Demo_SMBIOS()
{
    PSYSTEM_FIRMWARE_TABLE_INFORMATION FirmwareInfo;
    PSMBIOS_RAWDATA SMBIOSRawData;
    PSMBIOS_TABLE SMBIOSTable;
    ULONG i;

    FirmwareInfo = NT_GetFirmwareTable('RSMB', 0, SystemFirmwareTable_Get);
    if (FirmwareInfo == NULL)
    {
        DbgPrint("NT_GetFirmwareTable failed with 0x%08lX\n", WIE_GetLastStatus());
        return FALSE;
    }
    SMBIOSRawData = (PSMBIOS_RAWDATA)FirmwareInfo->TableBuffer;
    if (FirmwareInfo->TableBufferLength < sizeof(*SMBIOSRawData) ||
        FirmwareInfo->TableBufferLength != sizeof(*SMBIOSRawData) + SMBIOSRawData->Length)
    {
        DbgPrint("SMBIOS Data size incorrect\n");
        return FALSE;
    }

    DbgPrint("SMBIOS Version: %u.%u\n", SMBIOSRawData->SMBIOSMajorVersion, SMBIOSRawData->SMBIOSMinorVersion);
    DbgPrint("DMI Revision: %u\n", SMBIOSRawData->DmiRevision);
    DbgPrint("Data Size: %u\n\n", SMBIOSRawData->Length);

    SMBIOSTable = (PSMBIOS_TABLE)SMBIOSRawData->SMBIOSTableData;
    do
    {
        for (i = 0; i < ARRAYSIZE(g_Tables); i++)
        {
            if (g_Tables[i].Type == SMBIOSTable->Header.Type)
            {
                DbgPrint("[Type %u - %ls]\n", SMBIOSTable->Header.Type, g_Tables[i].Name);
                break;
            }
        }
        if (i >= ARRAYSIZE(g_Tables))
        {
            DbgPrint("[Type %u]\n", SMBIOSTable->Header.Type);
        }
        PrintSMBIOSTableInfo(SMBIOSTable);
        SMBIOSTable = EnumSMBIOSString(SMBIOSRawData, SMBIOSTable, SMBIOSTableStringCallback, SMBIOSTable);
    } while (SMBIOSTable != NULL && (PBYTE)SMBIOSTable < SMBIOSRawData->SMBIOSTableData + SMBIOSRawData->Length);

    RtlFreeHeap(CURRENT_PROCESS_HEAP, 0, FirmwareInfo);
    return TRUE;
}
