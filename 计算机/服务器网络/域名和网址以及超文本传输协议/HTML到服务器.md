# 访问服务器中的网页

## 把写好的网页放进服务器

## 直接访问（肯定失败）
在浏览器输入`ip/文件夹名/文件名`

## 为什么直接访问不行

查看80端口的占用
```bash
netstat -ntlp
```

不显示80端口被占用

需要web服务器软件提供网站访问能力

- nginx
- apache

## 安装nginx
```bash
sudo apt install nginx
```

## 启动nginx
```bash
nginx
```

遇到问题
```bash
the "user" directive makes sense only if the master process runs with super-user privileges, ignored in /etc/nginx/nginx.conf:1
```
因为没有权限，所以sudo就行了
或者进入 root 权限

## 访问ip可以成功了现在

## 修改nginx配置文件
nginx配置中root的位置改为你想让它通过ip访问的文件夹

```bash
cd /etc/nginx
vim ngix.conf
```

修改或添加：
```bash
server {
    listen       80 default_server;
    listen       [::]:80 default_server;
    server_name  _;
    root         /usr/share/nginx/html;
}
```

有时候不在nginx.conf文件中\
但是该文件中http里有include\
根据include的位置打开相应文件可以找到server设置\
并获得root默认位置信息\
大概率这个文件名是default