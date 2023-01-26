# Dockerfile

## 案例
example:
```docker
FROM openjdk:17-jdk-slim

COPY backend-element/target/lab3-0.0.1-SNAPSHOT.jar /app/element.jar
COPY backend-category/target/lab3-0.0.1-SNAPSHOT.jar /app/category.jar
COPY gateway/target/lab3-0.0.1-SNAPSHOT.jar /app/gateway.jar

WORKDIR /app

COPY run.sh /app/run.sh
RUN chmod +x /app/run.sh
EXPOSE 8081 80
RUN apt update && apt install -y nginx
COPY frontend/dist /var/www/html

CMD "/app/run.sh"
```

```CMD
docker build . -t myImage
docker container run -v /:/home/myDirectory/myImage
```

## EXPOSE
[EXPOSE](EXPOSE.md)