transfer the files inside the stripped folder into /online/ssh, then run theese commands to enable dropbear running on boot

```
mkdir -p /data/root-home
mkdir -p /data/root-home/.ssh
echo "ENTER_SSH_PASSWORD_HERE" > /data/root-home/password

mount -o remount,rw /system
echo "" >> /system/etc/autorun.sh
echo "#ssh" >> /system/etc/autorun.sh
echo "[ -f /online/ssh/run_sshd.sh ] && /online/ssh/run_sshd.sh &" >> /system/etc/autorun.sh
sync
mount -o remount,ro /system
```
change `ENTER_SSH_PASSWORD_HERE` to your desired password

