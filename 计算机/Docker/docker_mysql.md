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