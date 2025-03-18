# proxy

[代理和反向代理](../服务器知识积累/代理_Proxy和反向代理_ReverseProxy.md)

## proxy_pass
代理本地
```conf
server {
    listen       80;
    listen  [::]:80;
    server_name  localhost;

    location / {
        root   /usr/share/nginx/html;
        index  index.html index.htm;
    }

    location /api/ {
        proxy_pass http://localhost:8080;
    }
}
```
代理其他服务器
```conf
server {
    listen       80;
    listen  [::]:80;
    server_name  localhost;

    location / {
        proxy_pass http://172.17.0.2:80;
    }
}
```

## proxy_redirect
用于重定向：
即会改变用户浏览器地址栏的地址
```conf
location / {
    proxy_redirect http://localhost:8000/two/ http://frontend/one/;
}
```

## proxy_set_header proxy_pass_request_header/body
一个修改header，一个传原本header/body
```conf
proxy_set_header Host       $proxy_host;
proxy_pass_request_headers off;
proxy_pass_request_body on;
```