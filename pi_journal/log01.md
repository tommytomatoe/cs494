## Septmber 1, 2013

### Baking Pi

The very first thing I did with the Pi was load it up with my favorite GNU/Linux
distro - Arch Linux. Arch's philosophy can be summed up with KISS - keep it
simple, stupid. Simplicity makes Unix what it is. Using a distro such as Arch
just makes sense.

### Installing Arch Linux ARM

Installing Arch Linux ARM was super easy. I was up and running in less than five
minutes. Here are the steps I took. My development machine:

- MacBook Pro 2011 
  - Sandy Bridge i7-2720qm
  - 16GB RAM
  - 256GB Crucial SSD
- Dual boot using rEFInd 
  - Arch Linux is the primary OS
  - OS X Mountain Lion for Mac-specific tasks
  - Windows 7 Enterprise in a Virtual Box VM
- Raspberry Pi Model B Revision 2.0
  - 512MB RAM
  - 2 USB ports
  - HDMI out
  - RCA out
  - 32GB Sony Class 10 SD Card
  - 4-port USB Hub
  - Nexus 7 Micro USB charger

1. Download Arch Linux Arm using this [torrent](http://downloads.raspberrypi.org/images/archlinuxarm/archlinux-hf-2013-07-22/archlinux-hf-2013-07-22.img.zip.torrent).
  * Using the torrent was much faster than the direct downloads.
  * The download came in a .zip file (archlinux-hf-2013-07-22.img.zip). 
2. Unzip the download to get the .img file .
  * `unzip archlinux-hf-2013-07-22.img.zip`
3. Write the .img file to the SD card. 
  * `sudo dd bs=1M if=./archlinux-hf-2013-07-22.img of=/dev/mmcblk0`
  * Arch Linux was not able to mount the SD card, however I could write to it.
4. Setup Raspberry Pi
  * Plug SD card into Raspberry Pi.
  * Plug in micro USB charger.
  * Plug in Ethernet.
  * Wait for green lights. 
5. Once booted, use `nmap -sP 10.0.10.0/24` to find IP address on LAN
  * IP was found, boot was success!
  * Raspberry Pi was 10.0.10.22.
  * Use AirPort Utility to reserve 10.0.10.22 for Raspberry Pi using DHCP.
  * Now reboot Pi to make sure it gets the same IP using DHCP.
6. Why make the DHCP reservation on the router end?
  * In doing so, we can avoid setting a static IP on the pi.
  * This allows the Pi to easily connect to other networks in the future.
7. With Arch Linux ARM, `ssh` is turned on by default.
  * Log into Pi using `ssh root@10.0.10.22`.
  * The Pi will prompt for password, and the password is `root`.
  * `ssh` connection is successful.
8. Optionally, setup `ssh` config for easy connection in the future.
  * On the client (Arch Linux on my MBP):
  * ```sshconfig
Host pi
    Hostname 10.0.10.22
    IdentifyFile ~/.ssh/id_rsa
    User root
    Port 22
```
9. Copy public key to Pi: `cat ~/.ssh/id_rsa.pub | ssh pi "mkdir -p .ssh && cat > .ssh/authorized_keys"`.
  * Now we can `ssh` with ease.
10. Update Arch Linux ARM with `pacman -Syu` while in `ssh` session.

Next time we will play with VNC server and other fun things!
