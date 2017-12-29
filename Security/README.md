1. Create a certain structure client-router-server with virtual box
2. on router, open terminal, navigate to the folder with iptables.sh and give\\
sudo ./iptables2.sh restart \\
sudo iptables --list -nv \\

now test with client and server:
ICMP with ping, port -p icmp
DNS with dig, e.g. dig www.fri.uni-lj.si, port 53
HTTP with curl, e.g. curl google.com, port 80
HTTPS with curl, e.g. curl https://www.google.com, port 443
SSH with ssh: ssh isp@ip-of-the-machine-your-are-connecting-to, port 22
