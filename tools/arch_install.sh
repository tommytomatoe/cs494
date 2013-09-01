#! /bin/bash

# arch_install.sh
# 
# Quickly install drivers and packages for Arch Linux ARM 
# 
# Author: Tommy Nguyen
# Version: 0.1
# September 1, 2013

if [ -z "$1" ] 
then
  ARCHDE=xfce4
else 
  ARCHDE=$1
fi

# install audio
pacman -S alsa-utils alsa-firmware alsa-lib alsa-plugins 

# install video
pacman -S xf86-video-fbdev

# install x server
pacman -S xorg-xinit xorg-server xorg-server-uti

# install desktop environment
# default is 'xfce4' if no argument is given
pacman -S "$ARCHDE"

# install login manager
pacman -S slim
