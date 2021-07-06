---
title: Shell基本语句整理
date: 2021-07-06 21:12
---

基本语句
1、if语句
格式1
if 条件；then
 执行语句
fi
或
if 条件；
Then 执行语句
fi

格式2:
多条件
if 条件；then
 执行语句
elif 条件；then
 执行语句
...
else
 执行语句
fi
示例
[root@node1 shell_dmeo]# cat test.sh 
#/bin/bash
echo -n "please input a score:"
read SCORE
if [ $SCORE -lt 60 ]; then
    echo "C"
elif [ "$SCORE" -lt 80 -a "$SCORE" -ge 60 ]; then
    echo "B"
else
    echo "A"
fi
2、for循环
格式1
for var in {}
do
  执行语句
done

格式2
for((i=0;i<xx;i++))
do
 执行语句
done
示例1.
[root@node1 shell_dmeo]# cat exit_shell.sh 
#!/bin/bash
for i in {1..5}
do
  [ $i -eq 3 ] && continue
  echo $i
done
echo over
示例2
[root@node1 shell_dmeo]# cat calculator.sh 
#!/bin/bash
#a calculator dmeo
for((i=1;i<=9;i++))
do
  for((j=1;j<=i;j++))
  do
    echo -n "$i*$j=$[i*j] "
  done
  echo 
done
3、while循环
格式1
while ：
do
  执行语句
  至少需要break或exit，这是一个死循环
done

格式2
while [ 条件 ]
do
  执行语句
done
示例1
[root@node1 shell_dmeo]# cat double_ball.sh 
#!/bin/bash
red_ball=""
blue_ball=""
while :
do
  clear
  echo "chose two color balls"
  tmp=$[RANDOM%33+1]
  echo "$red_ball"|grep -w -q $tmp && continue
  red_ball+=" $tmp"
  echo -en "\033[91m$red_ball\033[0m"
  word=$(echo $red_ball|wc -w)
  if [ $word -eq 6 ]; then
    blue_ball=$[RANDOM%16+1]
    echo -e "\033[34m $blue_ball\033[0m"
    break
  fi
  sleep 0.5
done
示例2
[root@node1 shell_dmeo]# cat travel.sh 
#!/bin/bash
sum=0
i=1
while [ $i -le 100 ]
do
  let sum+=$i
  let i++
done
echo -e "1+2+3+...+100 is: $sum"

4、case语句
case $var in
 xx)
  语句1;;
 yy）
  语句2;;
 *)
   语句3;;
esac
示例1
[root@node1 shell_dmeo]# cat case_demo.sh 
#!/bin/bash
#case demo
read -p "please input redhat|centos:" key
case $key in
	redhat)
		echo "redhat.";;
	centos)
		echo "centos.";;
	*)
		echo "must input redhat or centos";;
esac
5、数组
定义
test=(11 22 33)

取数组元素
取第0个：${test[0]}，即11
取第1个：${test[1]}，即22
取所有元素：${test[@]}或${test[*]}
取数组长度：${#test[*]}或${#test[@]}

示例1
[root@node1 shell_dmeo]# cat array.sh 
#/bin/bash
ar=(10 1 2 3)
echo "all elm of array : ${ar[@]}"
echo "array len is: "${#ar[@]}
echo "arrar[0]: "${ar[0]}
echo "array[1]: "${ar[1]}

示例2
字符串转数组1
[root@node1 shell_dmeo]# ar=$(cat /proc/diskstats |awk '{s+=$6;t+=$4}END{print s,t}')
[root@node1 shell_dmeo]# echo $ar
947120 13776
[root@node1 shell_dmeo]# array=(${ar///})
[root@node1 shell_dmeo]# echo ${array[@]}
947120 13776

字符串转数组2
[root@node1 shell_dmeo]# array=($(echo $ar | awk 'BEGIN{FS=" ";OFS=" "} {print $1,$2}'))
[root@node1 shell_dmeo]# echo ${array[@]}
947120 13776
函数
定义
function关键字可选 name（）{
  函数体
  echo 执行结果
}

示例1
[root@node1 shell_dmeo]# cat add.sh 
#!/bin/bash
#get sum
function add(){
  echo "sum of $1+$2 is :" $[$1+$2]
}

add 1 2
add 3 4
[root@node1 shell_dmeo]# sh add.sh 
sum of 1+2 is : 3
sum of 3+4 is : 7
