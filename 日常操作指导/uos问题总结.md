1.

信号量报错

![1623391219351](C:%5CUsers%5CAdministrator%5CAppData%5CRoaming%5CTypora%5Ctypora-user-images%5C1623391219351.png)



**问题原因**

造成该问题的原因为参数RemoveIPC被设置为yes。
RemoveIPC参数在/etc/systemd/logind.conf中控制在用户完全注销时是否删除System V IPC对象。
该参数在 systemd 212(2014-03-25)版本中默认打开，RHEL7从219版本开始。显然，RHEL7中的该参数是默认关闭的。
当RemoveIPC = yes时，PostgreSQL服务器使用的信号量对象在随机时间被删除，导致服务器崩溃，出现类似的日志：



**解决办法**

修改/etc/systemd/logind.conf，

RemoveIPC = no

service systemd-logind restart

