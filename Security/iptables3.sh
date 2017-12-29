#This rules sum to iptables2.sh

# Allow SSH connections between client and server but not with the public Internet
iptables -A FORWARD -p tcp --dport 22 -s $IP_CLIENT -d $IP_SERVER -m state --state NEW -j ACCEPT
iptables -A FORWARD -p tcp --dport 22  -m state --state NEW -j DROP
