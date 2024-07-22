## Chapter 12 Secure remote access with OpenSSH
### 12.1 Install OpenSSH server
* Ubuntu install: sudo apt install openssh-server
* systemctl status sshd
### 12.2 Generate new host key
* sudo rm /etc/ssh/ssh_host*
* sudo ssh-keygen -A
### 12.3 Config OpenSSH server
* ls -l /etc/ssh/
* config file path: /etc/ssh/sshd_config
* If modify config file use following commad to reload sshd
* sudo systemctl reload sshd.server
* cat /etc/services  Check server port
### 12.4 Check Configuration Syntax
* sudo sshd -t
  * -t test (Does not affect service)
### 12.5 Set up password authentication
* ~/.ssh/known_hosts
### 12.6 Get key fingerprint
* ssh-keygen -lf /etc/ssh/ssh_host_rsa_key
### 12.7 Using public key authentication
* ssh-keygen
  * -C  add key comment
  * -f key name
  * -t key type (rsa ecdsa ed25519)
  * -b bit strength
  * -i tell the ssh client which key to use
### 12.8 Manage multiple public key
* ssh-keygen -f assign a name
### 12.9 Modify private key password
* ssh-keygen -p modify password
### 12.10 Automatically manage passwords using keychain
* Add following content to ~/.bashrc
  * keychain ~/.ssh/id-server1 ~/.ssh/id-server2 ~/.ssh/id-server3 . ~/.keychain/$HOSTNAME-sh
  * keychain is a manager of ssh-agent and gpg-agent (like gnome-keyring)
### 12.11 Use keychain to provide private key password to cron
* Create new shell script test1-backup-server1 content is following
* ``` #!/usr/bin/env bash
    source $HOME/.keychain/${HOSTNAME}-sh /usr/bin/rsync -ae "ssh -i /home/test1/.ssh/id-server3" /home/test1/ test1@server1:/backups/
* chmod +x test1-backup-server1
* crontab -e
* ```#
    15 22 * * * /home/test1/test1-backup-server1
### 12.12 Use ssh to establish a secure X session tunnel
* echo $XDG_SESSION_TYPE
* loginctl show-session "XDG_SESSION_ID" -p Type
* loginctl is part of systemctl
* Confirm session type
  * Wayland not support ssh
  * X11 modify /etc/ssh/sshd_config X11Forwarding field to yes
* /etc/ssh/sshd.conf can be config X11DisplayOffset
### 12.13 Open an ssh session and run a command with just one line of input
### 12.14 mount remote filesystem with sshfs
* mkdir sshfs
* sshfs test1@server1: sshfs/
* fusermount -u sshfs/
* sshfs test1:server1:/home/test1/arias sshfs/
* sshfs test1:server1:/home/test1/arias sshfs/ -o reconnect
### 12.15 Customize bash prompt for ssh
* ~/.bashrc
* ```
    if [ -n "$SSH_CLIENT" ]; then text=" ssh"
    fi
    export PS1='\[\e[0;36m\]\u@\h:\w${text}$\[\e[0m\] '
### 12.16 List OpenSSH supported encryption algorithms
* ssh -Q help
* ssh -Q sig