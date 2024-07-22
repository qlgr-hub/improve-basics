## Chapter 13 Secure remote access with OpenVPN
### 13.1 Install OpenVPN
* Ubuntu install: sudo apt install openvpn
* Ubuntu use network-manager-openvpn to integrate with network-manager
### 13.2 Build a simple link
* Make sure the openvpn service is not running
  * systemctl status openvpn@.openvpn1.service
  * systemctl stop openvpn@.openvpn1.service
* sudo openvpn --remote host2 --dev tun0 --ifconfig 10.0.0.1 10.0.0.2 # on host1
* sudo openvpn --remote host1 --dev tun0 --ifconfig 10.0.0.2 10.0.0.1 # on host2
* ping -I tun0 10.0.0.2 # on host1
* ping -I tun0 10.0.0.1 # on host2
### 13.3 Static key settings for simple encryption
* server side
  * sudo mkdir /etc/openvpn/keys
  * sudo openvpn --genkey --secret myvpn.key
* copy to client
  * scp myvpn.key client1:/etc/openvpn/keys/
* server side config /etc/openvpn/server1.conf
* ```
    dev tun
    ifconfig 10.0.0.1 10.0.0.2
    secret /etc/openvpn/keys/myvpn.key
    local 192.168.43.184
* client side config /etc/openvpn/client1.conf
* ```
    dev tun
    ifconfig 10.0.0.2 10.0.0.1
    secret /etc/openvpn/keys/myvpn.key
    remote 192.168.43.184
* Use sudo systemctl stop openvpn stop vpn service first
* sudo openvpn /etc/openvpn/server1.conf # server side
* sudo openvpn /etc/openvpn/client1.conf # client side
* ping -I tun0 10.0.0.1 # on server side
* ping -I tun0 10.0.0.2 # on client side
### 13.4 Manage PKI with EasyRSA
* After install default path of EasyRSA is /usr/share on Ubuntu
* mkdir mypki
* sudo cp -r /usr/share/easy-rsa mypki
### 13.5 Create PKI
* cd mypki
* easyrsa init-pki
* easyrsa build-ca
  * passphrase
  * passphrase
  * vpnserver1
* easyrsa gen-req vpnserver1 nopass
* easyrsa gen-req vpnclient1
* easyrsa sign-req server vpnserver1
* easyrsa sign-req client vpnclient1
* easyrsa gen-dh
* openvpn --genkey --secret ta.key
* openssl x509 -noout -text -in vpnserver1.crt
### 13.6 Customize EsayRSA's default options
* Create a copy of vars.example
* Modify config beginning of set_var
### 13.7 Build and test server & client config
* /etc/openvpn/server1.conf
* ```
    port 1194
    proto udp
    dev tun
    user nobody
    group nobody

    ca /etc/openvpn/keys/ca.crt
    cert /etc/openvpn/keys/vpnserver1.crt
    key /etc/openvpn/keys/vpnserver1.key
    dh /etc/openvpn/keys/dh.pem
    tls-auth /etc/openvpn/keys/ta.key 0

    server 10.10.0.0 255.255.255.0
    ifconfig-pool-persist ipp.txt
    keepalive 10 120
    persist-key
    persist-tun
    tls-server
    remote-cert-tls client

    status openvpn-status.log
    verb 4
    mute 20
    explicit-exit-notify 1

* /etc/openvpn/client1.conf
* ```
    client
    dev tun
    proto udp
    remote server1 1194

    persist-key
    persist-tun
    resolv-retry infinite
    nobind

    user nobody
    group nobody
    tls-client
    remote-cert-tls server
    verb 4

    ca /etc/openvpn/keys/ca.crt
    cert /etc/openvpn/keys/vpnclient1.crt
    key /etc/openvpn/keys/vpnclient1.key
    tls-auth /etc/openvpn/keys/ta.key 0
* sudo systemctl stop openvpn
* sudo openvpn /etc/openvpn/server1.conf # server side
* sudo openvpn /etc/openvpn/client1.conf # client side
### 13.8 Control OpenVPN with systemctl
* sudo systemctl enable openvpn@austin
### 13.9 Dispatch config with .ovpn
* Instead of configuring the certificate path, paste the certificate content directly into the .ovpn file.
### 13.10 Enhance the security of your OpenVPN server
* Use a stronger data channel encryption algorithm and disable encryption algorithm negotiation