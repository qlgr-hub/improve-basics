## chapter 01 Install Linux
### 1.1 BIOS/UEFI
### 1.2 Download Linux image
* Verify the downloaded Ubuntu image
  * echo "[shacode] *xxx.iso" | shasum -a 256 --check
### 1.3 Creating a Linux installation u disk with UNetbootin
* Same tools: USB Creator、ISO Image Writer、GNOME MultiWriter、Rufus
* Manage multiple Linux boot files on u disk
  * Ventoy
### 1.4 Creating a Linux installation DVD with k3b
### 1.5 Creating bootable CD/DVD with wodim
* wodim dev=/dev/cdrom -v xxx.iso
### 1.6 Creating a Linux installation u disk with dd 
* Check u disk device name
  * lsblk -o NAME,FSTYPE,LABEL,MOUNTPOINT
* Make installation u disk
  * sudo dd status=progress if=xxx.iso of=/dev/xxx
### 1.7 Simple installation of Ubuntu
### 1.8 Custom partitions (erase all existing partitions)
* /boot : 500M
* / : Usually 30GB is more than enough, For Btrfs file syetem best 60GB
* /home : In sparate patition or disk, isolate from root file system
* /var、/tmp : Usually 20GB per partition, for busy server need more space; Prepared for running various processes
* /swap : size is set to same as memory
### 1.9 Keep existing patitions (keep some partitions, change some partitions)
### 1.10 Custom packages
### 1.11 Multi-boot Linux
### 1.12 Linux/Windows dual booting (I like GRUB, Linux First mode)
### 1.13 Recover Windows8/10 OEM Product Key
* Use linux or SystemRescue (If Linux is installed on device) 
  * sudo cat /sys/firmware/acpi/tables/MSDM
* Use Windows command:
  * wmic path softwarelicensingservice get OA3xOriginalProductKey
### 1.14 Mount the ISO image to Linux
* Make a mount point
  * mkdir xxx
* Mount xxx.iso to new mount point (xxx)
  * sudo mount -o loop xxx.iso xxx 
* Unmount
  * sudo umount xxx


