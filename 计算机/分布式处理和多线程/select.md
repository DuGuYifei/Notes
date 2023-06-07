# select

## 介绍
```c
#include <sys/select.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

// 返回值：成功返回就绪的文件描述符数目，失败返回-1
// nfds：监控的文件描述符的最大值+1
// readfds：监控读事件的文件描述符集合
// writefds：监控写事件的文件描述符集合
// exceptfds：监控异常事件的文件描述符集合
// timeout：超时时间，NULL表示永久阻塞，0表示非阻塞，其他表示阻塞时间
```
## 使用(GPT生成)
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_SOCKETS 2

int main() {
    int sockets[MAX_SOCKETS];  // 存储socket描述符的数组
    fd_set readfds;  // 可读事件的文件描述符集合
    int max_fd;  // 最大的文件描述符
    int i;

    // 创建两个socket对象
    sockets[0] = socket(AF_INET, SOCK_STREAM, 0);
    sockets[1] = socket(AF_INET, SOCK_STREAM, 0);

    // 绑定socket到本地地址和端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(8001);
    bind(sockets[0], (struct sockaddr*)&addr, sizeof(addr));

    addr.sin_port = htons(8002);
    bind(sockets[1], (struct sockaddr*)&addr, sizeof(addr));

    // 监听连接
    listen(sockets[0], 1);
    listen(sockets[1], 1);

    // 初始化文件描述符集合
    FD_ZERO(&readfds);
    max_fd = -1;
    for (i = 0; i < MAX_SOCKETS; i++) {
        FD_SET(sockets[i], &readfds);
        if (sockets[i] > max_fd) {
            max_fd = sockets[i];
        }
    }

    while (1) {
        // 使用select函数阻塞等待事件发生
        fd_set tmp_fds = readfds;
        int num_ready = select(max_fd + 1, &tmp_fds, NULL, NULL, NULL);
        if (num_ready < 0) {
            perror("select");
            exit(1);
        }

        // 处理可读事件
        for (i = 0; i < MAX_SOCKETS; i++) {
            if (FD_ISSET(sockets[i], &tmp_fds)) {
                // 处理该socket上的消息
                int client_socket = accept(sockets[i], NULL, NULL);
                char buffer[1024];
                ssize_t num_bytes = recv(client_socket, buffer, sizeof(buffer), 0);
                if (num_bytes > 0) {
                    printf("Received data from socket %d: %s\n", i, buffer);
                }
                close(client_socket);
            }
        }
    }

    return 0;
}
```