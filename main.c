#include "uefi_structures.h"
#include "uefi_lib.h"

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;

    clearScreen(SystemTable); // clear screen

    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL WhitePixel = {255, 255, 255, 0};
    SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, NULL, (VOID **)&Gop);

    UINTN Width = Gop->Mode->Info->HorizontalResolution;
    UINTN Height = Gop->Mode->Info->VerticalResolution;

    UINTN TextCols;
    UINTN TextRows;

    setTextPosition(SystemTable, 4, 2);
    Print(SystemTable, L"Welcome to the SIMPLE Bootloader");

    borderOutline(Gop, &WhitePixel, Width, Height);
    setTextColour(SystemTable, EFI_YELLOW);

    getNumRowAndCol(SystemTable, &TextCols, &TextRows);
    setTextPosition(SystemTable, 0, TextRows - 5); // adjust the row number for each option
    Print(SystemTable, L"[Press 'b' to boot]\n");

    setTextPosition(SystemTable, 0, TextRows - 4); // move cursor down
    Print(SystemTable, L"[Press 'i' to print system specs]\n");

    setTextPosition(SystemTable, 0, TextRows - 3); // move cursor down
    Print(SystemTable, L"[Press 'r' to reboot]\n");

    setTextPosition(SystemTable, 0, TextRows - 2); // move cursor down
    Print(SystemTable, L"[Press 's' to shutdown]\n");

    setTextColour(SystemTable, EFI_LIGHTCYAN);
    SystemTable->ConIn->Reset(SystemTable->ConIn, 1); // clear keyboard buffer

    EFI_INPUT_KEY Key;

    do
    { // Take input from the user as long as the user doesnt enter b or r
        Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key);

        if (Key.UnicodeChar == L'r' || Key.UnicodeChar == L'R')
        {
            setTextPosition(SystemTable, 5, 2);
            Print(SystemTable, L"Rebooting...\n");
            SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
        }
        else if (Key.UnicodeChar == L'b' || Key.UnicodeChar == L'B')
        {
            setTextPosition(SystemTable, 5, 2);
            Print(SystemTable, L"Booting...\n");
        }
    } while (Status == EFI_NOT_READY || !(Key.UnicodeChar == L'r' || Key.UnicodeChar == L'R' || Key.UnicodeChar == L'b' || Key.UnicodeChar == L'B'));

    return 0;
}

// MOve reboot, shutdown options to bottom