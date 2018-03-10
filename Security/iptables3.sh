#This rules sum to iptables2.sh

### FORWARDING RULES

# Do NAT for internet-bound traffic
iptables -t nat -A POSTROUTING -o $INET_IFACE -j MASQUERADE

# (13) TODO: Allow routing of packets that belong to ESTABLISHED or RELATED connections.
iptables -A FORWARD -m state --state ESTABLISHED,RELATED -j ACCEPT

# (14) Forward pings
iptables -A FORWARD -p icmp --icmp-type echo-request -m state --state NEW  -j ACCEPT

# (15) Forward DNS requests from subnets to Internet and permit in corresponding responses
iptables -A FORWARD -o $INET_IFACE -p udp -m multiport --ports 53 -m state --state NEW -j ACCEPT

# Block Facebook.com
iptables -A FORWARD -p tcp --dport 80 -d $IP_FACEBOOK -m state --state NEW,ESTABLISHED -j DROP
iptables -A FORWARD -p tcp --dport 443 -d $IP_FACEBOOK -m state --state NEW,ESTABLISHED -j DROP
# (16) TODO: Forward HTTP, HTTPS and SSH traffic from client_subnet to Internet and to server_subnet
iptables -A FORWARD -p tcp --dport 80 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -A FORWARD -p tcp --dport 443 -m state --state NEW,ESTABLISHED -j ACCEPT

# Allow SSH connections between client and server but not with the public Internet
iptables -A FORWARD -p tcp --dport 22 -s $IP_CLIENT -d $IP_SERVER -m state --state NEW -j ACCEPT
iptables -A FORWARD -p tcp --dport 22  -m state --state NEW -j DROP
