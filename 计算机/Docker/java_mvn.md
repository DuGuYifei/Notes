# java_mvn

## maven版本直接
```bash
docker run -it --name maven_jdk8 maven:3.3.9-jdk-8
```

## 命令
```java
docker run -it --name jdk11 -v E:/DockerFolder/java/jdk11/myapp:/myapp openjdk:11-jdk
```

```bash
apt update && apt install -y maven
```

## dockerfile
```dockerfile
FROM openjdk:11-jdk
RUN apt-get update && apt-get install -y maven
```

```bash
docker build . -t myImage
docker run -it --name jdk11_mvn -v E/DockerFolder/java/jdk11/myapp:/myapp jdk11_mvn
```
