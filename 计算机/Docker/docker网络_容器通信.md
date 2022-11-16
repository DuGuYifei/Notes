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