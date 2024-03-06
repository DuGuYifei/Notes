# connect

## 函数

```c
int connect(int sock, struct sockaddr *serv_addr, socklen_t addrlen);  //Linux
int connect(SOCKET sock, const struct sockaddr *serv_addr, int addrlen);  //Windows
```

各个参数的说明和 bind() 相同。 [bind()](bind().md)