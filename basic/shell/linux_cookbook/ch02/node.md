## chapter 02 Manage GRUB
### 2.1 Rebuild GRUB config file
* Fedora or OpenSUSE
  * sudo grub2-mkconfig -o /boot/grub2/grub.cfg
* Ubuntu
  * sudo grub-mkconfig -o /boot/grub/grub.cfg
  * sudo update-grub
### 2.2 Show hidden GRUB menu
* Fedora Ubuntu
  * Use Shift (keyboard)
  * Modify /etc/default/grub (need rebuild GRUB config)
    * GRUB_TIMEOUT="10"
    * GRUB_TIMEOUT_STYLE=menu
    * comment GRUB_HIDDEN_TIMEOUT=0 and GRUB_HIDDEN_TIMEOUT_QUIET=true
### 2.3 Booting different Linux kernels (select from GRUB menu by keyboard)
### 2.4 GRUB configuration file
* config file paths:
  * /boot/grub/
  * /etc/default/grub
  * /etc/grub.d/
    * sudo ls -C1 /etc/grub.d/ (check functional scripts)
    * sudo chmod -x 20_linux_xen # disable 20_linux_xen
    * sudo chmod +x 20_linux_xen # enable 20_linux_xen
### 2.5 Write basic GRUB config file
* /etc/default/grub
  * GRUB_DEFAULT : Default startup item number (Count the menuentries from the /boot/grub/grub.cfg file to determine the number)
    * sudo awk -F\' '/menuentry / {print i++,$2}' /boot/grub/grub.cfg
    * GRUB_DEFAULT=saved + GRUB_SAVEDEFAULT=true to remember last startup
  * GRUB_TIMEOUT=10 seconds to wait
    * 0 : hidden
    * -1 : waiting for user selection
  * GRUB_CMDLINE_LINUX= Add Linux kernel options to all menu items
  * GRUB_CMDLINE_LINUX_DEFAULT= Only pass kernel options to the default menu item
  * GRUB_TERMINAL
    * gfxterm GUI mode
    * console CUI mode
  * GRUB_GFXMODE GUI display mode (1920x1080 etc)
    * in GRUB terminal use videoinfo command check supported mode
    * auto reasonable default value (system assign)
  * GRUB_BACKGROUND= GRUB menu backgroud image (url path)
  * GRUB_THEME= GRUB menu theme (url path)
### 2.6 Set custom GRUB background
* Prepare PNG\JPG\TFA image 
* GRUB_BACKGROUND="image path"
* Comment GRUB_THEME item
### 2.7 Change GRUB menu's font color
* Use GRUB terminal command (Press C in the GRUB menu enter GRUB terminal)
  * menu_color_highlight=cyan/blue
  * menu_color_normal=yellow/black
  * foreground/background mode (Solid color with no transparency)
  * save permanetly
    * create a new script in /etc/grub.d/ (07_font_colors etc)
    * ```
        if [ "x${GRUB_BACKGROUND}" != "x" ] ; then
            if [ "x${GRUB_COLOR_NORMAL}" != "x" ] ; then
                echo "set color_normal=${GRUB_COLOR_NORMAL}"
            fi

            if [ "x${GRUB_COLOR_HIGHLIGHT}" != "x" ] ; then
                echo "set color_highlight=${GRUB_COLOR_HIGHLIGHT}"
            fi
        fi
    * sudo chmod +x 07_font_colors
    * change /etc/default/grub
      * export GRUB_COLOR_NORMAL="yellow/block"
      * export GRUB_COLOR_HIGHLIGHT="cyan/blue"
### 2.8 Use GRUB theme
* Search and install GRUB theme packages
  * apt search theme | grep grub (grub-theme-breeze\grub-theme-ubuntu-mate\grub-breeze-theme)
  * use apt install them on Ubuntu
* Theme packages installed in /boot/grub/themes
* /etc/default/grub
  * GRUB_THEME="{theme path}/theme.txt"
  * comment GRUB_BACKGROUND item
### 2.9 Rescue an ubbootable system in GRUB terminal
* GRUB terminal command
  * set pager=1      # support turning pages to view long content
  * ls               # list disk partitions
  * ls (hd0,3)       # list specific partition's info
  * ls (hd0,3)/      # list specific partition's content
  * ls (hd0,3)/boot  # list specific partition's boot file
  * set root=(hd0,2) # specify root file system
### 2.10 Rescue an ubbootable system in GRUB rescue terminal
* GRUB rescue terminal command
  * Most of them are the same as GRUB terminal
  * set prefix=(hd0,2)/boot/grub # specify /boot/grub position
  * insmod normal # installation mode normal
  * insmod linux  # installation mode Linux
  * linux {vmlinuz file path} root={patition path} # specify vmlinuz path
  * initrd {initrd file path} # specify initrd path
  * boot
### 2.11 Reinstall GRUB config
* sudo grub-mkconfig -o /boot/grub/grub.cfg
* sudo grub-install {device name} (/dev/sda etc)