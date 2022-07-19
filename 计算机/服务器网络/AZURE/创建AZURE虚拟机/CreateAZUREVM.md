# Create AZURE VM

## 新建一个虚拟机
设置好用户名密码可以在之后省事

## 在linuxBash上SSH连接并做基本设置
[在 Linux 中使用 xrdp - Azure Virtual Machines](https://docs.microsoft.com/zh-cn/azure/virtual-machines/linux/use-remote-desktop)
```bash
ssh azureuser@myvm.westus.cloudapp.azure.com
```

安装xfce界面
```bash
sudo apt-get update
sudo apt-get -y install xfce4
sudo apt install xfce4-session
```

安装和配置远程桌面服务器
```bash
sudo apt-get -y install xrdp
sudo systemctl enable xrdp
echo xfce4-session >~/.xsession
sudo service xrdp restart
```

## 设置本地用户账户密码
不过可以跳过如果第一步里做了
```bash
sudo passwd azureuser
```
## linux里安装AZURE CLI
CLI: Command Line Interface
```bash
curl -sL https://aka.ms/InstallAzureCLIDeb | sudo bash
```

遇到报错和libc-bin有关

参考了下面的\
[该软件包正处于非常不稳定的状态； - Will_D_Zhang - 博客园](https://www.cnblogs.com/bk770466199/p/6430467.html)

```bash
dpkg: 处理软件包 redis-server (--configure)时出错：
/*balabalabala*/
在处理时有错误发生：
 libc-bin
E: Sub-process /usr/bin/dpkg returned an error code (1)
```
于是
```bash
sudo rm /var/lib/dpkg/info/libc-bin.*
```

## 为远程桌面流量创建网络安全组规则
```bash
az vm open-port --resource-group myResourceGroup --name myVM --port 3389
```

## 可以远程连接啦
win+r,输入：mstsc

然后点击显示选项，输入虚拟机的公网IP和你的用户名，步骤一里的那个，最后就会跳转到远程虚拟机让你输入用户名密码登录。

