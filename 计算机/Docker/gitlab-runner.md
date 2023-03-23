# gitlab-runner

## 1. 安装
```bash
docker run -d --name gitlab-runner --restart always  -v /var/run/docker.sock:/var/run/docker.sock -v /E/DockerFolder/gitlab_runner/gitlab-runner-config:/etc/gitlab-runner gitlab/gitlab-runner:latest
```

最重要的就是 `/var/run/docker.sock`别瞎只因BA改

## 2. 注册
```bash
docker run --rm -it -v /E/DockerFolder/gitlab_runner/gitlab-runner-config:/etc/gitlab-runner gitlab/gitlab-runner register

# 在内部
gitlab-runner register
```

* `--docker-volumes` 是 GitLab Runner 特有的参数，用于在 runner container 中挂载 Docker 的 volumes，使得 runner 能够通过 Docker 运行其他 container。
* `--docker-dns`是在GitLab Runner注册Docker执行器时使用的选项之一，用于设置Docker容器使用的DNS服务器地址。当容器启动时，它将使用此选项中指定的DNS服务器作为默认DNS服务器。这对于在Docker容器内部进行网络连接和访问互联网非常有用。

## 3. 重启
```bash
docker restart gitlab-runner
```