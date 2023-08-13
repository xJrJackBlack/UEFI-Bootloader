#pragma once

#include "uefi_structures.h"

struct rsdp
{
    CHAR8 signature[8];
    UINT8 checksum;
    CHAR8 oem_id[6];
    UINT8 rev;
    UINT32 rsdt_addr;
    UINT32 length;
    UINT64 xsdt_addr;
    UINT8 ext_checksum;
    UINT8 reserved[3];
} __attribute__((packed));

#define EFI_ACPI_20_TABLE_GUID                                                         \
    {                                                                                  \
        0x8868e871, 0xe4f1, 0x11d3, { 0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 } \
    }