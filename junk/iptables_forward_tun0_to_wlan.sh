iptables -A FORWARD -i WiFi0 -o tun0 -j ACCEPT
iptables -A FORWARD -i tun0 -o WiFi0 -m state --state ESTABLISHED,RELATED -j ACCEPT

iptables -A FORWARD -i br0 -o tun0 -j ACCEPT
iptables -A FORWARD -i tun0 -o br0 -m state --state ESTABLISHED,RELATED -j ACCEPT

iptables -t nat -A POSTROUTING -o tun0 -j MASQUERADE

