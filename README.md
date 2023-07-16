# Unified Extensible Firmware Interface (UEFI) Linux Bootloader
A UEFI Bootloader made for Linux, below i detail the development process.


# Tools and Resources

I was going to initially use GNU-EFI and GCC for this project however i decided to use the following tools for more flexibility:

- Clang
- LLVM Linker
- Qemu
- OVMF


# Creating a Hello World EFI Program

To begin writing a bootloader I needed to write a simple "Hello World!" program, In order to do this I created a header file with the necessary definitions as per the [UEFI Specification (Might be outdated depending on when your reading this)](https://uefi.org/sites/default/files/resources/UEFI_Spec_2_10_Aug29.pdf)
. By creating this header it gives us (the programmer) an easy way to interface with the computers underlying UEFI firmware and access it's functions and runtime services. I defined everything in the [uefi_structures.h](https://github.com/programmer838/Bootloader/blob/main/uefi_structures.h) file, it contains various data types, structs, function pointers and much more.

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

# Setting up the running and testing environment

Whilst developing this I utilised Qemu which is a free and open-source emulator to run my bootloader and test it. Below I will detail the setup process incase you want to develop your own bootloader:

1) Installing Qemu - ```sudo apt-get install qemu```
2) Installing OVMF - ```sudo apt-get install ovmf```, OVMF will provide our QEMU virtual machine with UEFI firmware
3) Create an empty disk image file - ```dd if=/dev/zero of=disk.img bs=1M count=200```, Whilst developing a UEFI bootloader we need to emulate something known as a EFI partition (also known as ESP partition), this is a special partition which contains the necessary files
our bootloader needs and is correctly structured for the computer to find and run the bootloader.
4) Format the disk with FAT32 filesystem -
5) Mount the disk
6) Structure the disk
7) Launch qemu


# Bootloader configuration file

The bootloader uses a configuration file which is reads to determine which kernel image and initramfs image to use:

- The configuration file should be named 'simple.cfg' and placed in the root of the EFI partition
- The first line of the configuration file should be the exact name of the kernel image
- The second line of the configuration file should be the exact name of the initramfs image





