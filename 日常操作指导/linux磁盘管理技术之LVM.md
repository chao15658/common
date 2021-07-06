# linux磁盘管理技术之LVM（逻辑卷管理）

LVM在物理硬盘和文件系统增加了一层，它提供了一个抽象的卷组，可以把多块硬盘进行卷组合并。

![1624107471687](C:%5CUsers%5CAdministrator%5CAppData%5CRoaming%5CTypora%5Ctypora-user-images%5C1624107471687.png)

PV：物理卷

VG：卷组

PE：物理单元

LV：逻辑卷

  物理卷处于 LVM 中的最底层，可以将其理解为物理硬盘、硬盘分区或者 RAID 磁盘阵
列，这都可以。卷组建立在物理卷之上，一个卷组可以包含多个物理卷，而且在卷组创建之后
也可以继续向其中添加新的物理卷。逻辑卷是用卷组中空闲的资源建立的，并且逻辑卷在建
立后可以动态地扩展或缩小空间。这就是 LVM 的核心理念。  	



**逻辑卷部署步骤**：

1、创建物理卷

pvcreate 设备路径 

2、创建卷组（一般只创建一个即可）

vgcreate storage /dev/sdb /dev/sdc

或将物理卷添加到现有的卷组

 vgextend centos /dev/sdb /dev/sdc

3、创建逻辑卷

lvcreate -n 名字 -L 大小 vg名

或将现有逻辑卷扩容

格式：

lvextend -L +扩展量 lv完整名

例如：

**lvextend -l+10239 /dev/mapper/centos-root** 



**示例**

**vm给centos虚拟机扩容**

前提：根目录磁盘占用100%，现给根目录扩容40G，使总容量达到60GB。

注意：扩容前删除虚拟机快照，这是vm要求的。

**操作步骤**

0、虚拟机关闭 

1、vm15点击编辑虚拟机设置，扩展，指定虚拟磁盘大小，单位GB

2、启动虚拟机，查看分区
**fdisk -l**，如下所示，为已经添加的/dev/sda3分区，分区类型为8e。

```
[root@node4 ~]# fdisk  -l

Disk /dev/sda: 64.4 GB, 64424509440 bytes, 125829120 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: dos
Disk identifier: 0x000a4a5c

   Device Boot      Start         End      Blocks   Id  System
/dev/sda1   *        2048     2099199     1048576   83  Linux
/dev/sda2         2099200    41943039    19921920   8e  Linux LVM
/dev/sda3        41943040   125829119    41943040   8e  Linux LVM

Disk /dev/mapper/centos-root: 61.2 GB, 61194895360 bytes, 119521280 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes

Disk /dev/mapper/centos-swap: 2147 MB, 2147483648 bytes, 4194304 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
```

3、对新增加的硬盘进行分区，分区类型设置为8e
**fdisk /dev/sda**

4、重读分区表

**partprobe**

5、对新增加的硬盘进行格式化
**mkfs.xfs/dev/sda3**

6、添加新LVM到已有的LVM组，实现扩容
**vgextend centos /dev/sda3**

 **vgdisplay** 
  --- Volume group ---
  VG Name               centos
  System ID             
  Format                lvm2
  Metadata Areas        2
  Metadata Sequence No  4
  VG Access             read/write
  VG Status             resizable
  MAX LV                0
  Cur LV                2
  Open LV               2
  Max PV                0
  Cur PV                2
  Act PV                2
  VG Size               58.99 GiB
  PE Size               4.00 MiB
  Total PE              15102
  Alloc PE / Size       4863 / <19.00 GiB
  Free  PE / Size       10239 / <40.00 GiB
  VG UUID               EmLW8N-hN2u-50UA-C8wi-AhGs-1JWc-FUuJy6

**lvextend -l+10239 /dev/mapper/centos-root**       -l指定的是free PE个数

注意：扩容前要删除大文件，避免主机磁盘占用100%，命令可能会执行失败。

7、执行扩容
 xfs_growfs /dev/mapper/centos-root 

8、显示扩容后磁盘容量

[root@node4 ~]# df -h
Filesystem               Size  Used Avail Use% Mounted on
devtmpfs                 228M     0  228M   0% /dev
tmpfs                    239M     0  239M   0% /dev/shm
tmpfs                    239M  5.5M  234M   3% /run
tmpfs                    239M     0  239M   0% /sys/fs/cgroup
**/dev/mapper/centos-root   57G   17G   41G  30% /**
/dev/sda1               1014M  177M  838M  18% /boot
tmpfs                     48M     0   48M   0% /run/user/0
[root@node4 ~]# 



相关命令参考：

lvdisplay查看逻辑卷列表

pvdisplay查看物理卷列表



#### 磁盘挂载、分区相关（lsblk、fdisk、mount）

1. 列出当前的所有设备

[root@localhost pthread]# lsblk
NAME                        MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
sr0                          11:0    1 1024M  0 rom  
sda                           8:0    0   40G  0 disk 
├─sda1                        8:1    0  500M  0 part /boot
└─sda2                        8:2    0 39.5G  0 part 
  ├─VolGroup-lv_root (dm-0) 253:0    0 37.6G  0 lvm  /
  └─VolGroup-lv_swap (dm-1) 253:1    0    2G  0 lvm  [SWAP]

2. 划分分区

fdisk  /dev/sda

参数介绍

Command (m for help): m
Command action
   a   toggle a bootable flag
   b   edit bsd disklabel
   c   toggle the dos compatibility flag
   d   delete a partition  删除
   l   list known partition types
   m   print this menu
   n   add a new partition  新增加分区
   o   create a new empty DOS partition table
   p   print the partition table 打印分区表
   q   quit without saving changes
   s   create a new empty Sun disklabel
   t   change a partition's system id
   u   change display/entry units
   v   verify the partition table
   w   write table to disk and exit  分区表写到磁盘
   x   extra functionality (experts only)

3.  创建文件系统

 mkfs -t xfs /dev/sda3

参数

-t 指定文件系统类型 

后面跟设备

4.  将子分区挂载到指定目录（/opt/disk3）

mount /dev/sda3 /opt/disk3

5.  分区卸载umount 

通过设备名卸载：umount /dev/sda3卸载分区

通过挂载点卸载：umount /opt/sda3

mount

不接参数mount不加参数，列出已加载文件系统的信息，包括以何种方式进行的加载(例如: rw,ro等 )

[root@localhost pthread]# mount
/dev/mapper/VolGroup-lv_root on / type ext4 (rw)
proc on /proc type proc (rw)
sysfs on /sys type sysfs (rw)
devpts on /dev/pts type devpts (rw,gid=5,mode=620)
tmpfs on /dev/shm type tmpfs (rw,rootcontext="system_u:object_r:tmpfs_t:s0")
/dev/sda1 on /boot type ext4 (rw)
none on /proc/sys/fs/binfmt_misc type binfmt_misc (rw)

6.强制卸载分区

a.查看当前访问分区的进程

fuser /mv device_name或lsof +device_name

杀死当前挂载设备的进程

fuser -kv device_name或使用kill -9 +proc_id



**参考文档**

E:\工作总结\book\编程语言\Linux就该这么学.pdf