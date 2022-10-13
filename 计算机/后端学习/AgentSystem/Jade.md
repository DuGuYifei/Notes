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