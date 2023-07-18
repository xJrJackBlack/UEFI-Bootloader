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
     SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
}

void clearKeyboardBuffer(EFI_SYSTEM_TABLE *SystemTable)
{

     SystemTable->ConIn->Reset(SystemTable->ConIn, 1);
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
     setTextPosition(SystemTable, 0, TextRows - 4); // adjust the row number for each option
     Print(SystemTable, L"[Press 'b' to boot]\n");

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

void Delay(EFI_SYSTEM_TABLE *SystemTable, UINTN Seconds)
{
     SystemTable->BootServices->Stall(1000000 * Seconds);
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

void printIntroduction(EFI_SYSTEM_TABLE *SystemTable)
{

     EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
     SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, NULL, (VOID **)&Gop);

     clearScreen(SystemTable); // Clear screen
     borderOutline(Gop);       // Create white border

     setTextPosition(SystemTable, 4, 2);
     Print(SystemTable, L"Welcome to the SIMPLE Bootloader\n"); // Print Hello message

     //setTextPosition(SystemTable, 4, 3);
     //printTime(SystemTable); // Print current time

     setTextPosition(SystemTable, 4, 4);
     printUEFIVersion(SystemTable); // Print UEFI version

     setTextColour(SystemTable, EFI_YELLOW);
     printOptions(SystemTable, Gop);   // Print Bootloader options
}

EFI_FILE_PROTOCOL *GetVolume(EFI_SYSTEM_TABLE *SystemTable, EFI_HANDLE ImageHandle)
{
     /*
       Open the FAT32 formatted EFI partition using ImageHandle
       and return a pointer to the volume
     */

     clearScreen(SystemTable);
     clearKeyboardBuffer(SystemTable);

     EFI_STATUS Status;
     EFI_LOADED_IMAGE_PROTOCOL *LoadedImage = NULL;
     EFI_GUID LipGUID = EFI_LOADED_IMAGE_PROTOCOL_GUID;

     EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem = NULL;
     EFI_GUID FsGUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

     EFI_FILE_PROTOCOL *RootVolume = NULL;

     SystemTable->BootServices->HandleProtocol(ImageHandle, &LipGUID, (void **)&LoadedImage);

     SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &FsGUID, (void **)&FileSystem);

     Status = FileSystem->OpenVolume(FileSystem, &RootVolume);

     setTextPosition(SystemTable, 4, 2);

     if (Status != EFI_SUCCESS)
     {
          clearScreen(SystemTable);
          setTextColour(SystemTable, EFI_RED);
          Print(SystemTable, L"FATAL ERROR: Failed to open Volume.\n");
          Delay(SystemTable, 5);
     }
     else
     {
          Print(SystemTable, L"Opened filesystem...");
          Delay(SystemTable, 2);
     }

     return RootVolume;
}

EFI_FILE_PROTOCOL *checkForConfigFile(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *Volume)
{
     /*
       Check if the simple.cfg configuration file exists, if it does not
       then the bootloader won't know which kernel image to work with
     */

     EFI_STATUS Status;
     EFI_FILE_PROTOCOL *file;
     Status = Volume->Open(Volume, &file, L"simple.cfg", EFI_FILE_READ_ONLY, 0);

     setTextPosition(SystemTable, 4, 3);

     if (Status != EFI_SUCCESS)
     {
          clearScreen(SystemTable);
          setTextColour(SystemTable, EFI_RED);
          Print(SystemTable, L"FATAL ERROR: 'simple.cfg' file not found.");
          Delay(SystemTable, 5);
          return NULL;
     }
     else
     {
          Print(SystemTable, L"Opened config file 'simple.cfg'...\n");
          Delay(SystemTable, 2);
     }

     return file;
}

UINT64 GetFileSize (EFI_FILE_PROTOCOL* FileName)
{
    UINT64 Size = 0;
    FileName->SetPosition(FileName, 0xFFFFFFFFFFFFFFFFULL);
    FileName->GetPosition(FileName, &Size);
    FileName->SetPosition(FileName, 0);
    return Size;
}

void printAscii(EFI_SYSTEM_TABLE *SystemTable, UINT8 *str) {
    while (*str != '\0') {
        CHAR16 out[2];
        out[0] = (CHAR16)*str;
        out[1] = '\0';
        Print(SystemTable, out);
        str++;
    }
}