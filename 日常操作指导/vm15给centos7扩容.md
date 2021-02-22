# vm15给centos7扩容

#### 困难：根目录磁盘占用100%，现给根目录扩容40G，使总容量达到60GB。

注意：扩容前删除虚拟机快照，这是vm要求的。

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



4、**partprobe**

5、对新增加的硬盘进行格式化
**mkfs.ext3 /dev/sda3**

6、添加新LVM到已有的LVM组，实现扩容
**lvm**
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

8、显示扩容后磁盘大小**df -h**

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





参考链接
https://my.oschina.net/chinaxy/blog/1929221