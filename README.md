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

To begin writing a bootloader I needed to write a simple "Hello World!" program, at this point I had no clue what I was doing but eventually after researching and reading the UEFI specification and a few examples online I managed to write a hello world EFI program:


