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
1. `/etc/nginx/conf.d`
2. 使用