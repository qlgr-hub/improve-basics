## Chapter 11 Create and manage filesystem
* File system (Commonly used in linux)
  * Ext4
  * XFS
  * Btrfs
  * FAT16/32
  * exFAT
* Specific systems file system
  * NTFS Windows
  * HFS/HFS+/APFS Apple
* Dedicated file system
  * UBIFS and JFFS2 (For CF card)
  * SquashFS\HDFS\CephFS\GlusterFS (Compressed file system for distributed computing)
### 11.1 List system supported filesystem
* cat /proc/filesystems
### 11.2 Identify current filesystem
* lsblk -o NAME,FSTYPE
* lsblk -o NAME,FSTYPE,LABEL,FSSIZE,FSUSE%，MOUNTPOINT
* lsblk --help
### 11.3 Resize the file system
* parted GParted
### 11.4 Delete filesystem
* lsblk -f  Check filesystem info
* umount /xxx Unmount filesystem partition
* sudo parted /dev/sdb
  * print
  * rm 1
  * p
### 11.5 Use new filesystem
* sudo mkdir -p /mnt/madmax/newfs
* sudo mount /dev/sdb1 /mnt/madmax/newfs
* sudo chown -R madmax:madmax /mnt/madmax/newfs
* sudo chmod -R 0755 /mnt/madmax/newfs
* Related commands
  * tree
  * stat
  * mount
  * mountpoint
### 11.6 Automatically mount file systems
* Write following content to /etc/fstab
* ``` #<file system>   <mount point>     <type>   <options>       <dump>    <pass>
      LABEL=xfs-ehd    /mnt/madmax/newfs   xfs    defaults,user     0         2
* sudo findmnt --verbose --verify  Check new config
* sudo mount -a Mount new config
* /etc/fstab
  * device UUID or filesystem identifier (don't use /dev beginning name)
  * mountpoint filesystem mount path
  * type filesystem type (e.g. xfs ext4 btrfs)
  * options mount options
    * defaults (rw suid dev exec user users auto noauto nouser async ro noatime gid)
  * dump backup
  * pass system first check filesystem
### 11.7 Create Ext4 filesystem
* df -Th /media/test1/stuff/
* sudo umount /media/test1/stuff
* sudo mkfs.ext4 -L 'mylabel' /dev/sdb1
* some default value config in /etc/mke2fs.conf
### 11.8 Config Ext4 log mode
* dmesg | grep sdb1
* sudo tune2fs -o journal_data /dev/sdb1
* dmesg | grep sdb1
### 11.9 Find Ext4 filesystem's log
* sudo dumpe2fs -h /dev/sda1 | grep -i uuid # Check UUID
* lsblk -f | grep {Journal UUID} # Check filesystem UUID via journal UUID
* sudo dumpe2fs -h /dev/sda2 | grep UUID # Check only filesystem UUID
### 11.10 Improving Ext4 performance with external journaling
* sudo parted
  * select /dev/sdb
  * mkpart "journal1" ext4 1600GB 1800GB
  * select /dev/sda
  * mkpart "ext4fs" ext4 1MB 500GB
* sudo tune2fs -l /dev/sda1 | grep -i 'block size'
* sudo mke2fs -b 4096 -O journal_dev /dev/sdb5
* sudo mkfs.ext4 -b 4096 -J device=/dev/sdb5 /dev/sda1
* sudo tune2fs -O ^has_journal /dev/sda1
* sudo tune2fs -b 4096 -J device=/dev/sdb5 /dev/sda1
### 11.11 Free Ext4 existing free space
* sudo tune2fs -m 1 /dev/sda1
* sudo tune2fs -l /dev/sda1 | grep -i 'block size'
* sudo tune2fs -m .25 /dev/sda1
* sudo tune2fs -r 25000 /dev/sda1
* sudo tune2fs -l /dev/sda1 | grep -i 'reserved block'
* sudo dumpe2fs -h /dev/sda1
### 11.12 Create XFS filesystem
* sudo apt install xfsprogs
* sudo parted /dev/sda mkpart testxfs 1MB 500GB
* sudo mkfs.xfs -L xfstest /dev/sda1
* lsblk -f | grep -w sda1
* sudo mkdir /mnt/xfstest
* sudo mount /dev/sda1 /mnt/cfstest
* sudo chown -R test1:test1 /mnt/cfstest
* sudo chmod -R -755 /mnt/xfstest
### 11.13 Resize XFS filesystem
* sudo parted /dev/sdb
  * p free
  * resizepart 2
  * q
* sudo xfs_growfs /media/test1/xfs
### 11.14 Create exFAT filesystem
* sudo mkfs.exfat /dev/sdc1
* sudo exfatlabel /dev/sdc2 exfatfs
* lsblk -f
### 11.15 Create FAT16/32 filesystem
* need dosfstools package
* sudo parted /dev/sdb
  * mkpart
  * fat32
  * {start}
  * {end}
  * print
  * q
* sudo mkfs.fat -F 32 -n fat32test /dev/sdb2
* lsblk -f /dev/sdb
### 11.16 Create Btrfs filesystem
* with GParted