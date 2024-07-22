## Chapter 08 Managing disk partitions with parted
* Partition Table
  * Ancient PC-DOS MBR (Master Boot Record)
  * GPT (GUID Partition Table)
* Boot System
  * BIOS (Basic Input Output System) 
  * UEFI (Unified Extensible Firmware Interface)
* Disk
  * Block: The smallest logical unit of storage on a disk
  * Sector: The smallest physical storage unit on a disk
  * A block can span multiple sectors, and a file can span multiple blocks.
### 8.1 Unmount part before use parted
* sudo umount /dev/sdc2
### 8.2 parted CUI mode
* sudo parted
* sudo parted /dev/sdb print devices
### 8.3 Check current disk part
* sudo parted
  * print devices
  * select /dev/sdb
  * print
  * quit
* sudo parted /dev/sda
  * print
  * print all
### 8.4 Creating a GPT partition on a non-bootable disk
* sudo umount /dev/sdc
* sudo parted /dev/sdc
  * mkpart "images" ext4 1MB 2004MB
  * mkpart "audio files" xfs 2005MB 100%
  * print
  * mkpart "images" ext4 2004MB 100%
### 8.5 Create a partition to install Linux
### 8.6 Delete partition
* sudo parted /dev/sdc
  * rm 2
  * p
### 8.7 Recover deleted partitions
* sudo parted /dev/sdc
  * rescue 2000MB 4010MB (specify start end position)
  * p
### 8.8 Extend partition
* sudo parted /dev/sdc
  * print free
  * resizepart 2 4010MB
  * p
### 8.9 Shrink partition
* Check current Occupancy
  * du -sh /xxx
* Run file system check
  * Ext4: sudo e2fsck -f /dev/sdc2
  * Btrfs: sudo btrfs check /dev/sdc2
  * FAT16/32: sudo fsck.vfat -v /dev/sdc2
* sudo parted /dev/sdc
  * resizepart 1 2000MB
  * p