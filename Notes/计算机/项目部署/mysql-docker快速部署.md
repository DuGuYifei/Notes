# mysql-docker快速部署

```yml
version: '3'  
services:  
  mysql:  
    image: mysql:8.0  
    container_name: mysql  
    ports:  
      - "3306:3306"  
    environment:  
      MYSQL_ROOT_PASSWORD: 'password'  
      MYSQL_ROOT_HOST: '%'  
    volumes:  
      - '/etc/localtime:/etc/localtime:ro'  
      - './opt/app/mysql/data:/var/lib/mysql'  
      - './opt/app/mysql/conf:/etc/mysql/conf.d'  
      - './opt/app/mysql/logs:/logs'  
      - './opt/app/mysql/init.sql:/data/application/init.sql'  
    command:  
      --default-time-zone='+8:00'  
      --default-authentication-plugin=mysql_native_password  
      --character-set-server=utf8mb4  
      --lower_case_table_names=1  
      --collation-server=utf8mb4_general_ci   
      --init-file /data/application/init.sql  
  
volumes:  
  mysql-data:
```

```sh
# 或者直接创建好这些文件夹 一次性上传上去比较好
mkdir ./opt/app/mysql
cp ./init.sql ./opt/app/mysql/
```

```sql
CREATE DATABASE IF NOT EXISTS exam;
```