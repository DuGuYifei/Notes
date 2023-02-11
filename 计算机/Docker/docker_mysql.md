# docker mysql

init database
```sql
CREATE DATABASE IF NOT EXISTS `animal`;
CREATE DATABASE IF NOT EXISTS `pet`;

CREATE USER 'root'@'localhost' IDENTIFIED BY 'root';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%';
```

docker_compose
[docker_compose](docker_compose.md)

```cmd
docker run -d -p 3306:3306 --name mysql -e MYSQL_ROOT_PASSWORD=root -e MYSQL_PASSWORD=123456 -v /E/DockerFolder/mysql/mysql:/var/lib/mysql mysql:latest
```

最后必须有一个环境变量`-e`，三个里至少一个不然会报错，**而且必须放在image之前**：
- MYSQL_ROOT_PASSWORD
- MYSQL_ALLOW_EMPTY_PASSWORD
- MYSQL_RANDOM_ROOT_PASSWORD