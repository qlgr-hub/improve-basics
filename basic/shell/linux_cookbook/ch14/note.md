## Chapter 14 Build Linux firewall with firewalld
* Traditional: netfilter + iptables
* New: 
  * ufw
  * nftables
  * firewalld
### 14.1 Query the running firewall
* systemctl status nftables.service
* systemctl status firewalld.service
* systemctl status ufw.service
### 14.2 Install firewalld
* Need insall firewalld package
* nmcli device status # check network connection
* nmcli connection down ACCESS_POINT
* nmcli connection up ACCESS_POINT
### 14.3 Query firewalld version
* sudo firewall-cmd --version
### 14.4 Config firewalld backend
* /etc/firewalld/firewalld.conf
  * FirewallBackend=nftables
  * FirewallBackend=iptables
### 14.5 List all zone and the services managed by each zone
* firewall-cmd --get-default-zone
* firewall-cmd --get-zones
* firewall-cmd --get-active-zones
* sudo firewall-cmd --zone=public --list-all
* sudo firewall-cmd --list-all-zones
### 14.6 Query service
* sudo firewall-cmd --get-services
* sudo firewall-cmd --get-services | xargs -n1
* sudo firewall-cmd --info-service bittorrent-lsd
* sudo firewall-cmd --info-service ceph-mon
### 14.7 Select and Set zone
* sudo firewall-cmd --zone=work --list-all
* sudo firewall-cmd --zone=work --permanent --change-interface=eth0
* sudo firewall-cmd --zone=work --list-interfaces
* sudo firewall-cmd --runtime-to-permanent
### 14.8 Modify firewalld default zone
* firewall-cmd --get-default-zone
* sudo firewall-cmd --set-default-zone drop
### 14.9 Customize firewalld zone
* firewall-cmd --zone=internal --list-all
* sudo firewall-cmd --remove-service=samba-client --zone=internal
* sudo firewall-cmd --zone=internal --add-service=ldaps
* sudo firewall-cmd --runtime-to-permanent
* sudo firewall-cmd --reload
### 14.10 Create New zone
* /etc/firewalld/zones/names.xml
* sudo firewall-cmd --permanent --get-zones
* sudo firewall-cmd --reload
* sudo firewall-cmd --get-zones
* sudo firewall-cmd --zone=names --list-all
### 14.11 firewalld integrate with NetworkManager
* nm-connection-editor
### 14.12 Allow or disable a port
* sudo firewall-cmd --zone=work --remove-port=22/tcp
* sudo firewall-cmd --zone=work --add-port=2022/tcp
* sudo firewall-cmd --list-all --zone=work
* sudo firewall-cmd --runtime-to-permanent
### 14.13 Using rich rules to block IP addresses
* sudo firewall-cmd --zone=internal --add-rich-rule='rule family="ipv4" source address=192.168.1.91 reject'
* sudo firewall-cmd --runtime-to-permanent
* sudo firewall-cmd --zone=internal --list-rich-rules
* sudo firewall-cmd --zone=internal --remove-rich-rule='rule family="ipv4" source address=192.168.1.91 reject'
* sudo firewall-cmd --zone=internal --add-rich-rule='rule family="ipv4" source address=192.168.1.91 service name=ssh" protocal=tcp reject'
### 14.14 Modify zone's default target
* sudo firewall-cmd --zone=internal --list-all
* sudo firewall-cmd --permanent --zone=internal --set-target=REJECT
* sudo firewall-cmd --reload
* firewall-cmd --zone=names --list-all
### firewall-cmd
* zone options:
  * target: Defines the default action when a packet is encountered that does not match any rule.
    * default: same as REJECT
    * ACCEPT: accept all
    * DROP: drop
    * REJECT: drop and send reject message
  * icmp-block-inversion Reverse icmp request
  * interfaces zone's network interfaces
  * source Can set the IP, MAC and IP range
  * services Services managed by zone
  * ports ports managed by zone
  * protocal protocal managed by zone  /etc/protocals
  * masquerade Masquerading for sharing IPv4 Internet connections
  * forward-ports manage forward ports
  * source-ports list of source port
  * icmp-blocks icmp block list
  * rich rules
* default zones
  * drop
  * block
  * public
  * external
  * dmz
  * work
  * home
  * internal
  * trusted