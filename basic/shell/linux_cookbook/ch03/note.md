## chapter 03 Linux start, stop, reboot and sleep modes.
* stat /sbin/shutdown # /sbin/shutdown -> /bin/systemctl
  * all old commands (/sbin/shutdown、/sbin/halt、/sbin/poweroff、/sbin/reboot) is symbolic link of /bin/systemctl
### 3.1 Use systemctl shutdown or reboot
* systemctl shutdown # stop the system and turn off the power
* systemctl poweroff # stop the system and turn off the power
* systemctl reboot # reboot system
* systemctl halt # stop the system without turning off the power
### 3.2 shutdown command
* shutdown -h now  # shut down immediately
* shutdown -h +10  # shut down after 10 minutes
* shutdown -c # cancel shut down
* shutdown -h +6 "bala bala" # shut down use custom prompt
* shutdown -h 22:15 # shut down at 10:15 PM
* shutdown -r # reboot
* shutdown # default is same as shutdown -h +1
* --help # help message
* -H, --halt # halt
* -P, --poweroff # poweroff
* -r, --reboot # reboot
* -k # send a 'wall(write to all logged-in users)' message, not shutting down  
* --no-wall # forbid 'wall' message
### 3.3 halt\reboot\poweroff command
* halt poweroff:
  * --help # help message
  * --halt # halt same as halt --halt
  * -p, --poweroff # poweroff same as poweroff --poweroff
  * --reboot # reboot
  * -f, --force # force shut down or force halt
  * -w, --wtmp-only # not shutting down, write record to /var/log/wtmp
  * -d, --no-wtmp # don't write wtmp record
### 3.4 systemctl's power saving mode
* suspend
  * Current session store to memory, hangs all hardware
  * Can be woken up by mouse or keyboard
* hibernate
  * Current session srore to disk, shut down device
  * Can be woken up by power button
* hybrid-sleep
  * Current session store to both memory and disk, turn off all hardware except memory
  * If memory is powered off, recover from disk, can be woken up by power button
* suspend-then-hibernate
  * First enters suspend mode, then enters hibernate mode after a specified time(set in the "HeibernateDelaySec=" feild in /etc/systemd/sleep.conf )
  * Can be woken up by power button
### 3.5 Ctrl-Alt-Delete reboot system
* CUI mode control with systemd
* GUI mode control with GUI shortcut key setting
* Linux without systemd control with /etc/inittab file
### 3.6 Disable\Enable\Config Ctrl-Alt-Delete by Linux terminal
* Disable and forbid
  * sudo systemctl disable ctrl-alt-del.target
    * Removed /etc/systemd/system/ctrl-alt-del.target
  * sudo systemctl mask ctrl-alt-del.target
    * Created symlink /etc/systemd/system/ctrl-alt-del.target -> /dev/null
* Unban and Enable to reboot
  * sudo systemctl unmask ctrl-alt-del.target
    * Removed /etc/systemd/system/ctrl-alt-del.target
  * sudo systemctl enable ctrl-alt-del.target
    * Created symlink /etc/systemd/system/ctrl-alt-del.target -> /lib/systemd/system/reboot.target
* Enable to poweroff
  * sudo systemctl disable ctrl-alt-del.target
    * Removed /etc/systemd/system/ctrl-alt-del.target
  * sudo ln -s /lib/systemd/system/poweroff.target /etc/systemd/system/ctrl-alt-del.target
* stat /lib/systemd/system/ctrl-alt-del.target (/lib/systemd/system/ctrl-alt-del.target -> reboot.target)
### 3.7 Implement scheduled shutdown using cron
* Change /etc/crontab (shut down at 22:30 20 minutes warning)
  * ``` # m  h  dom mon dow   user   command
       10 22   *   *   *    root   /sbin/shutdown -h +20
    ```
* Use sudo crontab -e edit and change /etc/crontab
### 3.8 Timed automatic wake-up system by UEFI
* change UEFI config
### 3.9 Timed automatic wake-up system by RTC
* use rtcwake command (supported by util-linux system package)
* cat /sys/power/state check system supported sleep mode (Linux without systemd use cat /proc/acpi/info command)
* sudo rtcwake -m {sleep mode} -s { seconds wait before restarting}
### 3.10 Timed automatic wake-up system by LAN
* Use ethtool check wether to support wake on LAN
  * sudo ethtool eno1 | grep -i wake-on
    * Supports Wake-on: pumbg
    * Wake-on: g # enabled
  * If supported but not enabled, can use following command to enable
    * sudo ethtool -s eno1 wol g
    * write following content to /etc/crontab for enable always
      * @reboot root /usr/bin/ethtool -s eno1 wol g
* Use wakeonlan command to wake-up
  * From another PC in the same subnet
    * /usr/bin/wakeonlan {destination device MAC address}
  * From another PC not in the same subnet
    * /usr/bin/wakeonlan -i {subnet broadcast address} {destination device MAC address}
### 3.11 Timed automatic wake-up system by WiFi
* Use wowlan
  * Use iw commonad show all wifi device 
    * iw dev
  * iw phy0 wowlan show # check wether to support wowlan
  * sudo iw phy0 wowlan enable magic-packet # to enable wowlan
  * Then use wakeonlan wake-up