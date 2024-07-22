## Chapter 17 Sync time with ntpd/chrony/timesyncd
* nptd/chrony NTP server
* timesyncd SNTP (just client)
### 17.1 Find NTP client on Linux
* ps ax | grep ntp
* ps ax | grep chrony
* ps ax | grep timesyncd
* timedatectl status
* systemctl status systemd-timesyncd
### 17.2 Sync time with timesyncd
* systemctl status systemd-timesyncd
* timedatectl set-ntp true
* systemctl status systemd-timesyncd
* systemctl start systemd-timesyncd
* timedatectl status
* /etc/systemd/timesyncd.conf
  * ```
        [Time]
        NTP=0.north-america.pool.ntp.org 1.north-america.pool.ntp.org 2.north-america.pool.ntp.org
        # FallbackNTP=ntp.ubuntu.com
        # RootDistanceMaxSec=5
        # PollIntervalMinSec=32
        # PollIntervalMaxSec=2048
### 17.3 Manually set time with timedatectl
* timedatectl set-time "2020-10-04 19:30:00"
* sudo systemctk stop systemd-timesyncd
* timedatectl set-ntp false
* timedatectl set-time "2020-10-04 19:30:00"
* timedatectl status
### 17.4 Set up chrony as NTP client
* sudo systemctl disable systemd-timesyncd
* sudo systemctl stop systemd-timesyncd
* sudo systemctl enable chrony
* chornyc activity
* /etc/chrony/chrony.conf
  * ```
        pool 0.ubuntu.pool.ntp.org iburst
        pool 1.ubuntu.pool.ntp.org iburst
        pool 2.ubuntu.pool.ntp.org iburst
        server ntp.domain.lan iburst prefer
* sudo systemctl status chrony
* sudo systemctl restart chrony
### 17.5 Set up chrony as LAN datetime server
* /etc/chrony/chrony.conf
  * ```
        pool 0.ubuntu.pool.ntp.org iburst
        pool 1.ubuntu.pool.ntp.org iburst
        pool 2.ubuntu.pool.ntp.org iburst
        
        local stratum 10
        allow 192.168.0.0/16
        allow 2001:db8::/56

        driftfile /var/lib/chrony/chrony.drift
        maxupdateskew 100.0
        rtcsync
        logdir /var/log/chrony
        log measurements statistics tracking
        leapsectz right/UTC
        makestep 1 3

        server ntp.domain.lan iburst prefer
### 17.6 Check chrony statistic data
* chronyc tracking
* chronyc sources
* chronyc sources -v
### 17.7 Set up ntpd as NTP client
* ps ax | grep -w ntpd
* systemctl start ntpd
* /etc/ntp.conf
  * ```
        server ntp.domain.lan iburst prefer
        pool 0.ubuntu.pool.ntp.org iburst
* systemctl restart ntpd
* sudo /etc/inti.d/ntp restart
* ntpq -p
### 17.8 Set up ntpd as datetime server
* Modify /etc/ntp.conf
### 17.9 Managing time zone with timedatectl
* timedatectl | grep -i "time zone"
* timedatectl list-timezones
* timedatectl list-timezones | grep -i berlin
* sudo timedatectl set-timezone Europe/Berlin
### 17.10 Managing time zone without timedatectl
* date
* ls -l /etc/localtime
* ls /usr/share/zoneinfo
* ls /usr/share/zoneinfo/Europe
* sudo ln -sf /usr/share/zoneinfo/Europe/Madrid /etc/localtime
* php -r 'print_r(timezone_identifiers_list())' (need php-cli package)