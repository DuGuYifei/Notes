# OpenClaw


## 安装

```bash
git clone git@github.com:openclaw/openclaw.git
# 不想自己build image (3.8G)
export OPENCLAW_IMAGE="ghcr.io/openclaw/openclaw:latest"
# 想自定义工作文件夹的话
OPENCLAW_CONFIG_DIR="${OPENCLAW_CONFIG_DIR:-$HOME/.openclaw}"
OPENCLAW_WORKSPACE_DIR="${OPENCLAW_WORKSPACE_DIR:-$HOME/.openclaw/workspace}"
./docker-setup.sh
# 如果没打开界面
openclaw dashboard --no-open
```

## skill部署

如果你自己创建了skill，直接复制到 skill 目录下即可。然后想加入openclaw的网络，网络名是 `openclaw_default`。

## 问题集结

### wsl docker

```
(node:7) [DEP0040] DeprecationWarning: The `punycode` module is deprecated. Please use a userland alternative instead.

(Use `node --trace-deprecation ...` to show where the warning was created)

2026-03-09T19:23:11.530+00:00 Gateway failed to start: Error: non-loopback Control UI requires gateway.controlUi.allowedOrigins (set explicit origins), or set gateway.controlUi.dangerouslyAllowHostHeaderOriginFallback=true to use Host-header origin fallback mode
```

```sh
# 解决方法
docker compose run --rm openclaw-cli config set gateway.controlUi.allowedOrigins '["http://127.0.0.1:18789","http://localhost:18789", "http://127.0.0.1:18790","http://localhost:18790"]' --strict-json
```

### 报权限问题

发生过，只要`sudo -E ./docker-setup.sh`就好了。

### paired required

```sh
openclaw devices list
openclaw devices approve <requestId>
```

### 删除旧的记录

```sh
rm -rf ~/.openclaw
```

### container里需要权限加载脚本

用root进去container

```sh
docker exec -it --user root openclaw-openclaw-gateway-1 bash
```