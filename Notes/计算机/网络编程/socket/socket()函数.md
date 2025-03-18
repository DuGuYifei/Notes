# socket()函数

创建套接字

## linux
```c
int socket(int af, int type, int protocol);
```

1. af 为地址族（Address Family），也就是 IP 地址类型，常用的有 AF_INET 和 AF_INET6。
   1. AF 是“Address Family”的简写，INET是“Inetnet”的简写。
      1. AF_INET 表示 IPv4 地址，例如 127.0.0.1；
      2. AF_INET6 表示 IPv6 地址，例如 1030::C9B4:FF12:48AA:1A2B。
   2. 你也可以使用 PF 前缀，PF 是“Protocol Family”的简写，它和 AF 是一样的。例如，PF_INET 等价于 AF_INET，PF_INET6 等价于 AF_INET6。
2. type 为数据传输方式/套接字类型，常用的有 [SOCK_STREAM（流格式套接字/面向连接的套接字） 和 SOCK_DGRAM（数据报套接字/无连接的套接字）](./SOCK_STREAM和SOCK_DGRAM.md)。
3. protocol 表示传输协议，常用的有 `IPPROTO_TCP` 和 `IPPTOTO_UDP，分别表示` TCP 传输协议和 UDP 传输协议。

有了地址类型和数据传输方式，还不足以决定采用哪种协议吗？为什么还需要第三个参数呢？

正如大家所想，**一般情况下有了 af 和 type 两个参数就可以创建套接字了，操作系统会自动推演出协议类型**，除非遇到这样的情况：有两种不同的协议支持同一种地址类型和数据传输类型。如果我们不指明使用哪种协议，操作系统是没办法自动推演的。

```c
int tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  //IPPROTO_TCP表示TCP协议
int udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  //IPPROTO_UDP表示UDP协议

// 上面两种情况都只有一种协议满足条件，可以将 protocol 的值设为 0，系统会自动推演出应该使用什么协议，如下所示：
int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);  //创建TCP套接字
int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);  //创建UDP套接字
```

## windows
```c
SOCKET socket(int af, int type, int protocol);
```

除了返回值类型不同，其他都是相同的。**Windows 不把套接字作为普通文件对待，而是返回 SOCKET 类型的句柄**。请看下面的例子：

```c
SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);  //创建TCP套接字
```