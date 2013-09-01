## Setpember 1, 2013

### Install VNC Server 
#### SSH into Raspberry Pi

Install tigervnc or tightvnc:

```bash
# pacman -S tigervnc
# pacman -S tightvnc
```

Setup the vncserver password. Run: 

```bash
$ vncserver
```

You will see:

```bash
[tommy@alarmpi ~]$ vncserver  

You will require a password to access your desktops.

Password:
Verify:

New 'alarmpi:1 (tommy)' desktop is alarmpi:1

Creating default startup script /home/tommy/.vnc/xstartup
Starting applications specified in /home/tommy/.vnc/xstartup
Log file is /home/tommy/.vnc/alarmpi:1.log
```

In order to see the XFCE Desktop in a VNC session, copy and paste the following
block into terminal. Copy the entire command (7 lines): 

```bash
cp ~/.vnc/xstartup ~/.vnc/xstartup.bak &&
cat << 'EOF' > ~/.vnc/xstartup
#!/bin/sh

export XKL_XMODMAP_DISABLE=1
exec /bin/sh /etc/xdg/xfce4/xinitrc
EOF
```

If all is well, go ahead and kill the existing vncserver:

```bash
$ vncserver -kill :1
```

Now, start it again with custom parameters:

```bash
$ vncserver -geometry 1024x800 -alwaysshared -dpi 96 :1
```

#### On the client side

There are many free VNC clients available for Linux, OS X, and Windows. TigerVNC
and TightVNC are two. From the client computer, connect to the vncserver with 
the following command:

```bash
$ vncviewer <ip.address>:1
```

When done with the session, go ahead and kill the vncserver from the Pi:

```bash
$ vncserver -kill :1
```
