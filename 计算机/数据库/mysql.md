# mysql

1. [linux](#linux)
   1. [安装](#安装)
   2. [让root远程可访问](#让root远程可访问)
2. [要允许访问 mysql 端口](#要允许访问-mysql-端口)
   1. [数据库管理](#数据库管理)
3. [查询端口号](#查询端口号)
4. [查询用户](#查询用户)
5. [数据库管理](#数据库管理-1)
   1. [备份与回复](#备份与回复)
   2. [创建与删除内容](#创建与删除内容)

## linux
写在前面：
host的`%`指的是任何主机的ip，但不包括本机，即localhost和127.0.0.1
### 安装
[How To Install MySQL on Ubuntu 20.04  | DigitalOcean](https://www.digitalocean.com/community/tutorials/how-to-install-mysql-on-ubuntu-20-04)

[Ubuntu下的MySQL数据库_m0_63228448的博客-CSDN博客_ubuntu查看mysql数据库](https://blog.csdn.net/m0_63228448/article/details/121739771)

------------------------------------------------
```bash
sudo apt update # 更新源
sudo apt install mysql-server
sudo systemctl start mysql.service # 确保服务器正在运行
```
------------------------------------------------

安全保护
**root是否靠用户名密码登录**，

**注意ubuntu默认不支持root密码登录，哪怕sudo passwd也不行，需要其他操作：** [ubuntu 设置root用户密码并实现root用户登录 - CharyGao - 博客园](https://www.cnblogs.com/Chary/p/14849542.html)

* 如果是，则直接：
```bash
sudo mysql_secure_installation
```

* 如果不是，则
```bash
sudo mysql
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';
exit
sudo mysql_secure_installation
# 安全脚本完成后，您可以重新打开 MySQL 并将根用户的身份验证方法更改回默认值 auth_socket 。要使用密码以根MySQL用户的身份进行身份验证，请运行以下命令：
# mysql -u root -p
# ALTER USER 'root'@'localhost' IDENTIFIED WITH auth_socket;
# 输入密码，然后所有问题都选 Y
```
------------------------------------------------

启动MySQL服务

* 第一个教程：
```bash
# 在上面就已经进行了，这里只是粘贴对比
sudo systemctl start mysql.service # 确保服务器正在运行
```

* 第二个教程
  * 方法1
```bash
/etc/init.d/mysql start  启动
/etc/init.d/mysql stop   停止
/etc/init.d/mysql restart 重启
/etc/init.d/mysql status  查看状态
```
  * 方法2
```bash
service mysql start  启动
service mysql stop   停止
service mysql restart 重启
service mysql status  查看状态
```
------------------------------------------------

运行MySQL
* 教程一：
在运行 MySQL 5.7（及更高版本）的 Ubuntu 系统中，root MySQL 用户默认设置为使用 auth_socket 插件进行身份验证，而不是使用密码。 此插件要求**调用 MySQL 客户端的操作系统用户名与命令中指定的 MySQL 用户名相匹配**，因此您必须使用 sudo 权限调用 mysql 才能获得对 MySQL 根用户的访问权限：
```bash
sudo mysql
```
如果您使用另一个教程安装了 MySQL 并为 root 启用了密码验证，您将需要使用不同的命令来访问 MySQL shell。 以下将以常规用户权限运行您的 MySQL 客户端，并且您只能通过身份验证获得数据库内的管理员权限：
正如教程二

* 教程二：
```bash
mysql -u root -p
```
------------------------------------------------

创建用户并授予权限

```bash
CREATE USER 'username'@'host' IDENTIFIED BY 'password';
```
GRANT privileges ON databasename.tablename TO ‘username’@‘host’；
```bash
GRANT ALL ON *.* TO 'username'@'%';
```

**privileges：用户的操作权限，如SELECT，INSERT，UPDATE等，如果要授予所的权限则使用ALL**


**补充**各种操作权限：
```bash
GRANT CREATE, ALTER, DROP, INSERT, UPDATE, DELETE, SELECT, REFERENCES, RELOAD on *.* TO 'sammy'@'localhost' WITH GRANT OPTION;
```

databasename：数据库名

tablename：表名，如果要授予该用户对所有数据库和表的相应操作权限则可用 * 表示，如*.*

------------------------------------------------

删除用户
```bash
drop user 'carl'@'%';
```

### 让root远程可访问 
方发1：
[How To Allow Remote Access to MySQL  | DigitalOcean](https://www.digitalocean.com/community/tutorials/how-to-allow-remote-access-to-mysql)

要允许访问 mysql 端口
-----------------------------------------------------
**来自于教程二，如果根据教程一，则可以只要第一步**

**注意当时可能已经设置为 % 了**

1. 更新root@localhost为 root@%
```bash
update mysql.user set host = '%' where user ='root' limit 1;

GRANT ALL PRIVILEGES ON *.* TO 'ubuntu'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;
GRANT ALL ON *.* TO 'username'@'%';
```

2. 修改监听地址
```bash
vim /etc/mysql/mysql.conf.d/mysqld.cnf
```
将bind 127.0.0.1这行注释掉 （也有可能是改成0.0.0.0，待尝试）

3. 修改root密码验证方式
```bash
update mysql.user set authentication_string=PASSWORD('123'),plugin='mysql_native_password' where user='root';
```

配置完后，刷新配置并重启mysql服务

```bash
/etc/init.d/mysql restart 

```

服务器需要允许访问 mysql （默认3306） 端口。
比如腾讯云要在防火墙中添加，自制服务器应该直接用命令就行。


### 数据库管理
[Ubuntu下的MySQL数据库_m0_63228448的博客-CSDN博客_ubuntu查看mysql数据库](https://blog.csdn.net/m0_63228448/article/details/121739771)

## 查询端口号
默认3306
```bash
netstat -anp|grep mysql
```
或进入mysql：
```sql
show global variables like 'port';
```


## 查询用户
```SQL
SELECT USER, HOST FROM mysql.user
```

该表中 grant_priv 是grant权限，grant是授权权限

## 数据库管理

### 备份与回复
```bash
mysqldump [OPTIONS] database [tables]
 
例子
mysqldump -h 192.168.1.200 -u root –p123456 wdg >/home/wdg/wdg.sql 
恢复数据库
mysql -u root –p123456 wdg < /home/wdg/wdg.sql 
```

### 创建与删除内容
| 代码                      | 作用                 |
| ------------------------- | -------------------- |
| show databases;           | 显示所有数据库       |
| use 数据库名;             | 切换到某个数据库     |
| show tables;              | 显示某个数据库里的表 |
| create database 数据库名; | 创建                 |
| drop database 数据库名;   | 删除                 |