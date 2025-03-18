# http

[http](../../%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%BD%91%E7%BB%9C/%E5%9F%9F%E5%90%8D%E5%92%8C%E7%BD%91%E5%9D%80%E4%BB%A5%E5%8F%8A%E8%B6%85%E6%96%87%E6%9C%AC%E4%BC%A0%E8%BE%93%E5%8D%8F%E8%AE%AE%E7%9A%84%E5%AE%9E%E9%99%85%E4%BD%BF%E7%94%A8/%E8%B6%85%E6%96%87%E6%9C%AC%E4%BC%A0%E8%BE%93%E5%8D%8F%E8%AE%AE.md)

* http 基本需要的是**第一行**，和**头和body之间的空行**
  * 如果没有空行就会在postman里显示错误，http协议的错误导致没有完成解析
* 换行是`\r\n`
* 返回完不关闭链接，就会一直保持链接，直到超时
  * postman可以很直观看到不关闭时，一直有绿色的加载线

```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "http_listen.h"
#include "register_room.h"
#include "param.h"

int distinguish_http_request(char *buffer, int client_fd)
{
	char *token;
	char *key;
	char *value, *psd_value;
	int idx = 0;

	// split the http request to handle it
	while ((token = strtok(buffer + idx, "\r")) != NULL)
	{
		idx += strlen(token) + 2;

		// skip the empty line before http body
		if (buffer[idx] == '\r')
		{
			idx += 2;
		}

		key = strtok(token, ":");
		if (key == NULL)
		{
			continue;
		}
		value = strtok(NULL, "\0");
		// if user or room
		if (strcmp(key, "user") == 0)
		{
			// printf("%s:%s\n", key, value);

			// handle user register to database in the future
			// TODO
			return 1;
		}
		else if (strcmp(key, "room") == 0)
		{
			// printf("%s:%s\n", key, value);

			// next line is the room password
			token = strtok(buffer + idx, "\r");
			idx += strlen(token) + 2;
			psd_value = strtok(token, ":");
			psd_value = strtok(NULL, "\0");
			// printf("psd:%s\n", psd_value);

			// handle room register
			int token = register_room(value, psd_value);
			return token > 0 ? token : -1;
		}
	}
	return 0;
}

void *listen_register()
{
	// create server socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// bind
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT_HTTP);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)))
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// listen
	if (listen(server_fd, 10) < 0)
	{
		perror("listen failed");
		exit(EXIT_FAILURE);
	}

	// accept
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	char buffer[MAX_BUFFER_SIZE] = {0};
	char token_str[30] = {0};
	int token = 0;
	while (client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len))
	{
		if (client_fd < 0)
		{
			perror("accept failed");
		}

		// read
		if (read(client_fd, buffer, MAX_BUFFER_SIZE) < 0)
		{
			if (write(client_fd, "HTTP/1.1 502 ERROR\r\n\r\n", 22) < 0)
			{
				perror("write failed");
			}
			perror("read failed");
			continue;
		}

		token = distinguish_http_request(buffer, client_fd);
		if (token > 0)
		{
			// add token after HTTP/1.1 200 OK\r\n\r\n
			sprintf(token_str, "HTTP/1.1 200 OK\r\n\r\n%d", token);
			if (write(client_fd, token_str, strlen(token_str)) < 0)
			{
				perror("write failed");
			}
			memset(token_str, 0, 30);
		}
		else if (token == -1)
		{
			if (write(client_fd, "HTTP/1.1 403 ERROR\r\n\r\nRoom exists and Wrong Password", 52) < 0)
			{
				perror("write failed");
			}
			printf("Room exists and Wrong Password\n");
		}
		else
		{
			if (write(client_fd, "HTTP/1.1 502 ERROR\r\n\r\n", 22) < 0)
			{
				perror("write failed");
			}
			printf("502 ERROR\n");
		}
		close(client_fd);
		memset(buffer, 0, MAX_BUFFER_SIZE);
	}

	close(server_fd);
}
```
