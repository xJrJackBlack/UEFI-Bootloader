#!/bin/sh

make
sudo mount -o loop disk.img mnt
sudo cp main.efi mnt/EFI/BOOT/BOOTX64.EFI
sudo umount mnt
#qemu-system-x86_64 -bios /usr/share/OVMF/OVMF_CODE.fd -hda disk.img -hdb root.img -m 2500 -serial stdio -d int -no-reboot -no-shutdown -D log.txt 

#qemu-system-x86_64 -bios /usr/share/OVMF/OVMF_CODE.fd -hda disk.img -hdb root.img -m 2500 -serial stdio -d int -M smm=off -no-reboot -no-shutdown -D log.txt 


qemu-system-x86_64 \
    -bios /usr/share/OVMF/OVMF_CODE.fd \
    -hda disk.img \
    -hdb root.img \
    -m 2500 \
    -serial stdio \
    -d int \
    -M smm=off \
    -no-reboot \
    -no-shutdown \
    -D log.txt \
    -global isa-debugcon.iobase=0x402 \
    -debugcon file:debug-uefi.log

