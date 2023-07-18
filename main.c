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

    EFI_FILE_PROTOCOL *Volume = GetVolume(SystemTable, ImageHandle); // Open EFI FAT32 filesystem
    EFI_FILE_PROTOCOL *file = checkForConfigFile(SystemTable, Volume); // Check if 'simple.cfg' exists and if so points to it
    VOID *FileContents = NULL; // Points to memory where file contents are stored 
    UINTN fileSize = GetFileSize(file);

    if (file != NULL)
    {
        Status = SystemTable->BootServices->AllocatePool(EfiLoaderData, fileSize, (VOID **)&FileContents); // Allocate memory for file content buffer
        Status = file->Read(file, &fileSize, FileContents); // Store file content in buffer
    }
    
    /*
    for (UINTN i = 0; i < fileSize; i++) {
        
         UINT8 val = ((UINT8*)FileContents)[i];

         if (val >= 33 && val <= 126) {
             CHAR16 str[2];
             str[0] = (CHAR16) val;
             str[1] = '\0';  // Null-terminator for the string
             Print(SystemTable, str);
         }
    }
    */

    UINT8* fileContents = (UINT8*) FileContents;
    UINTN i = 0;

    for (; i < fileSize && fileContents[i] != '#'; ++i);

    if (i == fileSize) {
        clearScreen(SystemTable);
        setTextColour(SystemTable, EFI_RED);
        Print(SystemTable, L"FATAL ERROR: Invalid entry in 'simple.cfg'.");
        Delay(SystemTable, 5);
        return 0;
    }

    UINT8 *name1;
    UINT8 *name2;

    SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(UINT8) * i+1, (VOID**)&name1); // Allocate memory for kernel image name
    SystemTable->BootServices->CopyMem(name1, FileContents, sizeof(UINT8) * i);                  // Copy kernel image file name into name1 buffer

    SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(UINT8) * fileSize-i, (VOID**)&name2);
    SystemTable->BootServices->CopyMem(name2, FileContents+i+1, sizeof(UINT8) * fileSize-i-1);
    name1[i] = '\0';
    name2[fileSize-i-1] = '\0';

    printAscii(SystemTable, name1);
    Print(SystemTable, L"\n");
    printAscii(SystemTable, name2);
    Delay(SystemTable, 50);

    return 0;   
}

/*
he#lo
01234
*/