
1、创建表
create table t_user1(userid int, username varchar(32), loginname varchar(32));

2、在orcale用户目录下启动预先编译好的oci程序
[oracle@node1 chao_20210225]$ ./oci
Oracle environment initialization success!
Oracle server attach success!
user session success!
Create stmt success !
Create stmt success !
insert - Success
数据库中的记录：
1	liming	ming
2	lihuag	hua
3	liulei	lei
 rows :3
update - Success
数据库中的记录：
6	liming	ming
2	lihuag	hua
3	liulei	lei
 rows :3
删除指定的用户信息！请输入需要删除的用户id：
2
delete - Success
数据库中的记录：
6	liming	ming
3	liulei	lei
 rows :2



 解释：
 如上所示，启动oci时插入3行数据，提示insert-Success表示插入成功；
 之后更新1行，将username为liuming的行的userid从1更新为6；
 之后按照提示输入要删除的用户id，提示删除成功，并显示删除后的结果。