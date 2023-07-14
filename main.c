#include "uefi_structures.h"
#include "uefi_lib.h"


EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, NULL, (VOID **)&Gop);

    clearScreen(SystemTable); // Clear screen
    borderOutline(Gop);       // Create white border

    setTextPosition(SystemTable, 4, 2);
    Print(SystemTable, L"Welcome to the SIMPLE Bootloader"); // Print Hello message

    setTextColour(SystemTable, EFI_YELLOW);
    printOptions(SystemTable, Gop);                      // Print Bootloader options

    SystemTable->ConIn->Reset(SystemTable->ConIn, 1); // clear keyboard buffer

    EFI_INPUT_KEY Key;

    do
    { // Take input from the user as long as the user doesnt enter b or r
        Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key);

        if (Key.UnicodeChar == L'r' || Key.UnicodeChar == L'R')
        {
            setTextPosition(SystemTable, 2, 5);
            Print(SystemTable, L"Rebooting...\n");
            SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
        }
        else if (Key.UnicodeChar == L'b' || Key.UnicodeChar == L'B')
        {
            setTextPosition(SystemTable, 2, 5);
            Print(SystemTable, L"Booting...\n");
        }
    } while (Status == EFI_NOT_READY || !(Key.UnicodeChar == L'r' || Key.UnicodeChar == L'R' || Key.UnicodeChar == L'b' || Key.UnicodeChar == L'B'));

    return 0;
}

// MOve reboot, shutdown options to bottom