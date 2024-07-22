## Chapter 04 Use sustemd manage service
* init process 
  * Early: SysV init, BSD init, LSB(Linux standard base) init
  * Now: systemd
### 4.1 Check if the Linux system uses systemd
* Check if the /run/systemd/system directory is exist
* stat /sbin/init (/sbin/init -> /lib/systemd/systemd)
* stat /proc/1/exe (/proc/1/exe -> /usr/lib/systemd/systemd)
* cat /proc/1/comm (systemd)
* ps -p 1 (1 ?  00:00:07 systemd)
### 4.2 Understanding PID 1
* ps -ef (PID 1 is /sbin/init splash)
* pstree -p (show process tree)
* pstree -sp {specific PID}
* ps -eo pid,user,stat,comm
### 4.3 Use systemctl list service
* systemctl # list all loaded service
* systemctl # list all service (active and unactive)
* systenctl list-unit-files # list all uint file
* systemctl list-unit-files --type=service # list all service file
* systemctl list-unit-files --type=service --state=enabled
* systemctl list-unit-files --type=service --state=disabled
* systemctl list-unit-files --type=service --state=static
* systemctl list-unit-files --type=service --state=masked (forbiden)
### 4.4 Check service status
* systemctl status cups.service
* systemctl status mariadb.service bluetooth.service lm-sensors.service
### 4.5 Start and stop service
* sudo systemctl start sshd.service
* sudo systemctl stop sshd.service
* sudo systemctl restart sshd.service
* sudo systemctl reload sshd.service  (like kill -HUP ?)
### 4.6 Enable\Disable service
* sudo systemctl enable sshd.service
* sudo systemctl disable sshd.service
* sudo systemctl mask sshd.service
* sudo systemctl unmask sshd.service
* Use --now to effective immediately
### 4.7 Stop abnormal process
* sudo systemctl kill mariadb
* sudo systemctl kill -9 mariadb
* sudo kill {PID}
* sudo kill -9 {PID}
### 4.8 Managing runlevels with systemd
* systemctl is-system-running (check if system running)
* systemctl get-default (target system CUI or GUI ?)
* runlevel (check current running level)
* sudo systemctl rescue (in rescue mode)
* sudo systemctl emergency (in emergency mode)
* sudo systemctl reboot
* sudo systemctl isolate multi-user.target (change target, don't modify default level)
* sudo systemctl set-default multi-user.target (change target, different default level)
* ls -l /lib/systemd/system/runlevel* (check all run level)
* systemctl list-dependencies graphical.target (list specific target's dependencies)
### 4.9 Diagnosis of the problem of slow system startup
* systemd-analyze blame
* systemd-analyze blame --user