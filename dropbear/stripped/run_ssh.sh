#!/system/bin/sh

#cd into the dir
cd /online/ssh/

#
export PATH=$PATH:$(pwd)
#

mkdir -p /data/root-home
mkdir -p /data/root-home/.ssh

SSH_USER="root"
SSH_PASS=$(cat /data/root-home/password | busybox tr -d '\n')
SSH_HOME="/data/root-home"
SSH_AUTHKEYSFILE="$SSH_HOME/.ssh/authorized_keys"

#///////
SSH_UID=$(busybox id -u "$SSH_USER")
SSH_GID=$(busybox id -g "$SSH_USER")
#///////

#
mkdir -p /data/dropbear
busybox chown -R root /data/dropbear
busybox chmod -R 600 /data/dropbear
#

if [ -z "$SSH_PASS" ]; then
	SSH_PASS="DEFAULTPASS_guy3rhgu"
fi

while [ true ]; do
	#respawn the server
	 ./dropbear -R -F -E -A -N "$SSH_USER" -C "$SSH_PASS" -T "$SSH_AUTHKEYSFILE" -U "$SSH_UID" -G "$SSH_GID" -S "$SSH_HOME" > /dev/null 2>&1
	killall -9 dropbear
	sleep 5
done



