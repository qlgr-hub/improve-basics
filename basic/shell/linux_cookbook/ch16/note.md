## Chapter 16 Manage local Name service with Dnsmasq & hosts
* Dnsmasq: LAN DNS & DHCP server (also support BOOTP PXE TFTP)
* Dnsmasq works well with /etc/hosts
### 16.1 Resolve host name via /etc/hosts
* ip addr show dev lo
* hostname
* hostname -f
* hostname -d
### 16.2 Testing and blocking spam sites via /etc/host
* Mapping spam sites to invalid IPs
### 16.3 Find all DNS & DHCP servers on the network
* sudo nmap --open 192.168.1.0/24 # Check all TCP port
* sudo nmap -sU -p 53,67 192.168.1.0/24 # Check DNS (UDP 53), DHCP (UDP 67)
* sudo nmap -sU -sT 192.168.1.0/24 # Check all opening TCP & UDP ports
### 16.4 Install Dnsmasq
* dnsmasq package
* systemctl status dnsmasq.service
* systemctl stop dnsmasq.service
* nmcli connction shwo --active
* nmcli con mod "1wired"
* systemctl restart NetworkManager.service
* systemctl status system-resolved.service
### 16.5 Avoid conflicts between NetworkManager, system-resolved  and Dnsmasq
* systemctl status system-resolved.service
* systemctl stop system-resolved.service
* systemctl disable system-resolved.service
* ls -l /etc/resolv.conf
* sudo rm /etc/resolv.conf
* sudo touch /etc/resolv.conf
* sudo nano /etc/NetworkManager/NetworkManager.conf
    *  ```
        [main]
        dns=none
* /etc/resolv.conf
  * ```
        search sqr3l.nut
        nameserver 127.0.0.1
        nameserver ::1
### 16.6 Configure Dnsmasq as LAN DNS server
* /etc/hosts
  * ```
        127.0.0.1 localhost
        ::1 localhost ip6-localhost ip6-loopback
        192.168.43.81 dns-serever
        192.168.43.82 backups
        192.168.43.83 https
* sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.old
* sudo nano /etc/dnsmasq.conf
  * ```
        # global options
        resolv-file=/etc/resolv.conf
        domain-needed
        dogus-priv
        expand-hosts
        domain=sqr3l.nut
        local=/sqr3l.nut/
        listen-address=127.0.0.1
        listen-address=192.168.43.81

        # upstream name servers
        server=208.67.222.222
        server=208.67.220.220
* dnsmasq --test
* sudo systemctl start dnsmasq.service
* sudo systemctl status dnsmasq.service
* nslookup dns-server
* nslookup dns-server.sqr3l.nut
* nslookup 192.168.43.81
* sudo ss -lp "sport = :domain"
  * socket statistics, in iproute2 package
### 16.7 Modify firewalld config to allow client access DNS & DHCP server
* sudo firewall-cmd --permanent --add-service=\{dns,dhcp\}
### 16.8 Test Dnsmasq server with client
* dig @192.168.1.10 oreilly.com
* dig @dns-server oreilly.com
* dig @dns-server.sqr3l.nut oreilly.com
### 16.9 Manage DHCP with Dnsmasq
* /etc/dnsmasq.conf
  * ```
        # DHCP range
        dhcp-range=192.168.1.25,192.168.1.75,12h
        dhcp-lease-max=25
* sudo systemctl restart dnsmasq.service
* nmcli con show --active
* nmcli con show 1net | grep ipv..method
* sudo nmcli con down 1net
* sudo nmcli con up 1net
* journalctl -ru dnsmasq
* sudo dhclient -v
### 16.10 Publish important services via DHCP
* /etc/dnsmasq.conf
  * ```
        dhcp-option=3,192.168.1.1   # gateway
        dhcp-option=6,192.168.1.10  # DNS
        dhcp-option=42,192.168.1.11 # NTP
* dnsmasq --help dhcp
### 16.11 Create subnet DHCP range
* /etc/dnsmasq.conf
  * ```
        dhcp-range=zone1,192.168.50.20,192.168.50.120
        dhcp-range=zone2,192.168.60.20,192.168.60.50,24h
        dhcp-option=zone1,3,192.168.50.1   # gateway
        dhcp-option=zone2,3,192.168.60.1   # gateway
        dhcp-option=zone1,6,192.168.1.10   # DNS
        dhcp-option=zone2,6,192.168.1.10   # DNS
        dhcp-option=zone1,42,192.168.50.15 # NTP
        dhcp-option=zone2,42,192.168.60.15 # NTP
### 16.12 Assigning static IP via DHCP
* /etc/dnsmasq.conf
  * ```
        dhcp-host=server2,192.168.3.45
### 16.13 Automatically add DHCP clients to DNS
* /etc/dhcp/dhclient.conf
  * ```
        send host-name = gethostname()
        # or send host-name = myhostname
* nmcli connection show --active
* nmcli connection shwo wifi1 | grep send-hostname
* nmcli con mod wifi1 ipv4.dhcp-send-hostname yes
* nmcli con mod wifi1 ipv6.dhcp-send-hostname yes
* sudo nmcli con reload
### 16.14 Manage Dnsmasq log
* /etc/logrotate.d/dnsmasq
* sudo /etc/logrotate.conf --debug
### 16.15 Configuring Wildcard Domains
* sudo systemctl restart dnsmasq.service
* nslookup foo.wildcard.net
