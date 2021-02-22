# git命令简单介绍

架构简单理解

![img](https://images2015.cnblogs.com/blog/1033579/201703/1033579-20170317195044479-1524873296.png)

我们写代码通常在暂存区（比如IDEA），代码提交总是先要提交到本地仓库（commit），然后推送到远程仓库（push）；

代码拉取时总是从远程仓库拉取到本地（pull）。

代码有多个分支：先merge，再commit到本地仓库，然后在推送到远端仓库。



git add file
将文件添加到暂存区域，以备提交到远程仓库中
git commit
提交代码到本地仓库
git push
从本地仓库推送到远程仓库
git pull
从远程仓库拉取到本地
git clone
复制包括了历史版本的所有版本
git merge
命令用于将两个或两个以上的开发历史加入(合并)一起。
git checkout
恢复文件
git log显示提交日志



git reset

回滚两种策略：

**2. 使用“git reset --hard 目标版本号”命令将版本回退：**

**2.使用“git revert -n 版本号”反做，并使用“git commit -m 版本名”提交：**





git commit 

  -a 提交所有更改的文件到本地仓库

  -m 添加描述信息

git status 

显示索引文件和当前HEAD提交之间的差异。

git rebase

参考：
https://www.cnblogs.com/wnbahmbb/p/6568179.html

<https://blog.csdn.net/yxlshk/article/details/79944535>
