## Chapter 10 Get detailed information about PC hardware
### 10.1 Get hardware info with lshw
* sudo lshw | tee hardware.txt
* sudo lshw -short
* sudo lshw -businfo
### 10.2 Filter lshw info
* sudo lshw -short -class bus -class cpu
* sudo lshw -html -class bus -class cpu | tee lshw.html
* sudo lshw -xml -class printer -class display -class input | tee lshw.xml
* sudo lshw -json -class storage | tee lshw.json
* sudo lshw -json -sanitize -class bus -class cpu | tee lshw.json
  * -sanitize Remove sensitive information
### 10.3 Check monitor/RAID device info with hwinfo
* hwinfo --monitor (Check monitor info)
* hwinfo --listmd (Check RAID device info)
* hwinfo --short
* hwinfo --mouse --network --cdrom
* hwinfo --help
### 10.4 Check PCI hardware with lspci
* lspci
* lspci -v
* lspci -vv
* lspci -vvv
### 10.5 Interpret lspci output
* lspci
* lspci -tvv
* lspci -D
### 10.6 Filter lspci output
* lspci -v | awk '/USB/,/^$/' Check USB device info
* lspci -v | awk '/Audio/,/^$/' Check Audio device info
* lspci -nn  Filter with bus id
* lspci -d ::0604 Filter with supplier type
* lspci -d 8086:: Filter with supplier type
* lspci -d :0412: Filter with supplier type
### 10.7 Identifying kernel modules via lspci
* lspci -kd ::0200 eth controller
* lspci -vmmk | awk '/VGA/,/^$/' VGA controller
### 10.8 Get USB device list with lsusb
* lsusb
* lsusb -tv
### 10.9 Get partitions and storage list via lsblk
* lsblk
* lsblk -f /dev/sda
* lsblk -S  Check SCSI device
### 10.10 Get CPU info
* lscpu
* lscpu -C Check cpu cache info
### Identify hardware Arch
* uname -m