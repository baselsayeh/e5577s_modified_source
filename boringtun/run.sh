#same as wireguard-go and openvpn

ln -s /bin/route /sbin/route
ln -s /bin/ifconfig /sbin/ifconfig

insmod tun.ko

mkdir /dev/net
ln -s /dev/tun /dev/net/tun

#wg0 is the new tun interface name
./boringtun wg0 --disable-multi-queue --disable-drop-privileges 1

