## Chapter 06 Managing files and directories
* Three types of ownership (owner, group, other)
* Six permission modes (read, write, execute, sticky bit, setuid, setgid)
* stat --format=%a:%A:%U:%G /etc (755:drwxr-xr-x:root:root)
### 6.1 Create file and directory
* mkdir -v presentations (Relative path)
  * -v verbose
* mkdir -p presentations/2020/august (Relative path)
  * -p parent
* mkdir -v /charts (Absolute path)
* mkdir -m 0700 /home/test2/dog-memes
  * -m 0700 permission of new directory
* touch newfile.txt
* tree -L 1 /
  * show file tree
  * -L level
### 6.2 Quickly create a batch of test files
* touch newfile.txt
* touch file{00..99}
* touch test{00..99}.doc
* touch {00..99}test.doc
* yes This is a test file | head -c 500MB > testfile.txt
* ``` 
    for x in {01..100};
        do yes This is a test file | head -c 1MB > $x-testfile.txt;
    done
* ls -v
  * -v Numbers in file names are sorted as integers
### 6.3 Relative path and Absolute path
* ls --group-directories-first
* pwd
### 6.4 Delete file and derectories
* rm -v aria.ogg
  * -v verbose
* rm -iv intermezzo.wav
  * -i Give confirmation prompt
* rm -rvi reheaesals
  * -r revursive
* rm -rv reheaesals/2020/jan
* rm -rv reheaesals
* rm -v *.txt
* rm -v aria*
* rm -f *.txt
  * -f force
### 6.5 Copy\Move\Rename file and directories
* cp -v aria.ogg solo.flac ~/songs2/
  * -v verbose
* cp -rv ~/music/song2 /shared/archives
  * -r recursive
* cp -rv --parents test2/music/songs2/ shows/
  * --parents Keep the parent path content without copying
* mv -v aria.ogg solo.flac ~/songs2/
* mv -v ~/songs2/ ~/music/
* cp command:
  * -a --archive Preserve all file attributes
  * -i --interactive Give confirmation prompt
  * -u --update Overwrite an existing destination file only if the source file is newer
* mv command:
  * -i --interactive Give confirmation prompt
  * -n --no-clobber Prevent overwriting of target files
  * -u --update Overwrite an existing destination file only if the source file is newer, or no that file
### 6.6 Set file permission with chmod (Octal notation)
* chmod -v 0600 file.txt
  * -v verbose
* chmod 0666 file.txt
* chmod -v 0644 file.txt
* chmod 0660 file.txt
* chmod 0750 bachup.sh
### 6.7 Set directory permission with chmod (Octal notation)
* sudo mkdir /shared
* chmod 0755 /shared
* chmod -R 0755 /shared
  * -R recursive
* chmod 0700 /shared
* chmod 0770 /shared
### 6.8 Using special modes (Octal notation)
* Special modes: sticky bit, setuid, setgid
  * sticky bit: chmod -v 1770 /home/test2/shared
  * setuid: chmod -v 4750 backup-script
    * stat --format=%a:%A:%U:%G /usr/bin/passwd
  * setgid: chmod -v 2770 /home/test2/shared
  * Sticky bit prevent other users from moving, renaming or deleting other people's files
    * stat --format=%a:%A:%U:%G /tmp
### 6.9 Delete special modes (Octal notation)
* chmod -v 00770 backup.sh
* chmod -v =770 backup.sh
### 6.10 Set permission with chmod (Symbolic notation)
* stat --format=%a:%A:%U:%G file.txt
* chmod -v g+w,o+w file.txt
  * + means add permission
* chmod -v g-w,o-w file.txt
  * - means delete permission
* chmod -v u=rw,g=rw,o-r file.txt
  * = means append permission (Overwrite existing)
* chmod -v u+x file.txt
* chmod -v u=rw,g=rw,o=r file.txt
  * r means read
  * w means write
  * x means execute
  * u means user
  * g means group
  * o means other
  * a means all
### 6.11 Set special modes with chmod (Symbolic notation)
* chmod o+t /shared/stickydir
* chmod -v g+s /shared
* chmod -v u+s backup-script
  * t means sticky bit
  * u+s means setuid
  * g+s means setgid
### 6.12 Batch setting permissions with chmod
* chmod -v 444 file1 file2 file3
  * -v verbose
* chmod -vR 755 /shared
  * -R recursive
* chmod -v 644 *.txt
* chmod -v 644 abcd*
* find . -type f -exec chmod -v 660 {} \;
* sudo find / -user test2 -exec chmod -v 660 {} \;
* sudo find / -user 1003 -exec chmod -v 660 {} \;
### 6.13 Set file and directories owner with chown
* sudo chown -v test2: song.wav
  * -v verbose
  * format user:group
* sudo chown -v :test2 song.wav
* sudo chown {user}:{group} song.wav
### 6.14 Batch setting owner with chown
* sudo chown -v test2:test2 file1 file2 file3
* sudo chowm -v :test2 *.txt
* sudo chown -Rv --from test2 test1 /shared/compositions
  * -R recursive
* sudo chown -Rv --from 1001 1003 /shared/compositions
  * --from Specify the current owner
* sudo find / -user test1 -exec chown -v test2 {} \;
* sudo find / -user 1003 -exec chown -v 1001 {} \;
### 6.15 Set default permission with umask
* umask (Octal notation)
* umask -S (Symbolic notation)
* umask 0022 (Modify current session default mask)
* set umask 0022 in ~/.bashrc (Modify current user's default mask)
* New user's default umask can be set in /etc/login.defs
  * UMASK 0022
* umask is bash builtin comman not a standalone executable
### 6.16 Create file and directories shortcuts
* ln -s /files/userstuff stuff (Symbolic link)
* ln /files/config1.txt myconf.txt (Hard link, a copy of file)
* find /etc -xdev -samefile config3.txt
  * Find all hard links associated with config3.txt
* df -i /dev/sda4
  * Count the number of inodes in the file system
### 6.17 Hidden files and directories
* You can make a file or directory hidden by preceding it with a period (.)