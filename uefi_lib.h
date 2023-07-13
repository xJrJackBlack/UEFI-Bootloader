#pragma once

#include "uefi_structures.h"

void setTextPosition(EFI_SYSTEM_TABLE *SystemTable, UINT32 Row, UINT32 Col) {

     SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, Col, Row);

}

void Print(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *String) {

     SystemTable->ConOut->OutputString(SystemTable->ConOut, String);
}

void clearScreen(EFI_SYSTEM_TABLE *SystemTable) {

     SystemTable->ConOut->Reset(SystemTable->ConOut, 1);

}

void setTextColour(EFI_SYSTEM_TABLE *SystemTable, UINTN Attribute) {

     SystemTable->ConOut->SetAttribute(SystemTable->ConOut, Attribute);
}