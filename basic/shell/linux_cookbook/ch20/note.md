## Chapter 20 Troubleshooting Linux Systems
### 20.1 Use log
* dmesg | less
* dmesg | grep -w sd # storage
* dmesg -T | less # human readable
* dmesg -l err,warn # filter
* sudo grep -ir graphicsmagick /var/log # find package from /var/log
* journalctl
* journalctl -r 
* journalctl -r | less
* journalctl -ex | less
* sudo journalctl -u mariadb.service
* journalctl -u mariadb.service -S today
* journalctl -u ssh.service -S '1 week ago'
* journalctl -u libvirtd.service -S '2021-03-05'
* journalctl -u httpd.service -S '2021-03-05' -u '2021-03-09'
* journalctl -u nginx.service -S '2 hours ago'
* journalctl -u httpd.service -S '2021-03-05 13:15:00' -U now
* journalctl -S '1h ago' -U '5 min ago' -o with-unit
* journalctl -b -n 50 -u httpd.service
* journalctl -b -2 -u httpd.service
* journalctl --list-boots
* journalctl -b -1 -p "crit" -u nginx.service
* journalctl -b -3 -p "crit".."warning"
* journalctl -n 10 -u mariadb.service -f
* journalctl -b -1 | grep madmax
### 20.2 Config journald
* systemctl status systemd-journald.service
* sudo mkdir /var/log/journal
* sudo chgrp /var/log/journal/ systemd-journald
### 20.3 Using systemd to build a log server
* install systemd-journald-remote
* config /etc/systemd/journal-remote.conf
* sudo chmod -R 0755 /etc/pki/joutnald
* sudo chmod 0440 /etc/pki/journald/log-server.key
* sudo chgrp systemd-journald-remote /etc/pki/journald/log-server.key
* sudo systemctl enable --now systemd-journald-remote.socket
* sudo systemctl enable --now systemd-journald-remote.service
* sudo firewall-cmd --zone=internal --add-port=19532/tcp
* sudo firewall-cmd --zone=internal --add-port=80/tcp
* sudo firewall-cmd --runime-to-permanent
* sudo firewall-cmd --reload
* sudo useradd -r -d /run/systemd -M -s /usr/sbin/nologin -U systemd-journald-upload
* sudo chmod -R 0755 /etc/pki/joutnald
* sudo chmod 0440 /etc/pki/journald/client.key
* sudo systemctl restart systemd-journald-upload.service
* sudo ls -la /var/log/journal/remote/
* sudo logger -p syslog.debug "Hello, I am client! Do you hear me?"
### 20.4 etect temperature/fan/voltage with lm-sensor
* Ubuntu lm-sensors
* sudo sensors-detect
* sudo systemctl restart systemd-modules-load.service
* sensors
* watch -d sensors
* watch -d -n 10 sensors
* grep -i nct6775 config-5.8.0-45-generic
* lsmod | grep nct6775
### 20.5 Add lm-sensors GUI
* smartmontools
* hddtemp
* Psensors
### 20.6 Detect disk with smartmontools
* systemctl status smartd.service
* sudo smartctl -i /dev/sda
* sudo smartctl -s on /dev/sda
* sudo smartctl -s off /dev/sda
* sudo smartctl -x /dev/sda
* sudo smartctl -H /dev/sda
* sudo smartctl -l error /dev/sda
* sudo smartctl -t long /dev/sda
* sudo smartctl -l selftest /dev/sda
* sudo update-smart-drivedb
### 20.7 Send email report with smartmontools
* echo "bala bala ..." | mail -s "Message subject" root@localhost
* mail
* systemctl status smartd.service
* systemctl status postfix.service
* sudo systemctl enable --now smartd.service
* sudo systemctl enable --now postfix.service
* Modify /etc/smartd.conf or /etc/smartmontools/smartd.conf
* sudo systemctl reload smartd.service
### 20.8 top
### 20.9 top process
* top -p {PID1, PID2, ...}
### 20.10 Unlocking a stuck GUI
* Ctrl-Alt-F2
### 20.11 Troubleshooting hardware