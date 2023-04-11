# mvn

## 创建项目

```bash
mvn archetype:generate -DgroupId=com.example -DartifactId=example -DarchetypeArtifactId=maven-archetype-quickstart -DinteractiveMode=false
```

## 编译

```bash
mvn compile
```

## 打包

```bash
mvn package
mvn clean package -Dmaven.test.skip=true
```

## 安装

```bash
mvn install
```

## package和install的区别
mvn package 命令用于将项目打包成可分发的格式（例如 JAR、WAR 或 EAR 文件），并将其复制到项目目录下的 target 文件夹中。打包的过程包括编译代码、运行测试、生成文档等步骤，但不包括将项目安装到本地 Maven 仓库中。

mvn install 命令的作用是将项目安装到本地 Maven 仓库中，以供其他项目引用。它会执行 mvn package 命令并将打包后的文件复制到本地仓库中，以及将项目所依赖的库文件也复制到本地仓库中。

换句话说，**mvn package 可以理解为是一个“局部的”构建过程，仅将项目打包成可分发的格式，并存放在 target 文件夹中；而 mvn install 是一个“全局的”构建过程，它不仅包括了打包的过程，还将打包后的文件和依赖库安装到本地 Maven 仓库中，以便其他项目引用**。


## 发布

```bash
mvn deploy
```

## 清理

clean命令用于清理项目，删除target目录。

```bash
mvn clean
```

## 运行

```bash
mvn exec:java -Dexec.mainClass="com.example.App"
```

## 测试

```bash
mvn test
```

## 依赖

### 查看依赖

```bash
mvn dependency:tree
```

### 添加依赖

```bash
mvn dependency:copy-dependencies
```

### 依赖冲突

```bash
mvn dependency:analyze
```

### 刷新依赖

```bash
mvn dependency:purge-local-repository
```

## 其他
1. [test和选择-跳过](test和选择-跳过.md)