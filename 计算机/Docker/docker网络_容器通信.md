# docker网络_容器通信

## 网络模式
[Docker系列九：Docker网络模式详解及容器间通信_iwester的博客-CSDN博客_docker查看容器网络模式](https://blog.csdn.net/web_snail/article/details/120652290)

## 命令

### 查看网络
`docker network ls`列出docker的所有模式

针对bridge和host分别查找有哪些container在其中:
```cmd
docker network inspect bridge
docker network inspect host
docker network ls
```

### 使用Docker自定义网络
```
创建一个基于 bridge 网络模式的自定义网络模式 new_network
docker network create new_network

通过自定义网络模式 new_network创建容器
docker run -itd --name centos7_07 --network new_network centos:7

查看新建容器网络
docker container inspect centos7_07

为容器扩容其他网络
docker network connect bridge centos7_07

断开容器网络
docker network disconnect bridge centos7_07

移除网络
docker network rm new_network
注意：如果通过某个自定义网络模式创建了容器，则该网络模式无法删除。
```

我的案例：
```cmd
E:\Redis>docker network create newnet
77f464c104d0c867477b891259b0ac176f81cfa35d3ddd00f8f74aae62440933
E:\Redis>docker network connect newnet redisClusterMaster1
```

#### 启动后修改网络
```
#1.启动时设置
docker run -itd --name c3 --net backend centos
docker run -itd --name c2 --net backend centos
docker run -itd --name c1 --net frontend centos
#2.启动后设置
docker network connect 网络名 container名
#查看
docker exec -it c2 /bin/bash
yum install -y net-tools  #安装网络工具包
ping c2      #处于backend 通
ping c3      #处于backend 通
```

### 容器间通信

#### ip问题
不要写 127.0.0.1 用 `docker network inspect bridge` 查询出来的ip，默认应该是从 `172.17.0.2` 开始，然后最后的`.2`开始累加。

## docker compose

### default
默认情况下docker-compose会建立一个默认的网络，名称为docker-compose.yml所在目录名称小写形式加上“_default”，我们的TFLinux环境就是“tflinux_default”。
如果要自定义默认网络可以针对“default”网络进行设置，这样就会影响导默认网络了。
```yml
networks:

  default:
    driver: bridge
```

### 自定义
除了默认网络之外，我们也可以建立自定义的网络，这个网络名称就比较随意了。

```yml
networks:

  persist:
    driver: bridge
```

### 已存在网络
```yml
networks:

  persist:
    external:
      name: bridge2
```

### 案例 创建和使用
[docker_compose](docker_compose.md)

## 本机网络
`host.docker.internal:host-gateway`:
```yml
services:
  proxy1:
    restart: always
    build: 
      context: ./proxy1
      dockerfile: Dockerfile
    ports:
      - "4000:80"
    volumes:
      - "/E/Gdansk University of Technology/fifth_semester/InternetiServicesArchitectures/Lab/Lab7/docker/proxy1/nginx/nginx.conf:/etc/nginx/nginx.conf"
      - "/E/Gdansk University of Technology/fifth_semester/InternetiServicesArchitectures/Lab/Lab7/docker/proxy1/nginx/conf.d/default.conf:/etc/nginx/conf.d/default.conf"
      - "/E/Gdansk University of Technology/fifth_semester/InternetiServicesArchitectures/Lab/Lab7/docker/proxy1/nginx/lognginx:/var/log/nginx"
    extra_hosts:
      - "host.docker.internal:host-gateway"
```