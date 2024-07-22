## Chapter 21 Troubleshooting network
### 21.1 ping
* ping localhost
* ping -c 3 {target ip}
* ping -c 500 -i 2 {ip}
* sudo modprobe pcspkr
* lsmod | grep pcspkr
* echo -e "\a"
* tput bel
* echo -e '\007'
### 21.2 fping nmap
* fping -c1 -gAds 192.168.1.0/24 2>1 | egrep -v "ICMP|xmt" >> fping.txt
* sudo nmap -sn 192.168.1.0/24 > nmap.txt
* awk '/Nmap/{print ""}1' nmap.txt ? nmap2.txt
* sudo nmap -sS 192.168.1.*
* nmap -sn 192.168.43.0/24 | grep 'Nmap scan report for' | cut -d' ' -f5,6
### 21.3 arping
* sudo arping -I wlan2 -c 4 192.168.1.91
* sudo arping -I wlan2 -c 4 192.168.1.91
* nmap -sn 192.168.43.0/24 | grep 'Nmap scan report for' | cut -d' ' -f5,6
* sudo tcpdump -pi eth1 arp
### 21.4 httping
* httping -c4 -l -g www.oreilly.com
* httping -c4 -l -Gg www.oreilly.com
* httping -c4 -l -rGg www.oreilly.com
* httping -c4 -l -rGg www.oreilly.com:8080
* httping -c4 -l -srGg www.oreilly.com
### 21.5 mtr
* mtr -wo LSRABW carlaschroder.com
* ping -c 3 hs17.name.tools
* whois -H networklayer.com
* mtr -r -c25 oreilly.com >> mtr.txt && date >> mtr.txt