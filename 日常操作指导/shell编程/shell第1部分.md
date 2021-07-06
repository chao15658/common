#### 第一节 shell**基础**

**输出输出**

标准输入0

标准输出1

标准错误输出2

重定向 >

示例1：

ls a.txt > b.txt

 标准错误输出重定向 2>

示例2：

ls xyz.txt 2>b.txt

标准错误输出 + 标准输出重定向 &>

示例3：

ls a.txt xyz.txt &> b.txt

追加 >>

示例3：

ls a.txt >> b.txt



# **执行命令的几种方式：**

开启子进程：

bash/sh

不开启子进程：

source



#### 第2节 **变量**

**变量定义**

x=val

注意：=号两边不能有空格

全局变量

export x=val

特点：在当前shell以及未来的子shell中依然有效。

局部变量

x=val

特点：仅在当前shell有效

显示变量

echo $x

echo ${x}6.5  防止变量歧义

取消变量

unset x

**预定义变量**

$0 当前进程或脚本名

$? 上一条命令的执行结果，0代表执行正常；非0代表不正常

$# 位置变量个数

$* 所有位置变量值

$$ 当前进程的pid

示例：

[root@node0 shell_dir]# cat vars.sh 

```
#!/bin/bash

echo "pid:"$$
echo "last command res:"$?
echo "args:"$*
echo "argc:"$#
echo "process:"$0
```

[root@node0 shell_dir]# sh vars.sh aa bb cc
pid:19654
last command res:0
args:aa bb cc
argc:3
process:vars.sh



#### 第3**节变量扩展**

单引号'' 禁止转义

双引号"" 允许转义

反引号`` 将命令的输出作为变量值，等于$()



示例：

修改密码（使用read定义变量）

[root@node0 shell_dir]# cat alter_user.sh

```
#!/bin/bash
#change passwd

read -p "please input username:" name
read -s -p "please input passwd:" passwd

useradd $name
echo "$passwd" | passwd --stdin $name
```

[root@node0 shell_dir]# sh alter_user.sh 
please input username:cc
please input passwd:useradd: user 'cc' already exists
Changing password for user cc.
passwd: all authentication tokens updated successfully.
[root@node0 shell_dir]# 



#### **第**4节基本运算

**整数**

+-*/

[root@node0 shell_dir]# x=2
[root@node0 shell_dir]# y=3
[root@node0 shell_dir]# echo $[x+y]
5

[root@node0 shell_dir]# echo $((x+y))
5

[root@node0 shell_dir]# echo $[x*y]
6

[root@node0 shell_dir]# echo $((x*y))
6

[root@node0 shell_dir]# echo $[x-y]
-1
[root@node0 shell_dir]# echo $[x/y]
0



自增，自减

[root@node0 shell_dir]# echo $[x-=1]
1

[root@node0 shell_dir]# echo $[x+=1]
2

或者使用let命令

[root@node0 shell_dir]# let x+=1
[root@node0 shell_dir]# echo $x
4

**小数运算**

示例1：

[root@node0 shell_dir]# echo "1.1+2.2"|bc
3.3

示例2：指定精度（小数点后位数）

[root@node0 shell_dir]# echo "scale=2;10/2"|bc
5.00



echo**命令常用选项**

-e 打开扩展

-n 不进行换行



**第5节综合案例**

1、计算三角形面积

[root@node0 shell_dir]# cat calc.sh

```
[root@node0 shell_dir]# cat calc.sh 
#!/bin/bash

#a calcator
read -p "请输入计算的num以内的整数和：" num
echo -e "\033[32m sum: $[num*(num+1)/2] \033[0m"

#三角形面积
read -p "请输入三角形的底边:" widght
read -p "请输入三角形的高:" height
area=$(echo "scale=2;$widght*$height/2"|bc)
echo $area
echo -e "\033[32m area: $area \033[0m"
```

[root@node0 shell_dir]# sh calc.sh 
请输入计算的num以内的整数和：100
  sum: 5050 
请输入三角形的底边:10
请输入三角形的高:3
 area: 15   

2、计算圆面积

[root@node0 shell_dir]# cat circle.sh 

```
#!/bin/bash

#calc circle area
read -p "请输入圆半径：" r
area=$(echo "scale=2;3.14*$r^2"|bc)
echo -e "\033[32m area: $area \033[0m"
```

[root@node0 shell_dir]# sh circle.sh 
请输入圆半径：5
 area: 78.50 

3、自动配置yum源

[root@node0 shell_dir]# cat autoconfigyum.sh 

```
#!/bin/bash

#auto config yum source

URL=192.168.1.100/media

echo "[centos]
name=centos
baseurl=$URL
gpgcheck=0" > /etc/yum.repos.d/iyum.repo
```

转义字符

 格式: echo -e "\033[字背景颜色;字体颜色m字符串\033[0m" 

字颜色:30-----------37
30:黑 
31:红 
32:绿 
33:黄 
34:蓝色 
35:紫色 
36:深绿 
37:白色  



 \33[0m 关闭所有属性 

 \33[30m -- \33[37m 设置前景色 

示例

设置字体颜色为红色

[root@node0 shell_dir]# echo -e "\033[31m xxx \033[0m"
 xxx 

设置字体颜色为绿色

[root@node0 shell_dir]# echo -e "\033[32m xxx \033[0m"
 xxx 



更多参考连接

 https://www.cnblogs.com/demonxian3/p/8963807.html 

