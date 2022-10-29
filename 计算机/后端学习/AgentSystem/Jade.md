# Jade

## 命令行创建
Main Container
```cmd
java17 -cp jade.jar jade.Boot -host 127.0.0.1 -port 5656 -local-host 127.0.0.1 -local-port 5656 -gui
```

Federate Container
```cmd
java17 -cp jade.jar jade.Boot -host 127.0.0.1 -port 5656 -container
```

## lab1
使用以下命令启动单个容器：
```
java ­cp lib/jade.jar jade.Boot
```

jade.Boot 类是主要的 JADE 类，它包括运行单个容器的 main () 方法。 可以使用以下可选参数配置容器启动：
