# linux性能分析工具使用

## perf

These are some examples of using the [perf](https://perf.wiki.kernel.org/index.php/Main_Page) Linux profiler, which has also been called Performance Counters for Linux (PCL), Linux perf events (LPE), or perf_events. Like [Vince Weaver](http://web.eece.maine.edu/~vweaver/projects/perf_events/), I'll call it perf_events so that you can search on that term later. Searching for just "perf" finds sites on the police, petroleum, weed control, and a [T-shirt](http://www.brendangregg.com/perf_events/omg-so-perf.jpg). This is not an official perf page, for either perf_events or the T-shirt.

perf_events is an event-oriented observability tool, which can help you solve advanced performance and troubleshooting functions. Questions that can be answered include:

- Why is the kernel on-CPU so much? What code-paths?
- Which code-paths are causing CPU level 2 cache misses?
- Are the CPUs stalled on memory I/O?
- Which code-paths are allocating memory, and how much?
- What is triggering TCP retransmits?
- Is a certain kernel function being called, and how often?
- What reasons are threads leaving the CPU?

perf_events is part of the Linux kernel, under tools/perf. While it uses many Linux tracing features, some are not yet exposed via the perf command, and need to be used via the ftrace interface instead. My [perf-tools](https://github.com/brendangregg/perf-tools)collection (github) uses both perf_events and ftrace as needed.



### perf-record  - 运行命令并将其配置文件记录到perf.data中

-e, --event=  - 指定要关注的事件（其中之一是使用perf list列出的事件）	

perf record -e=sched_process_exit 捕获命令退出的系统调用事件

### perf-script  - 读取perf.data（由perf记录创建）并显示跟踪输出



### 使用基本流程：

#### 先开启perf，记录当前系统范围所有退出事件

perf record -e sched:sched_process_exit

#### 执行某个系统操作。

比如df -h，然后接着执行一个dd if=/dev/zero of=/dev/null count=500000 bs=1M

#### 停止perf，执行perf scripts读取记录结果

 df  2425 [000]  4934.005589: sched:sched_process_exit: comm=df pid=2425 prio=120
 dd  2426 [000]  4971.417555: sched:sched_process_exit: comm=dd pid=2426 prio=120

### perf record参数

### 常用选项

> -e record指定PMU事件
>     --filter  event事件过滤器
> -a  录取所有CPU的事件
> -p  录取指定pid进程的事件
> -o  指定录取保存数据的文件名
> -g  使能函数调用图功能
> -C 录取指定CPU的事件

示例：

perf record -F 99 -p 3887 -g -- sleep 30

perf record 表示采集系统事件, 没有使用 -e 指定采集事件, 则默认采集 cycles(即 CPU clock 周期), -F 99 表示每秒 99 次, -p 13204 是进程号, 即对哪个进程进行分析, -g 表示记录调用栈, sleep 30 则是持续 30 秒.



###  perf report -n --stdio

为了便于阅读, `perf record` 命令可以统计每个调用栈出现的百分比, 然后从高到低排列.

### 生成性能火焰图

FlameGraph下载

git clone https://github.com/brendangregg/FlameGraph.git

perf script | FlameGraph/stackcollapse-perf.pl | FlameGraph/flamegraph.pl > process.svg

svg文件可用浏览器打开查看



#### 基本使用步骤：

1、记录信息

perf record -F 99 -p 9886 -g

2、读取perf.data（由perf记录创建）并显示跟踪输出

perf script -i perf.data &> perf.unfold

3、生成火焰图

perf script | FlameGraph/stackcollapse-perf.pl | FlameGraph/flamegraph.pl > process.svg

将process.svg发送到windows，用浏览器打开可看到预期效果。

#### 示例2：

##### 记录某个进程

 perf record -p 10910 -avg -- sleep 10

##### 查看

普通模式：

perf report

E用于展开，C用于折叠

详细模式:

 perf report -v -n --showcpuutilization -g --stdio

## sysdig

抓取进程交互信息。

-cl 列出所有的凿子（工具）

-i + chisel 显示某个chisel 详细信息

echo_fds        Print the data read and written by processes.（打印进程读写的数据）



-c指定凿子

   evt.type 事件类型

   proc.name= 进程名

例子：

1、捕获本机，dd命令的读事件

   sysdig -c echo_fds proc.name=dd evt.type=read

2、捕捉gpmmon进程的写事件，将捕捉日志重定向到gpmmon.log中。

sysdig -c echo_fds proc.name=gpmmon evt.type=write > ./gpmmon.log

## strace



## pstack

 **pstack命令**可显示每个进程的栈跟踪。pstack 命令必须由相应进程的属主或 `root` 运行。可以使用 pstack 来确定进程挂起的位置。此命令允许使用的唯一选项是要检查的进程的 `PID`。 

## lsof

查看端口使用情况

## netstat

查看端口占用情况

## gdb

实时跟踪进程



参考部分：

<http://www.brendangregg.com/perf.html>

