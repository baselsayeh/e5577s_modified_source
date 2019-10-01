ln -s /bin/route /sbin/route
ln -s /bin/ifconfig /sbin/ifconfig

mkdir /dev/net
ln -s /dev/tun /dev/net/tun

busybox date -s 201910010000.00

../openvpn --config client.conf

#note: you might manually run
#ip route add 0.0.0.0/0 via 10.8.0.5 dev tun0

