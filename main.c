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

    EFI_FILE_PROTOCOL *Volume = GetVolume(SystemTable, ImageHandle);            // Open EFI FAT32 filesystem
    Delay(SystemTable, 2);
    checkForConfigFile(SystemTable, Volume);                                  // Check if 'simple.cfg' exists
    //CHAR16 *file_names = getKernelImageAndInitRamFSName(SystemTable, Volume); // Read and parse 'simple.cfg' for kernel image and initramfs file names


    return 0;
}
