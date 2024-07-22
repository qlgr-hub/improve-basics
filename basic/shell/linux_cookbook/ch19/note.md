## Chapter 19 SystemRescue
### 19.1 Make SystemRescue bootable device
* Get SystemRescue iso image
* dd
### 19.2 SystemRescue basic use
* Defaule CUI
* Use startx change to GUI (Xfce4)
### 19.3 Booting SystemRescue
* BIOS
* UEFI
### 19.4 SystemRescue boot options
### 19.5 Filesystem identification
* lsblk -f
### 19.6 Reset Linux root password
* mkdir /mnt/sdb2
* mount /dev/sdb2 /mnt/sdb2
* chroot /mnt/sdb2/ /bin/bash
* passwd root
### 19.7 Visit SystemRescue via ssh
* systemctl stop iptables.service
* passwd root
* ssh root@{ip}
### 19.8 Network transfer file via scp sshfs
* lsblk -f
* mkdir /mnt/sdb3
* mount /dev/sdb3 /mnt/sdb3
* ls /mnt/sdb3
* scp -r /mnt/sdb3/home/ test1@pc:
* cd /mnt/sdb3/home/
* scp -r file1.txt directory1 file2.txt test1@pc:rescue/
* mkdir /mnt/remote
* sshfs test1@pc:rescue/ /mnt/remote
* ls /mnt/remote
* fusermount -u remote # unmount
### 19.9 Modify GRUB with SystemRescue
* mkdir /mnt/linux
* mount /dev/sda2 /mn/linux
* mount -o bind /proc /mnt/linux/proc
* mount -o bind /dev /mnt/linux/dev
* mount -o bind /sys /mnt/linux/sys
* chroot /mnt/linux /bin/bash
* mount /dev/sda1 /boot/
* grub-install /dev/sda
### 19.10 Reset Windows password
* mkdir /mnt/windows
* mount /dev/sda2
* cd /mnt/windows/Windows/System32/config
* chntpw -l SAM  # change NT password
* chntpw -u Administrator SAM
### 19.11 Rescue a Faulty Hard Drive with GNU ddrescue
* ddrescue -f -n /dev/sdb1 /dev/sdc1 ddlogfile
* ddrescue -d -f -r3 /dev/sdb1 /dev/sdc1 ddlogfile
* e2fsck -vfp /dev/sdc1
* mkdir /mnt/sdc1-copy
* mount -o ro /dev/sdc1 /mnt/sdc1-copy
* ddrescue not dd-rescue
### 19.12 SystemRescue's partition and disk management
* lsblk -p -o NAME,FSTYPE,LABEL
* parted GParted
### 19.13 Create a data partition on the SystemRescue USB drive
* syslinux-utils, install-mbr
* isohybrid --partok systemrescuecd-8.01-amd64.iso
* sudo parted /dev/sdc
  * mkpart "sysrec" fat32 1MB 2000MB
  * set 1 boot
  * mkpart "data" xfs 2001MB 4000MB
  * q
* sudo mkfs.fat -F 32 -n SYSRESCUE /dev/sdc1
* sudo mkfs.xfs -l data /dev/sdc2
* sudo dd status=progress if=systemrescuecd-8.01-amd64.iso of=/dev/sdc1
* sudo install-mbr /dev/sdc
* sudo if=/usr/share/syslinux/mbr.bin of=/dev/sdc
### 19.14 Save SystemRescue changes
* lsblk -p (save to /run/archiso/cowspace/persistent_RESCUE800)