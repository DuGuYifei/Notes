# cp宿主机和容器之间复制文件
```sh
# 从宿主机复制到容器
docker cp [OPTIONS] <宿主机路径> <容器ID>:<容器路径>
docker cp /home/user/document.txt my_container:/tmp/

# 从容器复制到宿主机
docker cp [OPTIONS] <容器ID>:<容器路径> <宿主机路径>
docker cp my_container:/tmp/document.txt /home/user/
```