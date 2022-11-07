# KeyValueDatabase_Redis

## Redis
### docker 运行Redis
[【愚公系列】2022年05月 Docker容器 Windows11上Redis的安装 - 腾讯云开发者社区-腾讯云](https://cloud.tencent.com/developer/article/1990739)

* 绑定挂载
* 
```bash
docker run --name redis -p 6379:6379 -v /E/Redis/conf/redis.conf:/etc/redis/redis_6379.conf -v /E/Redis/data:/data/ -d redis:latest redis-server /etc/redis/redis_6379.conf --appendonly yes
```
参数说明
* –name="容器新名字"：为容器指定一个名称
* -p: 指定端口映射，格式为：主机(宿主)端口:容器端口
* -d: 后台运行容器，并返回容器ID
* -v /D/docker/redis/conf/redis.conf:/etc/redis/redis_6379.conf 把宿主机配置好的redis.conf放到容器内的这个位置中
* -v /D/docker/redis/data:/data/ 把redis持久化的数据在宿主机内显示，做数据备份