# 1、字符串

**1、字符串比较**

示例1

字符串判空[ -z 字符串]

[root@node0 shell_dir]# str=""
[root@node0 shell_dir]# [ -z "$str" ]
[root@node0 shell_dir]# echo $?
0

[root@node0 shell_dir]# str="hello"
[root@node0 shell_dir]# [ -z "$str" ]
[root@node0 shell_dir]# echo $?
1

示例2

等于[ 字符串1 == 字符串2 ]

[root@node0 shell_dir]# [ $USER == root ]
[root@node0 shell_dir]# echo $?
0

[root@node0 shell_dir]# [ $USER == tom ]
[root@node0 shell_dir]# echo $?
1



2、**整数比较**

-le 小于等于

-lt小于

-eq等于

-ge大于等于

-gt大于



示例1

[root@node0 shell_dir]# [ 3 -le 8 ]
[root@node0 shell_dir]# echo $?
0
[root@node0 shell_dir]# [ 3 -ge 8 ]
[root@node0 shell_dir]# echo $?
1

[root@node0 shell_dir]# [ 3 -eq 8 ]
[root@node0 shell_dir]# echo $?
1

[root@node0 shell_dir]# [ 3 -eq 3 ]
[root@node0 shell_dir]# echo $?
0

示例2

当前登录用户数是否>=2

[root@node0 shell_dir]# [ $(who |wc -l) -ge 2 ]
[root@node0 shell_dir]# echo $?
0



3、**文件状态检测**

-e 目录或文件是否存在

[root@node0 shell_dir]# [ -e /etc/ ]
[root@node0 shell_dir]# echo $?
0

[root@node0 shell_dir]# [ -e /etc/xxx ]
[root@node0 shell_dir]# echo $?
1

-d判断是否为目录

[root@node0 shell_dir]# [ -d /etc/hosts ]
[root@node0 shell_dir]# echo $?
1
[root@node0 shell_dir]# [ -d /etc ]
[root@node0 shell_dir]# echo $?
0

-f判断是否为文件

[root@node0 shell_dir]# [ -f /etc/xxx ]
[root@node0 shell_dir]# echo $?
1
[root@node0 shell_dir]# [ -f /etc/hosts ]
[root@node0 shell_dir]# echo $?
0

-r判断是否具有读权限

[root@node0 shell_dir]# [ -r /etc/hosts ]
[root@node0 shell_dir]# echo $?
0
[root@node0 shell_dir]# [ -r /etc/xxx ]
[root@node0 shell_dir]# echo $?
1

-w写权限

[root@node0 shell_dir]# [ -w /etc/hosts ]
[root@node0 shell_dir]# echo $?
0
[root@node0 shell_dir]# [ -w /etc/xxx ]
[root@node0 shell_dir]# echo $?
1

-x执行权限

[root@node0 shell_dir]# [ -x /etc/hosts ]
[root@node0 shell_dir]# echo $?
1

[root@node0 shell_dir]# [ -x /usr/bin/ls ]
[root@node0 shell_dir]# echo $?
0



**组合多个命令**

; 顺序执行，无逻辑关系

&& 仅当前一条命令执行成功时才执行后一条命令

|| 前一条命令执行失败时才会执行后一条命令



示例1

[root@node0 etc]# cd /etc/ ; ls

切换到/etc下；之后执行ls

[root@node0 ~]# cd /etc/xxx ; ls
-bash: cd: /etc/xxx: No such file or directory
anaconda-ks.cfg               blog 

切换失败，执行的是ls /root/        

示例2

[root@node0 ~]# cd /etc/ && ls

切换到/etc/，之后执行ls /etc/成功

[root@node0 ~]# cd /etc/xxx && ls
-bash: cd: /etc/xxx: No such file or directory
切换失败，ls不执行

示例3

[root@node0 ~]# cd /etc/ || ls
[root@node0 etc]# 

切换成功，不执行ls /etc/

[root@node0 ~]# cd /etc/xxx || ls
-bash: cd: /etc/xxx: No such file or directory
anaconda-ks.cfg               blog         gpdb-6.source_20210512.tar.gz  pg_rman-1.3.11.tar.gz  srccode
apache-ant-1.9.15 

执行切换失败，ls /root

示例4

[root@node0 ~]# [ a == a ] && echo Y || echo N
Y

[root@node0 ~]# [ a == b ] && echo Y || echo N
N

示例5

节点性能指标采集

[root@node0 shell_dir]# cat info.sh 

```
#!/bin/bash

#this script is used to collect system metric

local_time=$(date +"%Y-%m-%d %H:%M:%S")
local_ip=$(ifconfig ens33|grep netmask|tr -s " "|cut -d " " -f 3)
free_mem=$(cat /proc/meminfo |grep Avail|tr -s " "|cut -d" " -f 2)
free_disk=$(df |grep "/$"|tr -s " "|cut -d " " -f4)
cpu_load=$(cat /proc/loadavg |cut -d " " -f3)
login_user=$(who | wc -l)
procs=$(ps -aux | wc -l)

[ $free_mem -le 1048576  ] && \
    echo "$local_time free memory not enough. free mem: $free_mem on $local_ip"

res=$(echo "$cpu_load > 4" | bc)
[ $res -eq 1  ] && \
    echo "$local_time CPU load to high, CPU 15 averageload: $cpu_load on $local_ip" 

[ $login_user -gt 3  ] &&\
    echo "$local_time too many user. $login_user users login to $local_ip" 

[ $procs -gt 50  ] && \
    echo "$local_time too many procs. $procs proc are running on $local_ip"
```

示例6

批量密钥交换

[root@node0 shell_dir]# cat for_ip.sh 

```
#!/bin/bash

#select alive ip of current netmask,
#write alive ip to ip.txt
#used to exchange key  in batch

#1.get ip
> ip.txt
for i in {90..120}
do
  ip=192.168.1.$i
  {
    ping -c1 -W1 $ip &> /dev/null
    if [ $? -eq 0 ];then
      echo "$ip" >> ip.txt
    fi
  } & 
# &放在后台执行命令，相当于多进程
done
#防止下面的echo在上面for循环执行结束之前开始运行
wait
echo "get ip ok!"

#2. generate key
if [ ! -f  ~/.ssh/id_rsa ]; then
  ssh-keygen -P "" -f ~/.ssh/id_rsa 
fi

#3. distribute key
pass=passwd
while read line
do
  /usr/bin/expect <<-EOF
      set timeout 2 
      spawn ssh-copy-id $line -f
      expect -D {
        "yes/no" { send "yes\r"; exp_continue }
        "password:" { send "$pass\r" }
      }
      expect eof
EOF
done <ip.txt
```


