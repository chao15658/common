1、使用expect做批量免密

a.获取主机ip列表

b.生成本机密钥

c.拷贝密钥至其他各个主机

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
```

 [for_ip.sh](for_ip.sh) 

注意：在shell中插入expect语法时，expect中定义的变量会失效，必须放在expect之外。



**expect**语法介绍

**安装**

yum install -y tcp 

yum install -y expect

**选项**

-d / -D 开启调试模式

spawn 后跟一个命令，开启一个会话

set timeout 30 设置会话超时时间 

expect接收命令执行的输出，和期望字符比较，如果对应则执行对应的send来发送交互信息（多分支类似switch语句）。

```kotlin
expect 
{
    "$case1" {send "$response1\r"}
    "$case2" {send "$response2\r"}
    "$case3" {send "$response3\r"}
}
```

expect eof等待执行结束

exp_continue匹配之后允许expect继续执行而不是返回。



参考链接

 https://www.jianshu.com/p/b987f5e92c03 