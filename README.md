# Unified Extensible Firmware Interface (UEFI) Linux Bootloader
A UEFI Bootloader made for Linux and small tutorial in case you want to make one yourself.


# Tools and Resources

I was going to initially use GNU-EFI and GCC for this project however i decided to use the following tools for more flexibility:

- [UEFI Specification (Might be outdated depending on when your reading this)](https://uefi.org/sites/default/files/resources/UEFI_Spec_2_10_Aug29.pdf)
- Clang - ```sudo apt install clang```
- LLVM Linker - ```sudo apt install lld```
- Qemu - ```sudo apt install qemu-system```
- OVMF -  ```sudo apt install ovmf```


# Creating a Hello World EFI Program

To begin writing a bootloader I needed to write a simple "Hello World!" program, In order to do this I created a header file with the necessary definitions as per the UEFI Specification. By creating this header it gives us (the programmer) an easy way to interface with the computers underlying UEFI firmware and access it's functions and runtime services. I defined everything in the [uefi_structures.h](https://github.com/programmer838/Bootloader/blob/main/uefi_structures.h) file, it contains various data types, structs, function pointers and much more.

```
#include "uefi_structures.h"

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status = SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Welcome to Qasim's EFI Program.\n");
    return Status;
}
```
# Testing and Running During Development



