# close()和shutdown()

# close()

close(fd)函数用于关闭套接字句柄，当套接字不再使用时，应该关闭套接字，否则会造成资源浪费。

**fd可以是远程对方的句柄。**

# shutdown()
```c
int shutdown(int sock, int howto); //Linux
int shutdown(SOCKET s, int howto); //Windows
```

* 可以选择关闭 howto 
  * Linux
  	* SHUT_RD：断开输入流。套接字无法接收数据（即使输入缓冲区收到数据也被抹去），无法调用输入相关函数。
  	* SHUT_WR：断开输出流。套接字无法发送数据，但如果输出缓冲区中还有未传输的数据，则将传递到目标主机。
  	* SHUT_RDWR：同时断开 I/O 流。相当于分两次调用 shutdown()，其中一次以 SHUT_RD 为参数，另一次以 SHUT_WR 为参数。
  * Windows
    * SD_RECEIVE：关闭接收操作，也就是断开输入流。
    * SD_SEND：关闭发送操作，也就是断开输出流。
    * SD_BOTH：同时关闭接收和发送操作。
* 而且会先发送完数据再关闭