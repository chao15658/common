# x86服务器配置本地yum源



1.上传镜像至服务器

sftp> put ***.so



2.挂载

mount /root/xx.so /media

查看挂载信息

mount|grep media

```
/dev/sr0 on /media type iso9660 (ro,relatime)

```



3.将挂载命令写入/etc/fstab（最后一行）

[root@node0 ~]# cat /etc/fstab 

```
#

# /etc/fstab

# Created by anaconda on Mon Nov 30 08:44:07 2020

#

# Accessible filesystems, by reference, are maintained under '/dev/disk'

# See man pages fstab(5), findfs(8), mount(8) and/or blkid(8) for more info

#
/dev/mapper/centos-root /                       xfs     defaults        0 0
UUID=5d4685e3-b969-464a-9f87-c88d115b4f42 /boot                   xfs     defaults        0 0
/dev/mapper/centos-swap swap                    swap    defaults        0 0
/dev/sr0 /media iso9660 defaults        0 0
```

4.验证文件编辑正确性

umount /media/ && mount -a /etc/fstab

如果出现目标挂载信息，说明文件修改正确。

注意：该文件格式错误会导致linux系统无法正常启动，因此需要谨慎操作。



5.配置本地yum源

cd /etc/yum.repo.d

编辑内容如下：

cat myrepo.repo

**[myrepo]**

**name=myrepo

**baseurl=file:///media

**enabled=1**

**gpgcheck=0**



6.清除yum缓存

yum clean all



7.安装某个包，以vim为例

yum install -y vim --nogpg



**/etc/fstab文件解释：**

第一列 Device

​    磁盘设备文件或者该设备的Label或者UUID

第二列 Mount point

​    设备的挂载点，就是你要挂载到哪个目录下。

第三列 filesystem

磁盘文件系统的格式，包括ext2、ext3、reiserfs、nfs、vfat等

第四列 parameters

文件系统的参数

| Defaults | 同时具有rw,suid,dev,exec,auto,nouser,async等默认参数的设置 |
| -------- | ---------------------------------------------------------- |
| rw/ro    | 是否以以只读或者读写模式挂载                               |

| auto/noauto | 当下载mount -a 的命令时，此文件系统是否被主动挂载。默认为auto |
| ----------- | ------------------------------------------------------------ |
|             |                                                              |

第五列：能否被dump备份命令作用

​     dump是一个用来作为备份的命令。通常这个参数的值为0或者1

| 0    | 代表不要做dump备份       |
| ---- | ------------------------ |
| 1    | 代表要每天进行dump的操作 |

第六列 是否检验扇区

开机的过程中，系统默认会以fsck检验我们系统是否为完整（clean）。

| 0    | 不要检验                     |
| ---- | ---------------------------- |
| 1    | 最早检验（一般根目录会选择） |





**参考链接**

 https://blog.csdn.net/youmatterhsp/article/details/83933158 