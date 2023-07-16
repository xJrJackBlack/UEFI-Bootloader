#include "uefi_structures.h"
#include "uefi_lib.h"

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_INPUT_KEY Key;

    printIntroduction(SystemTable);

    do
    { 
        Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key);

        if (Key.UnicodeChar == L'r' || Key.UnicodeChar == L'R')
        {
            COLD_REBOOT(SystemTable);
        }
        else if (Key.UnicodeChar == L'b' || Key.UnicodeChar == L'B')
        {
        }
        else if (Key.UnicodeChar == L's' || Key.UnicodeChar == L'S')
        {
            SHUTDOWN(SystemTable);
        }
    } while (Status == EFI_NOT_READY || !(Key.UnicodeChar == L'r' || Key.UnicodeChar == L'R' || Key.UnicodeChar == L'b' || Key.UnicodeChar == L'B'));

    EFI_FILE_PROTOCOL *vol = GetVolume(SystemTable, ImageHandle); // Open EFI FAT32 filesystem
    EFI_FILE_PROTOCOL *file;

    checkForConfigFile(SystemTable, vol);
    //SystemTable->BootServices->Stall(100000 * 20);

    return 0;
}
