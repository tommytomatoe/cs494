## Setpember 1, 2013

### Install Audio, Video, and Essential Packages

#### In a `ssh` session, run the following commands.

Install audio:

```bash
# pacman -S alsa-utils alsa-firmware alsa-lib alsa-plugins 
```

Install video: 

```bash
# pacman -S xf86-video-fbdev
```

Install X server:

```bash
# pacman -S xorg-xinit xorg-server xorg-server-utils
```

Install desktop environment or windows manager (choose one or more):

```bash
# pacman -S xfce4 
# pacman -S kde
# pacman -S gnome
# pacman -S cinamon
# pacman -S enlightenment2
# pacman -S lxde
# pacman -S blackbox
# pacman -S openbox
# pacman -S fluxbox
```

Install login manager:

```bash
# pacman -S slim
```

#### Optional install script
The `arch_install.sh` script automatically installs necessary packages
It accepts one argument: the desktop environment or windows manager

```bash
# cd /tmp && wget https://raw.github.com/tommytomatoe/cs494/master/tools/arch_install.sh
# chmod +x arch_install.sh
# ./arch_install.sh
```
