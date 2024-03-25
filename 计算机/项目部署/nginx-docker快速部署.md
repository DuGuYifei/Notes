# nginx-docker快速部署
```yml
version: '3'  
services:  
  nginx:  
    image: nginx:latest  
    ports:  
      - "80:80"  
    volumes:  
      - ./dist:/usr/share/nginx/html:ro  
  
volumes:  
  mysql-data:
```

想要修改配置文件：
1. `/etc/nginx/conf.d/default.conf`：修改默认配置文件
2. 使用命令：`docker exec -it nginx /bin/bash`进入容器，修改配置文件
3. 重启容器：`docker restart nginx`
4. 也可以使用`docker cp`命令将配置文件拷贝到容器中
```
docker cp default.conf nginx:/etc/nginx/conf.d/default.conf
```