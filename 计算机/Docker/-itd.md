# -itd

-i: 交互式容器 –interactive： 即使没有连接，也要保持标准输入保持打开状态，一般与 -t 连用。
-t: 分配一个伪交互式终端 –tty 分配一个伪tty，一般与 -i 连用。
-d: 守护式容器 在后台运行容器，并且打印容器id

* 什么是守护式容器：
交互式容器在命令结束后停止，当我们需要长期运行的容器来提供服务时，就需要docker的守护式容器。守护式容器 能够长期运行，没有交互式会话，非常适合运行应用程序。