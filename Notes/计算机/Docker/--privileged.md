# --privileged

有的时候我们需要容器具备更多的权限，比如操作内核模块，控制 swap 交换分区，挂载 USB 磁盘，修改 MAC 地址等。

`--privileged=true`

同时也能解决`Permission denied`