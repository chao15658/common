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

pass=passwd
#3. distribute key
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
