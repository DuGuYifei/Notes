# LinuxBash笔记

1. [win下的linux进入win系统盘](#win下的linux进入win系统盘)
2. [Xlaunch 帮助zenity在windows上图形化](#xlaunch-帮助zenity在windows上图形化)
3. [定时任务](#定时任务)
   1. [举例](#举例)
4. [给root账户设置密码](#给root账户设置密码)
5. [进入root账户](#进入root账户)
6. [多行命令](#多行命令)
7. [apt-get](#apt-get)
   1. [卸载](#卸载)
8. [内存占用查询](#内存占用查询)

## win下的linux进入win系统盘
```bash
cd /mnt/e/"Gdansk University of Technology"/"first semester"/"Operating System"/BigScript/Lab6
```

## Xlaunch 帮助zenity在windows上图形化
```bash
DISPLAY=:0 bash **.sh
```

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

## 多行命令

`\`

## apt-get

### 卸载
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

## 内存占用查询
```
free -h
```