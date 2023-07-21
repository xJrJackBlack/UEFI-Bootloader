# Unified Extensible Firmware Interface (UEFI) Linux Bootloader
A UEFI Bootloader made for Linux, below i detail the development process.


# Tools and Resources

I was going to initially use GNU-EFI and GCC for this project however i decided to use the following tools for more flexibility:

- Clang
- LLVM Linker
- QEMU
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

1) Installing QEMU - ```sudo apt-get install qemu```
2) Installing OVMF - ```sudo apt-get install ovmf```, OVMF will provide our QEMU virtual machine with UEFI firmware
3) Create an empty disk image file - ```dd if=/dev/zero of=disk.img bs=1M count=200```, Whilst developing a UEFI bootloader we need to emulate something known as a EFI partition (also known as ESP partition), this is a special partition which contains the necessary files
our bootloader needs and is correctly structured for the computer to find and run the bootloader.
4) Format the disk with FAT32 filesystem - ```sudo mkfs.vfat -F 32 disk.img```
5) Mount the disk - ```sudo mount -o loop disk.img mnt```
6) Structure the disk - ```cd mnt``` - ```touch simple.cfg``` - ```mkdir -p EFI/BOOT```
7) Launch QEMU ```qemu-system-x86_64 -bios /usr/share/OVMF/OVMF_CODE.fd -hda disk.img```


# Bootloader configuration file

The bootloader uses a configuration file which is reads to determine which kernel image and initrd image to use:

- The configuration file should be named 'simple.cfg' and placed in the root of the EFI partition
- The configuration file should contain a single line in the following format:
```LinuxKernelImageName#InitRDFileName```
- ```LinuxKernelImageName``` should be the name of the kernel image
- Next it should be followed by a single hash ```#```
- ```InitRDFileName``` should be the name of the initrd file name


# Steps for booting the kernel

1) **Load the real-mode code**: The real-mode code is a part of the kernel image which contains code that runs in real mode. In the Linux kernel the real-mode code is made up of the boot-sector portion and the setup-code portion. The size of the boot-sector portion is always 512 bytes. The size of the setup-code portion can be obtained by reading at offset 0x1f1 into the kernel image, which gives the size of the setup-code in 512 byte sectors. If the value read is 0, then  change it to 4. Then finally multiply this by 512. Using this information we can calculate the size of the real-mode code by adding both the boot-sector portion size and the setup-code portion size.






