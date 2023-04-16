# WSAStartup()WSACleanup()

在Windows平台下，使用Socket编程进行网络通信之前，必须先调用WSAStartup()函数来初始化Winsock库。Winsock库是Windows Socket API的实现，用于支持网络通信。

WSAStartup()函数的主要作用是加载Winsock库，并告诉操作系统所需的Winsock库的版本号。函数原型如下：

```c
int WSAStartup(
  WORD      wVersionRequested,
  LPWSADATA lpWSAData
);
```

其中，参数wVersionRequested指定所需的Winsock库的版本号，一般使用宏定义MAKEWORD(2,2)表示需要使用2.2版本的Winsock库。参数lpWSAData是一个指向WSADATA结构体的指针，用于接收Winsock库的初始化信息。

WSAStartup()函数返回0表示成功，其他值表示失败。如果函数执行成功，就可以使用Socket编程进行网络通信了。而在结束网络通信后，需要调用`WSACleanup()`函数来释放Winsock库所占用的资源。

