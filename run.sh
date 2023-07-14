#!/bin/sh

sudo mount -o loop disk.img mnt
sudo cp main.efi mnt/
sudo umount mnt
qemu-system-x86_64 -bios /usr/share/OVMF/OVMF_CODE.fd -hda disk.img
