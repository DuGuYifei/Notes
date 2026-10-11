# 让服务器连接本地VPN

本地:

```bash
ssh -N -T -o ExitOnForwardFailure=yes -R 127.0.0.1:1899:127.0.0.1:11304 user@服务器公网IP
```

1899 是服务器端口，11304 是本地VPN代理端口。

服务器:

```bash
export http_proxy=http://127.0.0.1:1899
export https_proxy=http://127.0.0.1:1899
export HTTP_PROXY=http://127.0.0.1:1899
export HTTPS_PROXY=http://127.0.0.1:1899
```

docker

```bash
sudo mkdir -p /etc/systemd/system/docker.service.d

# 若有之前的“禁用代理”配置，先备份移走
if [ -f /etc/systemd/system/docker.service.d/disable-proxy.conf ]; then
  sudo mv /etc/systemd/system/docker.service.d/disable-proxy.conf "/root/docker-disable-proxy.conf.bak.$(date +%Y%m%d%H%M%S)"
fi

# 备份现有代理配置
if [ -f /etc/systemd/system/docker.service.d/proxy.conf ]; then
  sudo cp -p /etc/systemd/system/docker.service.d/proxy.conf "/root/docker-proxy.conf.bak.$(date +%Y%m%d%H%M%S)"
fi

sudo tee /etc/systemd/system/docker.service.d/proxy.conf >/dev/null <<'EOF'
[Service]
Environment="HTTP_PROXY=http://127.0.0.1:1899"
Environment="HTTPS_PROXY=http://127.0.0.1:1899"
Environment="http_proxy=http://127.0.0.1:1899"
Environment="https_proxy=http://127.0.0.1:1899"
Environment="NO_PROXY=localhost,127.0.0.1,::1,10.0.0.0/8,172.16.0.0/12,192.168.0.0/16"
Environment="no_proxy=localhost,127.0.0.1,::1,10.0.0.0/8,172.16.0.0/12,192.168.0.0/16"
EOF
sudo systemctl daemon-reload
sudo systemctl restart docker
docker info --format 'HTTP={{.HTTPProxy}} HTTPS={{.HTTPSProxy}}'
```