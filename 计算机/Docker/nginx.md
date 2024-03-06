# nginx
## nginx挂载本地硬盘

我的版本：
```cmd
docker run -p 4030:80 --name mynginx --privileged=true ^
-v /E/"Gdansk University of Technology"/fifth_semester/InternetiServicesArchitectures/Lab/Lab5/M1/html:/usr/share/nginx/html ^
-v /E/"Gdansk University of Technology"/fifth_semester/InternetiServicesArchitectures/Lab/Lab5/M1/nginx/nginx.conf:/etc/nginx/nginx.conf ^
-v /E/"Gdansk University of Technology"/fifth_semester/InternetiServicesArchitectures/Lab/Lab5/M1/nginx/conf.d/default.conf:/etc/nginx/conf.d/default.conf ^
-v /E/"Gdansk University of Technology"/fifth_semester/InternetiServicesArchitectures/Lab/Lab5/M1/lognginx:/var/log/nginx ^
-d nginx
```

教程：
```bash
docker run -p 80:80 --name mynginx --privileged=true \
-v /home/mynginx/html:/usr/share/nginx/html \
-v /home/mynginx/conf/nginx.conf:/etc/nginx/nginx.conf \
-v /home/mynginx/conf.d/default.conf:/etc/nginx/conf.d/default.conf \
-v /home/mynginx/logs:/var/log/nginx \
-d nginx
```

## 防止容器挂掉
```sh
nginx -g "daemon off;"
```

docker 容器启动时，默认会把容器内部第一个进程，也就是pid=1的程序，作为docker容器是否正在运行的依据，如果 docker 容器pid=1的进程挂了，那么docker容器便会直接退出。

docker未执行自定义的cmd之前，nginx的pid是1，执行到cmd之后，nginx就在后台运行，bash或sh脚本的pid变成了1。

所以一旦执行完自定义cmd，nginx容器也就退出了。