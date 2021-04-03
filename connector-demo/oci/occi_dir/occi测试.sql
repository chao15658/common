
1、创建表
create table t_user(userid int, username varchar(32), loginname varchar(32));

2、在oracle用户目录下启动occi
[oracle@node1 chao_20210225]$ ./occi 
insert - Success
insert - Success
insert - Success
数据库中的记录：
userid: 3	username: jack	loginname: jk	
userid: 2	username: rose	loginname: rs	
userid: 1	username: john	loginname: jj	
update - Success
userid: 6	username: jack	loginname: jk	
userid: 2	username: rose	loginname: rs	
userid: 1	username: john	loginname: jj	
删除指定id的用户信息！请输入需要删除的用户id：
1
delete - Success
删除指定id的用户信息后！
userid: 2	username: rose	loginname: rs	
userid: 6	username: jack	loginname: jk	
调用析构函数进行处理！

解释：
 如上所示，启动oci时插入3行数据，提示insert-Success表示插入成功；
 之后更新1行，将username为jack的行的userid从3更新为6；
 之后按照提示输入要删除的用户id，提示删除成功，并显示删除后的结果。
