

# python调试代码

使用python运行代码的时候指定-m选项，从开始进入调试模式。

python -m pdb $GPHOME/bin/gpcheckperf -f hostfile_exkeys -d /home/gpadmin -r n



bt 打印堆栈

p + var 打印变量值

##### 表 1. pdb 常用命令

|        命令         |            解释            |
| :-----------------: | :------------------------: |
| break 或 b 设置断点 |          设置断点          |
|    continue 或 c    |        继续执行程序        |
|      list 或 l      |     查看当前行的代码段     |
|      step 或 s      |          进入函数          |
|     return 或 r     | 执行代码直到从当前函数返回 |
|      exit 或 q      |         中止并退出         |
|      next 或 n      |         执行下一行         |
|         pp          |        打印变量的值        |
|        help         |            帮助            |



参考：

<http://python.jobbole.com/85668/>