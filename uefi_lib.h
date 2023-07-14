#pragma once

#include "uefi_structures.h"

void setTextPosition(EFI_SYSTEM_TABLE *SystemTable, UINT32 Col, UINT32 Row)
{
     SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, Col, Row);
}

void Print(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *String)
{
     SystemTable->ConOut->OutputString(SystemTable->ConOut, String);
}

void clearScreen(EFI_SYSTEM_TABLE *SystemTable)
{
     SystemTable->ConOut->Reset(SystemTable->ConOut, 1);
}

void setTextColour(EFI_SYSTEM_TABLE *SystemTable, UINTN Attribute)
{
     SystemTable->ConOut->SetAttribute(SystemTable->ConOut, Attribute);
}

void setPixel(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, UINT32 x, UINT32 y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Colour)
{
     Gop->Blt(Gop, Colour, EfiBltVideoFill, 0, 0, x, y, 1, 1, 0);
}

void borderOutline(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop)
{
     /*
        This function creates a two pixel wide border on the screen
        with a 10 pixel margin from the edge

        Make sure to call SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, NULL, (VOID **)&Gop);
        before using this function
     */

     EFI_GRAPHICS_OUTPUT_BLT_PIXEL WhitePixel = {255, 255, 255, 0};

     UINTN Width = Gop->Mode->Info->HorizontalResolution;
     UINTN Height = Gop->Mode->Info->VerticalResolution;

     for (UINTN X = 10; X < Width - 10; X++)
     {
          setPixel(Gop, X, 10, &WhitePixel);              // Top outer pixel
          setPixel(Gop, X, 10 + 1, &WhitePixel);          // Top inner pixel
          setPixel(Gop, X, Height - 1 - 10, &WhitePixel); // Bottom outer pixel
          setPixel(Gop, X, Height - 2 - 10, &WhitePixel); // Bottom inner pixel
     }

     for (UINTN Y = 10; Y < Height - 10; Y++)
     {
          setPixel(Gop, 10, Y, &WhitePixel);             // Left outer pixel
          setPixel(Gop, 10 + 1, Y, &WhitePixel);         // Left inner pixel
          setPixel(Gop, Width - 1 - 10, Y, &WhitePixel); // Right outer pixel
          setPixel(Gop, Width - 2 - 10, Y, &WhitePixel); // Right inner pixel
     }
}

void getNumRowAndCol(EFI_SYSTEM_TABLE *SystemTable, UINTN *Cols, UINTN *Rows)
{
     SystemTable->ConOut->QueryMode(SystemTable->ConOut, SystemTable->ConOut->Mode->Mode, Cols, Rows);
}

void printOptions(EFI_SYSTEM_TABLE *SystemTable, EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop)
{
     /*
        Make sure to call SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, NULL, (VOID **)&Gop);
        before using this function
     */

     UINTN TextCols;
     UINTN TextRows;

     getNumRowAndCol(SystemTable, &TextCols, &TextRows);
     setTextPosition(SystemTable, 0, TextRows - 5); // adjust the row number for each option
     Print(SystemTable, L"[Press 'b' to boot]\n");

     setTextPosition(SystemTable, 0, TextRows - 4); // move cursor down
     Print(SystemTable, L"[Press 'i' to print system specs]\n");

     setTextPosition(SystemTable, 0, TextRows - 3); // move cursor down
     Print(SystemTable, L"[Press 'r' to reboot]\n");

     setTextPosition(SystemTable, 0, TextRows - 2); // move cursor down
     Print(SystemTable, L"[Press 's' to shutdown]\n");
}

void COLD_REBOOT(EFI_SYSTEM_TABLE *SystemTable)
{
     SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
}

void SHUTDOWN(EFI_SYSTEM_TABLE *SystemTable)
{
     SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
}

void printNum(EFI_SYSTEM_TABLE *SystemTable, UINTN num)
{
     CHAR16 Buffer[16];
     UINTN i = 0;

     while (num)
     {
          Buffer[i++] = (num % 10) + '0';
          num /= 10;
     }

     Buffer[i] = '\0';

     UINTN left = 0;
     UINTN right = i - 1;

     while (left < right)
     {
          CHAR16 tmp = Buffer[left];
          Buffer[left++] = Buffer[right];
          Buffer[right--] = tmp;
     }

     Print(SystemTable, Buffer);
}

void printTime(EFI_SYSTEM_TABLE *SystemTable)
{
     EFI_TIME currentTime;
     SystemTable->RuntimeServices->GetTime(&currentTime, NULL);

     Print(SystemTable, L"Current Time: ");
     printNum(SystemTable, currentTime.Day);
     Print(SystemTable, L"/");
     printNum(SystemTable, currentTime.Month);
     Print(SystemTable, L"/");
     printNum(SystemTable, currentTime.Year);

     Print(SystemTable, L"  ");

     printNum(SystemTable, currentTime.Hour);
     Print(SystemTable, L":");
     printNum(SystemTable, currentTime.Minute);
     Print(SystemTable, L":");
     printNum(SystemTable, currentTime.Second);
     Print(SystemTable, L"\n");
}

void printUEFIVersion(EFI_SYSTEM_TABLE *SystemTable)
{
     Print(SystemTable, L"UEFI Version: ");
     printNum(SystemTable, SystemTable->Hdr.Revision >> 16);
     Print(SystemTable, L".");
     printNum(SystemTable, SystemTable->Hdr.Revision & 0XFFFF);
     Print(SystemTable, L"\n");
}
