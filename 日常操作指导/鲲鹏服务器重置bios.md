# 华为鲲鹏服务器恢复出厂设置

**操作前提：**

打开服务器盖子，短接对应的两个接口

**操作步骤：**

1.使用win 10自带的SCP命令，往HDM的 /tmp文件夹上传R4960-BIOS-1.72.hpm，输入默认密码Password@_

scp R4960-BIOS-1.72.hpm admin@192.168.1.2:/tmp



2.将服务器关机，使用SSH工具登录HDM

3.输入以下命令，升级BIOS固件，恢复BIOS默认配置

ipmcset -t maintenance -d upgradebios -v /tmp/R4960-BIOS-1.72.hpm

默认密码恢复之后，使用密码：admin@9000登录bios



参考文件

file:///E:/BaiduNetdiskDownload/Case%2005176973%20-%20QQMail.html

