# LinuxBash笔记

1. [win下的linux进入win系统盘](#win下的linux进入win系统盘)
2. [DISPLAY](#display)
   1. [Xlaunch 帮助在windows上图形化](#xlaunch-帮助在windows上图形化)
3. [命令中包含含号](#命令中包含含号)
4. [定时任务](#定时任务)
   1. [举例](#举例)
5. [给root账户设置密码](#给root账户设置密码)
6. [进入root账户](#进入root账户)
7. [vim](#vim)
8. [多行命令](#多行命令)
9. [安装卸载包管理](#安装卸载包管理)
   1. [apt-get](#apt-get)
      1. [卸载](#卸载)
   2. [dpkg 安装包管理](#dpkg-安装包管理)
10. [内存占用查询](#内存占用查询)
11. [磁盘空间](#磁盘空间)
12. [清理缓存](#清理缓存)
13. [~路径](#路径)
14. [url下载](#url下载)
15. [mv 移动/重命名](#mv-移动重命名)
    1. [移动](#移动)
    2. [重命名](#重命名)
16. [解压和压缩](#解压和压缩)
    1. [解压](#解压)
17. [mkdir 创建文件夹](#mkdir-创建文件夹)
18. [rm 删除](#rm-删除)
19. [ls](#ls)
20. [显示整个路径名](#显示整个路径名)
21. [查询私有ip](#查询私有ip)
22. [解决ssh连接后显示为 \[。。@。。 ~\]](#解决ssh连接后显示为--)
23. [服务器](#服务器)
24. [查询命令位置](#查询命令位置)
25. [{ }](#-)
26. [seq](#seq)
27. [cut](#cut)
28. [tr](#tr)
29. [uniq和sort](#uniq和sort)
30. [awk](#awk)
    1. [NR NF FNR](#nr-nf-fnr)
    2. [BEGIN END for循环](#begin-end-for循环)
31. [grep](#grep)
    1. [grep -P](#grep--p)
32. [tail head](#tail-head)
33. [sed](#sed)
34. ['s///g'](#sg)

## win下的linux进入win系统盘
或者直接在问价夹导航栏里输入`bash`就像输入`cmd`打开command一样。
```bash
cd /mnt/e/"Gdansk University of Technology"/"first semester"/"Operating System"/BigScript/Lab6
```
## DISPLAY
```
DISPLAY=ip:0.0
```
0.0 是默认主显示器

### Xlaunch 帮助在windows上图形化
```bash
DISPLAY=:0 bash **.sh
```

## 命令中包含含号
用转义字符`\(\)`

## 定时任务
crontab -e 编辑
crontab -l 查看
crontab -r 删除

分 时 日 月 周 指令串
`*` 任意
`,` 和
`-` 到
`/` 后面跟数字表示每隔

### 举例
1. 每天晚上十点定时关机 
```
* 22 * * * shutdown now
```

2. 每天早上8点和10点定时拷贝文件1到目录1中
```
* 8,10 * * * cp file1 dir1
```

3. 每天每隔五分钟把服务器内存的实时情况输入到文件file1中
```
*/5 * * * * free -h >> file1
```

## 给root账户设置密码
```bash
sudo password
```

但是ubuntu默认不支持root密码登录，需要其他操作：[ubuntu 设置root用户密码并实现root用户登录 - CharyGao - 博客园](https://www.cnblogs.com/Chary/p/14849542.html)

## 进入root账户
```
sudo su
```

## vim
[vim](vim.md)

## 多行命令

`\`

## 安装卸载包管理

### apt-get
#### 卸载
[Ubuntu apt-get彻底卸载软件包_享学IT的博客-CSDN博客_卸载软件包](https://blog.csdn.net/get_set/article/details/51276609)
```bash
# 删除软件及其配置文件
apt-get --purge remove <package>
# 删除没用的依赖包
apt-get autoremove <package>
# 此时dpkg的列表中有“rc”状态的软件包，可以执行如下命令做最后清理：
dpkg -l |grep ^rc|awk '{print $2}' |sudo xargs dpkg -P
```

当然如果要删除暂存的软件安装包，也可以再使用clean命令。
```bash
apt-get clean
```

### dpkg 安装包管理
查询包
```bash
dpkg -l | grep "软件或者包的名字"
```

## 内存占用查询
```
free -h
```

## 磁盘空间
```
df -hl
```

## 清理缓存
```
free -h
sync
echo 3 > /proc/sys/vm/drop_caches
free -h
```

## ~路径
~ 就是root文件夹

## url下载
```bash
wget url
```
如果`Unable to locally verify the issuer's authority`就是root文件夹
```bash
wget url --no-check-certificate
```

## mv 移动/重命名
### 移动
```
mv 文件名 另一个目录
mv 子文件夹/* 另一个目录
```

### 重命名
```
mv origin.txt later.txt
```

## 解压和压缩

### 解压
```
unzip file.zip
```

## mkdir 创建文件夹
创建文件夹

## rm 删除
```
rm -rf 目录名字   
```

-r 向下递归，不管有多少级目录，一并删除。

-f 直接强行删除，没有任何提示。

## ls
隐藏文件
`ls -a`

## 显示整个路径名
`pwd`

## 查询私有ip
```
ip addr show
```

## 解决ssh连接后显示为 [。。@。。 ~]
输入`bash` 有时是`sh`

## 服务器
[ssh命令连接服务器](../../../服务器网络/云服务器知识积累/ssh命令连接服务器.md)
[物理机与虚拟机文件互传](../../../服务器网络/云服务器知识积累/物理机与虚拟机文件互传.md)

## 查询命令位置
`whereis`

## { }
`{ }`在 bash 中是 brace explansion(括号展开) 的意思。
如 `mkdir redis-637{4,5,6}` 会生成 `redis-6374、redis-6375、redis-6376` 这 3 个文件夹

```bash
$ echo {0..10}
0 1 2 3 4 5 6 7 8 9 10

$ {0..10}
bash: 0: command not found # 这里的问题

$ echo {0..10..2}
0 2 4 6 8 10
```

## seq
seq：用于产生从某个数到另外一个数的所有整数

例如：

seq 5  ------------ 1 \n 2 \n 3 \n 4 \n 5 （默认从1开始）
seq -1  ------------ 1 \n 0 \n -1
seq 2 5  ------------ 2 \n 3 \n 4 \n 5
seq 5 -1  ------------ 5 \n 4 \n 3 \n 2 \n 1 \n 0 \n -1


参数：

-f --format（default：%g）
-s --separator（default：\n）
-w --equal


-f：
例如：
%后指定数字位数，default：%g
```bash
seq -f"%3g" 9 11
9
10
11

seq -f"%03g" 9 11

009
010
011

seq -f"str%03g" 9 11     %前指定字符串前缀

str009
str010
str011
```

-w    指定同宽，不能和-f同时用
例如：
```bash
seq -w 98 101

098
099
100
101
```

-s    指定分隔符，default：\n
例如：
```
seq -s" " -f"str%03g" 9 11

str009  str010  str011
```

————————————————
版权声明：本文为CSDN博主「冯智」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_15394121/article/details/77777865

## cut
```bash
cut -d ' ' -f 1-5
cut -d ' ' -f 1,5
```

## tr
```bash
# 将空格换位换行
tr -s ' ' '\n'
```

## uniq和sort
```bash
# 先sort是因为uniq -c统计的是重复出现的行
# sort -r 反向排序
sort|uniq -c|sort -r
```

## awk
* $0 代表整个文本行；
* $1 代表文本行中的第 1 个数据字段；
* $2 代表文本行中的第 2 个数据字段；
* $n 代表文本行中的第 n 个数据字段。
```bash
# 这样两个变量中间没空格
awk '{print $1$2}'
# 这样两个变量中间有空格
awk '{print $1,$2}'
```

```bash
# 正则查询
awk '/^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$/' file.txt
```

### NR NF FNR
NR是指awk正在处理的记录位于文件中的位置（行号）
NF是指awk正在处理的记录包含几个域（字段），这于域分隔符有关，默认为空格
在awk处理多个输入文件的时候，在处理完第一个文件后，NR并不会从1开始，而是继续累加，因此就出现了FNR，每当处理一个新文件的时候，FNR就从1开始计数，`FNR`可以理解为`File Number of Record`。

```bash
September 2003 # NR=1;NF=2
Su Mo Tu We Th Fr Sa # NR=2;NF=7
1 2 3 4 5 6 # NR=3;NF=6
7 8 9 10 11 12 13 # NR=4;NF=7
14 15 16 17 18 19 20 # NR=5;NF=7
21 22 23 24 25 26 27 # NR=6;NF=7
28 29 30 # NR=7;NF=3
```

```bash
CodingAnts@ubuntu:~/awk$ cat class1
zhaoyun 85 87
guanyu 87 88
liubei 90 86

CodingAnts@ubuntu:~/awk$ cat class2
caocao 92 87 90
guojia 99 96 92

CodingAnts@ubuntu:~/awk$ awk '{print NR,$0}' class1 class2
1 zhaoyun 85 87
2 guanyu 87 88
3 liubei 90 86
4 caocao 92 87 90
5 guojia 99 96 92

CodingAnts@ubuntu:~/awk$ awk '{print FNR,$0}' class1 class2
1 zhaoyun 85 87
2 guanyu 87 88
3 liubei 90 86
1 caocao 92 87 90
2 guojia 99 96 92
```

### BEGIN END for循环
在Unix awk中两个特别的表达式，BEGIN和END，这两者都可用于pattern中（参考前面的awk语法），提供BEGIN和END的作用是给程序赋予初始状态和在程序结束之后执行一些扫尾的工作。
* 通常使用BEGIN在循环文件之前设置变量；
* 使用END来输出最终结果。

```bash
awk
'BEGIN {print "统计销售金额";total=0} # 输出提示语"统计销售金额"，并设置total变量为0
{print $3;total=total+$3;}  # 逐行扫描文件
END {print "销售金额总计",total}' file.txt # 在扫描文件之后执行，打印total变量
```

```bash
awk '{
        for (i=1;i<=NF;i++){
            if (NR==1){
                res[i]=$i
            }
            else{
                res[i]=res[i]" "$i
            }
        }
    }END{
        for(j=1;j<=NF;j++){
            print res[j]
        }
    }' file.txt
```

```bash
awk -F ',' '{
    if($2<=365)
        print $0
}' signing_in.csv > signing_in_2015.txt

awk -F ',' '{
    if($2>365 && $2<=731)
        print $0
}' signing_in.csv > signing_in_2016.txt

awk -F ',' '{
    if($2>731 && $2<=1096)
        print $0
}' signing_in.csv > signing_in_2017.txt

awk -F ',' '{
    if($2>1096 && $2<=1461)
        print $0
}' signing_in.csv > signing_in_2018.txt

awk -F ',' '{
    if($2>1461 && $2<=1826)
        print $0
}' signing_in.csv > signing_in_2019.txt

awk -F ',' '{
    if($2>1826 && $2<=2192)
        print $0
}' signing_in.csv > signing_in_2020.txt

awk -F ',' '{
    if($2>2192 && $2<=2557)
        print $0
}' signing_in.csv > signing_in_2021.txt
```

## grep

### grep -P
正则表达式(regular expression)描述了一种字符串匹配的模式，可以用来检查一个串是否含有某种子串、将匹配的子串做替换或者从某个串中取出符合某个条件的子串等。

Perl语言的正则表达式功能非常强大，基本上是常用语言中最强大的，很多语言设计正则式支持的时候都参考Perl的正则表达式。

Perl的正则表达式的三种形式，分别是匹配，替换和转化:

匹配：m//（还可以简写为//，略去m）

替换：s///

转化：tr///
```
grep -P '^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$' file.txt
```

## tail head
* `-n +10`    表示从第 10 行开始显示
* `-n 10`或`-10`     表示显示最后的 10 行
* `-c NUM`    显示指定NUM个字节的内容
* `-c +NUM`   从第NUM个字节开始显示整个文件内容

## sed

## 's///g'
注意：
1. 用`\(\)`将要作为变量的包裹起来
2. `\0`表示整个匹配值
3. `\1`等表示用括号括起来的匹配值
4. 修改的字符串使用变量`\1`等时，若匹配时正则有两个`\(.*\)`，应注意，可能会被扔到第二行，如`cat employee.txt|sed 's/\(.*\),\([M,F]\)\(.*\)\([0-9]*\|[0-9]*\)/\1\3\2\4/g'`

```bash
# 将 "from 数字 to 数字" 改成 "数字|数字","more than 数字" 改成 "数字|1000"
cat employee.csv|sed 's/from \([0-9]*\) to \([0-9]*\)/\1|\2/g'|sed 's/more than \([0-9]*\)/\1|1000/g'>employee.txt

# 注意这里必须输出到一个新文件，不然会变成空
cat employee.txt|sed 's/\(.*\),\([M,F]\)\(,.*-[0-9]\{4\},\)\([0-9]*|[0-9]*\)/\1\3\4\|\2/g'>employee1.txt
```