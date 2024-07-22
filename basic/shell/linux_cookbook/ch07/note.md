## Chapter 07 Backing up and restore system
* cp (GNU coreutils package)
* rsync
### 7.1 Confirm backup content
* /boot/grub
* /etc
* /home
* /mnt
* /opt
* /root
* /srv
* /tmp
* /var
* /proc /sys /dev is In-memory pseudo-file system, no need to back up
* /media Mount on removable storage, no need to back up
### 7.2 Confirm restore content
* Don't restore /etc/fstab
* Some configuration files in /home /etc need attention when restoring
### 7.3 The simplest local backup
* copy content with cp (from local storage to USB disk)
### 7.4 Automatic simple local backup
* Combine crontab cp plan backup
* cp -auv Pictures/cat-desk.jpg Pictures/cat-chair.png ~/cat-pics /media/test1/2tbdisk/backups/
* cp -auv ~ /media/test1/2tbdisk/backups/
* cp -auv /home/test1/* /media/test1/2tbdisk/backups/
* crontab -e 
* ```# m  h  dom mon dow   command
   30 22   *   *   *    /bin/cp -au /home/test1 /media/test1/2tbdosk/backups/
* cp command
  * -x --one-file-system Prevent copying of other filesystem's contents
  * -R -r recursive
* lsblk check USB disk path
### 7.5 Local backup with rsync
* rsync -av ~ /media/test1/2tbdisk/
* rsync -av ~/arias ~/overtures /media/test1/2tbdisk/test1/
* rsync -av /media/test1/2tbdisk/test1/arias /home/test1/
* rsync -av --dry-run ~/Music/scores ~/Music/woodwinds /media/test1/2tbdisk/test1/
* rsync -av --delete /home/test1 /media/test1/2tbdisk/
* rsync command
  * -a --archive Preserve file attributes
  * -v --verbose
  * -q --quiet Omit non-error messages
  * --progress Displays transfer information for each file
  * -A --als Preserve ACL
  * -X --xattrs Preserve extended file attributes
### 7.6 Remote transfer file with rsync over SSH
* rsync -av ~/Music/arias {user name}@{host name}:songs/
* rsync -av ~/Music/arias {user name}@{FQDN}:songs/
* rsync -av {user name}@{host name}:songs/ ~/Music/arias
* rsync command
  * -e (e.g. ssh)
  * --partial Resume upload from breakpoint
  * -h --human-reabable 
  * --log-file= log directory
* rsync --partial --progess --log-file=/home/test1/rsynclog.txt -hav ~/Music/arias {user name}@{host name}/backups/
### 7.7 Automatic rsync backup
* crontab -e
* ``` # m  h  dom mon dow  user  command
       00 22   *   *   *   root  /usr/bin/rsync -a /etc server1:/system-backups 
### 7.8 Exclude files from backup
* rsync -av --exclude=lho-perduta.wav ~/Music/arias /media/test1/2tbdisk/test1/Music/
* rsync -av --exclude=arias/lho-perduta.wav ~/Music/arias /media/test1/2tbdisk/test1/Music/
* rsync -av --exclude={'arias/lho-perduta.wav','non-mi-dir.wav','un-bel-di-vedremo.flac'} ~/Music/arias /media/test1/2tbdisk/test1/Music/
* rsync -av --exclude={'soprano/','tenor/','non-mi-dir.wav'} ~/Music/arias /media/test1/2tbdisk/test1/Music/
### 7.9 Backup specific file
* rsync -av --include=*/ --include=lho-perduta.wav --exclude='\*' ~/Music/arias /media/test1/2tbdisk/test1/Music/
* rsync -av --include=*/ --include={'lho-perduta.wav','non-mi-dir.wav','un-bel-di-vedremo.flac'} --exclude='\*' ~/Music/arias /media/test1/2tbdisk/test1/Music/
* rsync -av --include=*/ --include=soprano/lho-perduta.wav --exclude='\*' ~/Music/arias /media/test1/2tbdisk/test1/Music/
* rsync -avm --include=*/ --include=soprano/lho-perduta.wav --exclude='\*' ~/Music/arias /media/test1/2tbdisk/test1/Music/
  * -m --prune-empty-dirs Prevent copying of empty directories
  * --include=*/ Traverse the entire source directory
  * --exclude='*' Exclude everything except "--include"
### 7.10 List file management backup items
* Create a text file listing the files that need to be backed up
* rsync -av ~ --files-from ~/include-list.txt {user name}@{host name}:/backups/
### 7.11 Manage inclusions and exclusions with exclusion lists
* rsync -av ~ --exclude-from=/home/test1/exclude-list.txt /media/test1/2tbdisk/
* file format:
  * \+ Beginning line is include
  * \- Beginning line is exclude
  * \# Beginning line is comment
### 7.12 Limiting rsync bandwidth
* --bwlimit=512 (Only accept KB units)
### 7.13 Building an rsyncd backup server
* sudo systemctl start rsyncd.service or sudo rsync --daemon
* rsync server1:: or rsync {ip address}:: to check server status
* rsync -av ~/drawings server1::{backup_dir}
* rsync server1::{backup_dir}/drawings/ to check sync
* rsync -av server1::{backup_dir}/drawings ~/download
### 7.14 rsyncd config
* config file path: /etc/rsyncd.conf
### 7.15 Create rsyncd MOTD
* Message Of The Day: /etc/rsync-motd