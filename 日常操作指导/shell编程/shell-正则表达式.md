**大致分类**

基本正则

扩展正则

Perl支持的正则



**基本正则**

^开头

$结尾

.匹配任意单个字符

*重复前面的字符0-无穷次

.*任意字符

\{2,\4} 匹配2-4次

{2,}匹配2次以上

\{2\}匹配2次

[abc]匹配a或b或c

[^abc]匹配不是a或b或c

示例

1、过滤abc开头的行

[root@node0 ~]# grep ^abc /etc/passwd

2、过滤bash结尾的行

[root@node0 ~]# grep bash$ /etc/passwd

3、过滤包含a或b或c的行

[root@node0 ~]# grep "[abc]" /etc/passwd

4、过滤不包含abc的行

[root@node0 ~]# grep "[^abc]/etc/passwd

5、过滤数字出现3-4次的行

[root@node0 ~]# grep "[0,9]\{3,4\}" /etc/passwd

**扩展正则**

grep -E开启扩展正则

?匹配前面字符0或1次

+匹配前面字符至少1次

{2,4}匹配2-4次

{2，}匹配至少2次

{2}匹配2次

|或

()组合或保留

示例

1、匹配0，2-3次

[root@node0 ~]# grep -E "0{2,3}" /etc/passwd

2、匹配小写字母至少1次

[root@node0 ~]# grep -E "[a-z]+" /etc/passwd

3、匹配bin或sbin

[root@node0 ~]# grep -E "s?bin" /etc/passwd

4、匹配root或daemon

 grep -E "(root|daemon)" /etc/passwd

5、匹配2次ab

[root@node0 ~]# echo "ababc"|grep -E "(ab){2}"

**Perl支持的正则**

-P开启Perl语言支持的正则

\b匹配单词边界

\d匹配数字

\d+匹配多数字

\D匹配非数字

\w匹配字符数字下划线

\W匹配非字符数字下划线

\s匹配空白

示例

1、匹配bin

[root@node0 ~]# grep -P "\bbin\b" /etc/passwd

2、匹配字符数字下划线

[root@node0 ~]# grep -P "\w" /etc/passwd

3、匹配多个数字

[root@node0 ~]# grep -P "\d+" /etc/passwd

4、匹配空白

[root@node0 ~]# grep -P "\s" /etc/passwd

**grep常用选项**

-v反向选择

-n显示行号

-r递归的过滤目录

-i忽略大小写

-P支持perl正则

-E支持扩展正则

-q安静默认，标准输出不打印匹配结果

-w匹配单词

