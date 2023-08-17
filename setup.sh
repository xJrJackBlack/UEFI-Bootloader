#!/bin/sh

# Create the EFI disk image
dd if=/dev/zero of=disk.img bs=1M count=200
sudo mkfs.vfat -F 32 disk.img
sudo mount -o loop disk.img mnt
sudo touch mnt/simple.cfg
sudo echo "vmlinuz-5.10.0-23-amd64#initrd.img-5.10.0-23-amd64" >> mnt/simple.cfg
sudo mkdir -p mnt/EFI/BOOT
sudo cp vmlinuz-5.10.0-23-amd64 mnt/
sudo cp initrd.img-5.10.0-23-amd64 mnt/
sudo umount mnt

# Create the root filesystem disk image
dd if=/dev/zero of=root.img bs=1M count=600
sudo mkfs.ext4 root.img
sudo mount -o loop root.img root
sudo umount root
