#include "uefi_structures.h"
#include "uefi_lib.h"

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_INPUT_KEY Key;

    printIntroduction(SystemTable);
    clearKeyboardBuffer(SystemTable); // clear keyboard buffer
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

    EFI_FILE_PROTOCOL *Volume = GetVolume(SystemTable, ImageHandle);   // Open EFI FAT32 filesystem
    EFI_FILE_PROTOCOL *file = checkForConfigFile(SystemTable, Volume); // Check if 'simple.cfg' exists and if so points to it
    VOID *FileContents = NULL;                                         // Points to memory where file contents are stored 
    UINTN fileSize = GetFileSize(file);                       // Stores size of file contents

    if (file != NULL)
    {
        Status = SystemTable->BootServices->AllocatePool(EfiLoaderData, fileSize, (VOID **)&FileContents); // Allocate memory for file content buffer
        Status = file->Read(file, &fileSize, FileContents);                                                // Store file content in buffer
    }

    CHAR16 **names = parseConfigFile(SystemTable, FileContents, fileSize);
    checkKernelMagicNumber(SystemTable, Volume, names[0]);

    Delay(SystemTable, 50);

    return 0;   
}