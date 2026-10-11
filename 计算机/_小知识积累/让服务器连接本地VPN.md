# 让服务器连接本地VPN

本地:

```bash
ssh -N -T -o ExitOnForwardFailure=yes -R 127.0.0.1:1888:127.0.0.1:11304 user@服务器公网IP
```

1888 是服务器端口，11304 是本地VPN代理端口。

服务器:

```bash
export http_proxy=http://127.0.0.1:1888
export https_proxy=http://127.0.0.1:1888
export HTTP_PROXY=http://127.0.0.1:1888
export HTTPS_PROXY=http://127.0.0.1:1888
```