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
    SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, NULL, (VOID**)&Gop);

    UINTN Width  = Gop->Mode->Info->HorizontalResolution;
    UINTN Height = Gop->Mode->Info->VerticalResolution;
    borderOutline(Gop, &WhitePixel, Width, Height);

    setTextColour(SystemTable, EFI_YELLOW);
    setTextPosition(SystemTable, 3, 2);
    Print(SystemTable, L"Welcome to the Simple UEFI Bootloader.\n\n");

    setTextColour(SystemTable, EFI_LIGHTCYAN);
    setTextPosition(SystemTable, 4, 2);
    Print(SystemTable, L"Press 'r' to reboot | Press 'b' to boot\n");

    SystemTable->ConIn->Reset(SystemTable->ConIn, 1); // clear keyboard buffer

    EFI_INPUT_KEY Key;

    do { // Take input from the user as long as the user doesnt enter b or r
           Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key);

           if (Key.UnicodeChar == L'r' || Key.UnicodeChar == L'R') {
               Print(SystemTable, L"Rebooting...\n");
               SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
           }
	       else if (Key.UnicodeChar == L'b' || Key.UnicodeChar == L'B') {
               setTextPosition(SystemTable, 3, 2);
	           Print(SystemTable, L"Booting...\n");
           }
    }
    while (Status == EFI_NOT_READY || !(Key.UnicodeChar == L'r' || Key.UnicodeChar == L'R' || Key.UnicodeChar == L'b' || Key.UnicodeChar == L'B'));

    Print(SystemTable, L"\nKey pressed: ");
    // Convert the key value to a wide character string
    wchar_t KeyChar[2];
    KeyChar[0] = Key.UnicodeChar;
    KeyChar[1] = L'\0'; // Null-terminate the string

    SystemTable->ConOut->OutputString(SystemTable->ConOut, KeyChar);

    return 0;
}