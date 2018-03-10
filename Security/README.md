## Using iptables.sh
1. Create a certain structure client-router-server with virtual box</br>
2. on router, open terminal, navigate to the folder with iptables.sh and give</br>
sudo ./iptables2.sh restart </br>
sudo iptables --list -nv </br></br>

now test with client and server:</br>
ICMP with ping, port -p icmp</br>
DNS with dig, e.g. dig www.fri.uni-lj.si, port 53</br>
HTTP with curl, e.g. curl google.com, port 80</br>
HTTPS with curl, e.g. curl https://www.google.com, port 443</br>
SSH with ssh: ssh isp@ip-of-the-machine-your-are-connecting-to, port 22</br>
