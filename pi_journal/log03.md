## Setpember 1, 2013

### Install VNC Server

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
