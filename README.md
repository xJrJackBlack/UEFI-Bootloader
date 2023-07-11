# Unified Extensible Firmware Interface (UEFI) Linux Bootloader
A UEFI Bootloader made for Linux



# Tools and Resources

I was going to initially use GNU-EFI and GCC for this project however i decided to use the following tools for more flexibility:

- [UEFI Specification (Might be outdated depending on when your reading this)](https://uefi.org/sites/default/files/resources/UEFI_Spec_2_10_Aug29.pdf)
- Clang - ```sudo apt install clang```
- LLVM Linker - ```sudo apt install lld```
- Qemu - ```sudo apt install qemu-system```
- OVMF -  ```sudo apt install ovmf```


# Creating a Hello World EFI Program

To begin writing a bootloader I needed to write a simple "Hello World!" program, In order to do this I created a header file with the necessary structure and type definitions as per the UEFI Specification. 

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

