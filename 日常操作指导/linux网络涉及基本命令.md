# 网络基础介绍



ip：局域网中其他主机识别本机的标识。

gateway(网管)：

route （）路由）：本机访问局域网中其他主机需要经过的路径。

netmask(掩码):



## 网卡配置：

[root@ci ~]# more /etc/sysconfig/network-scripts/ifcfg-ens33
TYPE=Ethernet
PROXY_METHOD=none
BROWSER_ONLY=no
BOOTPROTO=static
DEFROUTE=yes
IPV4_FAILURE_FATAL=no
IPV6INIT=yes
IPV6_AUTOCONF=yes
IPV6_DEFROUTE=yes
IPV6_FAILURE_FATAL=no
IPV6_ADDR_GEN_MODE=stable-privacy
HWADDR=00:0c:29:10:5e:3c
NAME=ens33
UUID=f2848874-8d88-4dd8-b6e4-4ed09c1f20f6
DEVICE=ens33
ONBOOT=yes
IPADDR0=192.168.31.100
PREFIX00=255.255.255.0
GATEWAY0=192.168.31.1
DNS1=8.8.8.8
DNS2=8.8.4.4

## ifconfig输出：

[root@ci ~]# ifconfig
ens33: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.31.100  netmask 255.255.255.0  broadcast 192.168.31.255
        inet6 fe80::7197:66c6:9018:1ee9  prefixlen 64  scopeid 0x20<link>
        ether 00:0c:29:10:5e:3c  txqueuelen 1000  (Ethernet)
        RX packets 3662  bytes 235694 (230.1 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 715  bytes 83260 (81.3 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0



[root@ci ~]# ip a|grep ens
2: ens33: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    inet 192.168.31.100/24 brd 192.168.31.255 scope global noprefixroute ens33
[root@ci ~]#

## 路由表：

[root@ci ~]# route
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
default         gateway         0.0.0.0         UG    100    0        0 ens33
192.168.31.0    0.0.0.0         255.255.255.0   U     100    0        0 ens33

如何添加路由：

route add -net 224.0.0.0 netmask 240.0.0.0 dev eth0    #增加一条到达244.0.0.0的路由。



删除路由：

route del -net 224.0.0.0 netmask 240.0.0.0 删除路由