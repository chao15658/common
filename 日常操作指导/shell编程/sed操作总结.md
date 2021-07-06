# sed操作总结

工作原理：逐行处理文本。每读取一行，之后执行后面的条件。之后再读取下一行，直到读取所有行，再输出。



命令格式

sed [选项] [定位符] [指令]



常用选项：

-n屏蔽默认输出

-i 修改源文件

-r支持扩展正则表达式



注意：要修改源文件必须加-i,不加-i只是输出替换的效果，不会实际修改源文件。

**定位符**指的是要操作的行号范围或者正则表达式，默认不写的话是操作所有行。



常用的几种指令模式：

插入 (i)

追加（a）

读取（r）

导出（w)

删除（d）

打印 (p)

行替换（c）

关键字替换（s）

原始文件test.txt 

[root@node0 shell_dir]# cat test.txt 
2046 2048 2046 2046
1001 2046 2999 1888
2046 2046 2046 2046



1、插入（insert）

示例1：

第2行之前插入abcXYZ

[root@node0 shell_dir]# sed '2i abcYZ' test.txt 

预览结果：

2046 2048 2046 2046
abcYZ
1001 2046 2999 1888
2046 2046 2046 2046

示例2：

匹配特定字符串

[root@node0 shell_dir]# sed '/2046/i abc\nXYZ' test.txt 

预览结果：

abc
XYZ
2046 2048 2046 2046
abc
XYZ
1001 2046 2999 1888
abc
XYZ
2046 2046 2046 2046



2、追加（append）

示例1：第2行之后追加一行

[root@node0 shell_dir]# sed '2a abcYZ' test.txt 
2046 2048 2046 2046
1001 2046 2999 1888
abcYZ
2046 2046 2046 2046

示例2：包含2046的行后追加

[root@node0 shell_dir]# sed '/2046/a abc\nXYZ' test.txt 
2046 2048 2046 2046
abc
XYZ
1001 2046 2999 1888
abc
XYZ
2046 2046 2046 2046
abc
XYZ



3、读取(read)

示例1：将/etc/hosts文件内容追加到test文件的第2行后面

[root@node0 shell_dir]# sed '2r /etc/hosts' test.txt 
2046 2048 2046 2046
1001 2046 2999 1888
#127.0.0.1   localhost localhost.localdomain localhost4 localhost4.localdomain4
#::1         localhost localhost.localdomain localhost6 localhost6.localdomain6
192.168.9.100 node0
......
2046 2046 2046 2046

示例2：对test.txt匹配1888，匹配到读取/etc/hosts

[root@node0 shell_dir]# sed '/1888/r /etc/hosts' test.txt 
2046 2048 2046 2046
1001 2046 2999 1888
#127.0.0.1   localhost localhost.localdomain localhost4 localhost4.localdomain4
#::1         localhost localhost.localdomain localhost6 localhost6.localdomain6
192.168.9.100 node0
...
2046 2046 2046 2046



4、导出文件

示例1：将test.txt另存为test_copy.txt

[root@node0 shell_dir]# sed 'w test_copy.txt' test.txt 
2046 2048 2046 2046
1001 2046 2999 1888
2046 2046 2046 2046

示例2：将test.txt包含1888的行保存到文件test_copy.txt

[root@node0 shell_dir]# sed '/1888/w test_copy.txt' test.txt 
2046 2048 2046 2046
1001 2046 2999 1888
2046 2046 2046 2046



5、打印(print)，需要屏蔽默认输出（使用-n)

示例1：打印第3行

[root@node0 shell_dir]# sed -n '3p' test.txt 
2046 2046 2046 2046

示例2：打印1-3行

[root@node0 shell_dir]# sed -n '2,3p' test.txt 
1001 2046 2999 1888
2046 2046 2046 2046

示例3：过滤以root开头的行

[root@node0 shell_dir]# sed -n '/^root/p' /etc/passwd
root:x:0:0:root:/root:/bin/bash

示例4：过滤包含3个数字的行

[root@node0 shell_dir]# sed -rn '/[0-9]{3}/p' /etc/passwd
games:x:12:100:games:/usr/games:/sbin/nologin
systemd-network:x:192:192:systemd Network Management:/:/sbin/nologin
...

示例5：过滤磁盘根分区

[root@node0 shell_dir]# df -h |sed -n '/\/$/p'
/dev/mapper/centos-root   97G   20G   78G  21% /

示例6：过滤内存信息

[root@node0 shell_dir]# free -h|sed -n '/Mem/p'
Mem:           981M        289M        457M        7.5M        234M        520M

示例7：打印1，3，6行

[root@node0 shell_dir]# sed -n '1p;3p;6p' /etc/passwd
root:x:0:0:root:/root:/bin/bash
daemon:x:2:2:daemon:/sbin:/sbin/nologin
sync:x:5:0:sync:/sbin:/bin/sync

示例8：打印IP设置

[root@node0 shell_dir]# sed -n '/IPADDR/p' /etc/sysconfig/network-scripts/ifcfg-ens33 
#IPADDR0=169.254.90.60
IPADDR0=192.168.1.100

6、删除行（delete）

示例1：删除文件内容

[root@node0 shell_dir]# sed 'd' /etc/hosts

示例2：删除第一行

