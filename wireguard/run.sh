#!/system/bin/busybox sh

#change 10.0.6.2 to your ip
#and load the tun module before loading this script
#and you will need to run the openvpn_run script

#for compiling, use https://gist.github.com/baselsayeh/d7022c370a33452546e96bd2fda2c877

./wireguard-go-armv7a-stripped wg0
./wg-armv7a-stripped setconf wg0 config.conf
ip addr add 10.0.6.2/24 broadcast + dev wg0
ip link set dev wg0 up


