# shell面试题总结

#### 1、统计词频

某公司网络中心的linux服务器只有系统维护时才执行reboot, 网络管理员统计服务器使用reboot指令的次数（   ）

```
history | grep -w reboot | grep -v grep | wc -l
```

其中：grep -w指定精确匹配。

​            wc -l统计行数

#### 2、创建文件test

```
touch /test
```

```
>/test
```

```
 a=`touch /test`
```



#### 3、获取shell脚本参数

$1 获取第一个参数

$* 获取所有参数

其他用法：

$$
Shell本身的PID（ProcessID）
$!
Shell最后运行的后台Process的PID
$?
最后运行的命令的结束代码（返回值）
$-
使用Set命令设定的Flag一览
$*
所有参数列表。如"$*"用「"」括起来的情况、以"$1 $2 … $n"的形式输出所有参数。
$@
所有参数列表。如"$@"用「"」括起来的情况、以"$1" "$2" … "$n" 的形式输出所有参数。
$#
添加到Shell的参数个数



#### 4、if [ $2 -a $2 = "test" ]中 -a是什么意思

```
并且
```



#### 5、以下哪个命令可实现文件去重并排序

```
sort demo.txt|uniq
```

uniq 是删除相邻的重复行，故要先排序



6、获取文件某一行某一列

cat cut 



LeetCode笔试题

1、给定一个文本文件 `file.txt`，请只打印这个文件中的第十行。

tail -n +10 file.txt | head -1

注意：

tail -n K 输出最后k行数据

tail -n +K 输出从第k行开始的后面所有行数据

2、https://leetcode-cn.com/problems/word-frequency/