sed '1d' /etc/hosts
#::1         localhost localhost.localdomain localhost6 localhost6.localdomain6

...

示例3：删除第1-3行

[root@node0 shell_dir]# sed '1,3d' /etc/hosts
192.168.3.101 node1
192.168.3.102 node2
192.168.3.103 node3

...

示例4：删除不包含dev的行

[root@node0 shell_dir]# sed  '/dev/!d' /etc/fstab 

Accessible filesystems, by reference, are maintained under '/dev/disk'

/dev/mapper/centos-root /                       xfs     defaults        0 0
/dev/mapper/centos-swap swap                    swap    defaults        0 0
/dev/sr0 /media iso9660 defaults        0 0

示例5：删除以#开头的行

[root@node0 shell_dir]# sed '/^#/d' /etc/fstab 

/dev/mapper/centos-root /                       xfs     defaults        0 0
UUID=5d4685e3-b969-464a-9f87-c88d115b4f42 /boot                   xfs     defaults        0 0
/dev/mapper/centos-swap swap                    swap    defaults        0 0
/dev/sr0 /media iso9660 defaults        0 0

示例6：删除空白行

[root@node0 shell_dir]# sed '/^$/d' /etc/fstab 
#

/etc/fstab

Created by anaconda on Mon Nov 30 08:44:07 2020

#

Accessible filesystems, by reference, are maintained under '/dev/disk'

See man pages fstab(5), findfs(8), mount(8) and/or blkid(8) for more info

#
/dev/mapper/centos-root /                       xfs     defaults        0 0
UUID=5d4685e3-b969-464a-9f87-c88d115b4f42 /boot                   xfs     defaults        0 0
/dev/mapper/centos-swap swap                    swap    defaults        0 0
/dev/sr0 /media iso9660 defaults        0 0



7、替换行（c）

示例1：所有行替换为123456

[root@node0 shell_dir]# sed 'c 123456' /etc/hosts
123456
123456
123456

示例2：IPADDR替换为1.1.1.1

[root@node0 shell_dir]# sed  -n '/IPADDR/c IPADDR=1.1.1.1' /etc/sysconfig/network-scripts/ifcfg-ens33 
IPADDR=1.1.1.1
IPADDR=1.1.1.1

示例3：包含127的行替换为127.0.0.1 localhost

[root@node0 shell_dir]# sed -n '/127/c 127.0.0.1 localhost' /etc/hosts
127.0.0.1 localhost

示例4：第4行替换为xxxx

[root@node0 shell_dir]# sed -n '4c xxxx' /etc/shells 
xxxx



8、替换关键字（s）

示例1：替换2046为xxxx，每行只替换第一次出现的位置

[root@node0 shell_dir]# sed 's/2046/xxxx/' test.txt 
xxxx 2048 2046 2046
1001 xxxx 2999 1888
xxxx 2046 2046 2046

示例2：2046全部替换为xxxx

[root@node0 shell_dir]# sed 's/2046/xxxx/g' test.txt 
xxxx 2048 xxxx xxxx
1001 xxxx 2999 1888
xxxx xxxx xxxx xxxx

示例3：只替换第2次出现的位置

[root@node0 shell_dir]# sed 's/2046/xxxx/2' test.txt 
2046 2048 xxxx 2046
1001 2046 2999 1888
2046 xxxx 2046 2046

示例4：2046替换为（2046）

[root@node0 shell_dir]# sed 's/2046/(&)/g' test.txt 
(2046) 2048 (2046) (2046)
1001 (2046) 2999 1888
(2046) (2046) (2046) (2046)

示例5：替换第2行的2046为xxxx

[root@node0 shell_dir]# sed '2s/2046/xxxx/g' test.txt 
2046 2048 2046 2046
1001 xxxx 2999 1888
2046 2046 2046 2046

示例6：删除第2行所有的2046

[root@node0 shell_dir]# sed '2s/2046//g' test.txt 
2046 2048 2046 2046
1001  2999 1888
2046 2046 2046 2046

示例7：替换第2行的2046并打印输出

[root@node0 shell_dir]# sed -n '2s/2046/xxxx/p' test.txt 
1001 xxxx 2999 1888

示例8：自定义替换符（解决/转义问题）

a. [root@node0 shell_dir]# sed -n '2s#2046#xxxx#p' test.txt 
1001 xxxx 2999 1888  #作为替换符

b. [root@node0 shell_dir]# sed -n '2s,2046,xxxx,p' test.txt 
1001 xxxx 2999 1888    逗号作为替换符

c.[root@node0 shell_dir]# sed -n '2s2\20462xxxx2p' test.txt 
1001 xxxx 2999 1888         如果将2作为替换符，需要对替换的内容转义

示例9：替换ls的路径

 echo "/usr/bin/ls" | sed -n 's#/usr/bin/ls#which#p'
which



9、获取行号（=）

示例1：获取包含root的行号

[root@node0 shell_dir]# sed -n '/root/=' /etc/passwd
1
10

示例2：获取bash结尾的行号

[root@node0 shell_dir]# sed -n '/bash$/=' /etc/passwd
1
30
43
44
45
46

示例3：统计行数

[root@node0 shell_dir]# sed -n '$=' /etc/passwd
46

