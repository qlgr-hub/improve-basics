## Chapter 05 Manage User and Group
### 5.1 Check User's ids
* id command
  * -u # Effective UID
  * -g # Effective GID
  * -G # All GID
  * -n # Name
    * -un # Effective UID user name
    * -gn # Effective GID group name
    * -Gn # All GID group name
  * -r # Actual UID
* id {user name}
* sudo id -un (effective user name: root)
* sudo -u {user name} id -gn {print user's group name}
* ls -l /usr/bin/passwd
* run passwd and ps -a | grep passwd
* ps -eo pid,euser,ruser,rgroup | grep {passwd process PID}
### 5.2 Add normal user with useradd
* User-related configuration files
  * .bashrc .profile .bash_history .bash_logout
* useradd
  * sudo useradd test1
  * id test1
  * sudo ls -a /home/test1/ (After {sudo useradd test1}, the user's home directory will not be created)
  * -m # Create user's home directory
  * -U # Create a private group with the same name as the user
  * -G --groups # Add the user to multiple supplementary groups, separated by commas, The groups must exist.
  * -c --comment # Comments (Corresponds to the fields in /etc/passwd)
### 5.3 Add system user with useradd
* sudo useradd -rs /bin/false service1
  * -r # Indicates specifying an actual ID for the new system user.
  * -s # Indicates specifying an login shell
  * /bin/false # An exe (do nothing, block user login)
  * nobody # UID 65534 GID 65534 Fixed system user
### 5.4 Modify useradd's default settings
* /etc/default/useradd
* /etc/login.defs
* /etc/skel # Abbreviation of skeleton
* useradd -D # Check default settings
### 5.5 Customize Video\Music\Doc\Image\Download directory
* /etc/xdg/user-dirs.defaults
* New ~/.config/user-dirs.dirs and add name=value content
* Then use xdg-user-dirs-update apply it
* xdg-user-dirs-update --force # restore /etc/xdg/user-dirs.defaults to default
### 5.6 groupadd command
* /etc/group
* sudo groupadd musicians # Normal
* sudo groupadd -r service1 # System
### 5.7 usermod
* -a # Append
* -G # A group or groups
* sudo usermod -aG musicians test1
* sudo usermod -aG qlgr,test2 test1
### 5.8 Ubuntu's adduser
* A perl script
* config file path: /etc/adduser.conf
### 5.9 Add system user with adduser
* sudo adduser --system --no-create-home --group service1
### 5.10 addgroup command
* sudo addgroup composers # Normal
* sudo addgroup --system service1 # System
* config file path: /etc/adduser.conf
### 5.11 Check password file integrity
* sudo pwck
* sudo grpck
* sudo pwck -q
* sudo grpck -q
### 5.12 Disable User Account
* sudo passwd -l test2 (Temporary suspension)
* sudo passwd -u test2
* sudo usermod --expiredate 1 test2 (Completely disable)
* sudo usermod --expiredate -1 test2 (Restore enabled)
* Replace the 'x' in the password field with '*' in /etc/passwd (Disable)
* Replace the '*' in the password field with 'x' in /etc/passwd (Restore enabled)
### 5.13 userdel command
* sudo userdel test2
* sudo userdel -r test2 (For delete user's home directory and all files)
### 5.14 Ubuntu's deluser
* sudo deluser test2
* sudo deluser --remove-all-files --backup test2
  * --backup # Creates a compressed archive of user files in the current directory.
* sudo deluser --remove-all-files --backup-to /usr-backups test2
  * --backup-to # Creates a compressed archive of user files in the specific directory.
* config file path: /etc/deluser.conf
### 5.15 Ubuntu's delgroup
* sudo delgroup musicians
* sudo delgroup --only-if-empty musicians
* config file path: /etc/deluser.conf
### 5.16 Find and manage all user files
* sudo find / -uid 1001
* sudo find /etc -uid 1001
* sudo find /home -uid 1001
* sudo find /var -uid 1001
* sudo find / -gid 1001
* sudo find / -name test2
* sudo find / -group test2
* sudo find /{xxx} -uid 1003 -exec chown -v 1000 {} \;
* sudo find / -uid 1003 -exec cp -v {} /{destination path} \;
* sudo find / -uid 1003 -exec cp -vr {} /{destination path} \;
  * -v # verbose
  * -r # recursive
* sudo find / -uid 1003 -exec rm -v {} \;
* sudo find / -uid 1003 -exec rm -rv {} \;
  * -v # verbose
  * -r # recursive
* sudo find / -uid 1003 -exec mv {} /{destination path} \;
### 5.17 Change to root with su
* su -l # same as su, default includes -l
### 5.18 sudo command
* sudo visudo # Check and adit /etc/sudoers
* sudo awk 'BEGIN {system("/bin/bash")}' (Open a root permission shell)
* sudo less /etc/sysctl.conf
  * then enter !sh(Shell escapes) open a root permission shell
  * then use whoami confirm it
* root ALL=(ALL)ALL
  * root user fields (user, user alias, system group etc)
  * ALL= host fields (ALL means Anywhere Any Host)
  * (ALL) Optional user fields ((ALL) means Can execute commands like any other user)
  * ALL command fields (ALL means No restrictions)
### 5.19 Extend the sudo password timeout
* sudo visudo
  * Defaults timestamp_timeout=60
    * 60 means 60 minutes
    * 0 means ask for password every time you use it
    * nagative (e.g. -1) means password never expires
### 5.20 Create sudo configuration for each user
* Create a separate configuration for the user in /etc/sudoers.d/
  * cd /etc/sudoers.d/
  * sudo visudo -f {user name}
  * sudo ls /etc/sudoers.d/
### 5.21 Managing root password
* sudo su -l # change to root user
* reset root password with passwd command
### 5.22 Remove the requirement to enter the root password for sudo
* sudo visudo
  * Comment following two line content
    * Defaults targetpw
    * ALL ALL=(ALL) ALL