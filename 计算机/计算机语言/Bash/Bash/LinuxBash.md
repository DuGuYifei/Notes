# LinuxBash笔记

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