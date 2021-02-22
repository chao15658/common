# LINUX文本命令

## awk

获取输出结果某一列

[postgres@MiWiFi-R3L-srv extension]$ df -m /opt
Filesystem                   1M-blocks  Used Available Use% Mounted on
/dev/mapper/VolGroup-lv_root     17710  1509     15301   9% /

获取第三列

df -m /opt | awk '{print $3}'

[postgres@MiWiFi-R3L-srv extension]$ df -m /opt |awk '{print $3}' 
Used
1509

grep

剔除掉Used

[postgres@MiWiFi-R3L-srv extension]$ df -m /opt |awk '{print $3}' |grep -v 'Used'
1509

## vim

文本编辑器

多行编辑

1、鼠标移动到要编辑的行的第一个字符

2、ctrl +V进入块编辑模式，然后选择多行

3、shift + i，进入行首

4、连续按2下Esc。



### 例1：

全局替换

:%s/x/y

将x替换为y



### 例2：

将全文中所有的t字符替换为& （特殊字符需要使用\做转义）。

：%s/t/\&/



搜索：

在插入模式下点击Esc按钮，输入/加上要输入的文本

回车，按n默认从当前行向前搜索；按shift + n 向前搜索



## sed

批量替换多个文件

`sed -i "s/oldstring/newstring/g" grep oldstring -rl yourdir`



## python转义字符\









# 常用shell操作

ctrl + w —往回删除一个单词，光标放在最末尾 
ctrl + k —往前删除到末尾，光标放在最前面（可以使用ctrl+a） 
ctrl + u 删除光标以前的字符 
ctrl + k 删除光标以后的字符 
ctrl + a 移动光标至字符头 
ctrl + e 移动光标至字符尾 

ctrl + l 清屏（相当于clear）

ctrl + r 查询以前输入的命令，之后输入字符可以联想对应命令记录





# dmesg



# cat  /var/log/messages





linux命令总结

dd用于从按块从文件读取数据，效率极高，容易因块尺寸造成数据丢失。
truncate用于截断文件，按大小。
split用于切割大文件（按行、按大小）
awk、sed用于按行读取文件

nmon工具用于查看系统读写、网络性能

psql用于操作PG、GP数据库
pg_ctl用于启动、停止PG、GP数据库


vim使用总结
：+行号用于快速跳转指定行
shift + g 迅速跳转到文件尾部

官方GP数据库安装遇到的坑：

最后在初始化数据库前，密钥交换完成之后，各个节点一定要重启sshd（service sshd restart）,不然初始化过程中会报socket连接失败。

vertica的copy支持管道。

dd、fio用于测试磁盘顺序读写、随机读写、有无缓存、混合读写



linux查看操作系统关于某个进程的详细信息

cat /proc/procpid/limits查看该进程的限制（用户最大进程、文件描述符等）

如查看22进程的限制信息

[root@localhost pthread]# cat /proc/22/limits 
Limit                     Soft Limit           Hard Limit           Units     
Max cpu time              unlimited            unlimited            seconds   
Max file size             unlimited            unlimited            bytes     
Max data size             unlimited            unlimited            bytes     
Max stack size            10485760             unlimited            bytes     
Max core file size        0                    unlimited            bytes     
Max resident set          unlimited            unlimited            bytes     
Max processes             1809                 1809                 processes 
Max open files            1024                 4096                 files     
Max locked memory         65536                65536                bytes     
Max address space         unlimited            unlimited            bytes     
Max file locks            unlimited            unlimited            locks     
Max pending signals       1809                 1809                 signals   
Max msgqueue size         819200               819200               bytes     
Max nice priority         0                    0                    
Max realtime priority     0                    0                    
Max realtime timeout      unlimited            unlimited            us    

要修改该值需要在/etc/security/limits.d/增加一个用户名.conf可限制某个用户的进程相关限制

或直接改/etc/security/limits.conf 修改的是root用户的信息。





linux查看内存：
free -m
输出结果分析：
[root@node1 ~]# free -m
             total       used       free     shared    buffers     cached
Mem:           980        906         73         10          3         62
-/+ buffers/cache:        840        139
Swap:         1983       1541        442



物理内存

total总内存 

used已用的内存

 free剩余的

buffers写缓存

cached读缓存

-buffers/cached 906-62-3

(-buffers/cache) used内存数：286M (指的第一部分Mem行中的used – buffers – cached)  

(+buffers/cache) free内存数: 715M (指的第一部分Mem行中的free + buffers + cached)

 +buffers/cached 73+3+62=139



 所以看系统，真正已经用的内存数：used-(buffers+cached)的值。

​                真正未用到的内存数：free+buffers+cached  的值。

参考：

https://www.cnblogs.com/fanjc/p/9453133.html

https://blog.csdn.net/makang456/article/details/78694120





nmon使用

​    -s    每隔多少秒刷新一次屏幕，就是每隔多少秒记录一次数据

​    -c    刷新次数，就是记录次数

​    -f    电子表格输出格式，形成一个可以以Excel表解读的数据集。

​     -t

​      -x

./nmon -f -s 2 -c 10

采集10次，每隔2s,数据采集到.nmon文件中。

nmon_analyse
