# ssh命令连接服务器

## log in
linux：
```bash
ssh 用户名@公共ip地址
```

## log out
方法1. ctrl + d 

方法2. 输入logout

## 图形
[ssh_q_X连接并将远程图形化到本地windows和linux](ssh_q_X连接并将远程图形化到本地windows和linux.md)

## 服务器存储ssh公钥的位置
`~/.ssh/authorized_keys`

## 服务器以允许 SSH 代理连接和转发流量
1. 安装和配置 SSH 服务器：确保您的服务器上安装了 SSH 服务器软件，例如 OpenSSH。在大多数 Linux 发行版中，可以使用包管理工具安装 OpenSSH。安装完成后，打开 SSH 服务器的配置文件，通常位于 `/etc/ssh/sshd_config`，并进行以下配置更改：

启用代理转发：确保 `AllowTcpForwarding` 选项设置为 `yes`。如果该行存在但被注释掉了（以 # 开头），请删除注释符号。
（可选）更改 SSH 监听端口：如果您想使用非默认的 SSH 端口（默认为 22），可以修改 Port 选项来更改 SSH 服务器的监听端口。

2. 重启 SSH 服务器：保存并关闭 SSH 配置文件后，重新启动 SSH 服务器，以使配置更改生效。在大多数 Linux 发行版中，可以使用以下命令重启 SSH 服务器：
   ```bash
   sudo service ssh restart
   ```

## 创建代理隧道
### -D
```bash
ssh -D 6666 user@server-ip
```
### config
```bash
Host server
    HostName server-ip
    User user
    DynamicForward 6666
```