# perror

perror的作用是打印出上一个函数发生错误的原因，它可以根据之前某个函数发生的错误进行打印。

```c
if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_fd))){
	perror("bind failed");
}

// 可能会输出：
// bind failed: Address already in use
// bind failed: Invalid argument
// ...
```