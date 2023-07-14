#pragma once

#include "uefi_structures.h"

void setTextPosition(EFI_SYSTEM_TABLE *SystemTable, UINT32 Row, UINT32 Col)
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

void borderOutline(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Colour, UINTN Width, UINTN Height)
{
     /*
        This function creates a two pixel wide border on the screen
        with a 10 pixel margin from the edge
     */

     for (UINTN X = 10; X < Width - 10; X++)
     {
          setPixel(Gop, X, 10, Colour);              // Top outer pixel
          setPixel(Gop, X, 10 + 1, Colour);          // Top inner pixel
          setPixel(Gop, X, Height - 1 - 10, Colour); // Bottom outer pixel
          setPixel(Gop, X, Height - 2 - 10, Colour); // Bottom inner pixel
     }

     for (UINTN Y = 10; Y < Height - 10; Y++)
     {
          setPixel(Gop, 10, Y, Colour);             // Left outer pixel
          setPixel(Gop, 10 + 1, Y, Colour);         // Left inner pixel
          setPixel(Gop, Width - 1 - 10, Y, Colour); // Right outer pixel
          setPixel(Gop, Width - 2 - 10, Y, Colour); // Right inner pixel
     }
}