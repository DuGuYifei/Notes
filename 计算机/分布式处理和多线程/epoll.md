# epoll

```c
void *handle_client(void *c_fd)
{
	int client_fd = *(int *)c_fd;
	int pipe_fd[2] = {0};

	if (pipe(pipe_fd) < 0)
	{
		printf("pipe error\n");
		close(client_fd);
		pthread_exit(NULL);
	}

	message *msg = (message *)malloc(sizeof(message));

	if (read(client_fd, msg, MAX_BUFFER_SIZE) < 0)
	{
		printf("read error\n");
		close(client_fd);
		pthread_exit(NULL);
	}

	// find the room from database
	pthread_mutex_lock(&room_list_mutex);
	room *room = find_room_token(msg->token);

	// first time need register client_fd to room
	room->client_list = client_list_add(room->client_list, client_fd, pipe_fd);

	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
		// handle error
		pthread_mutex_unlock(&room_list_mutex);
		perror("epoll_create1 error");
		return NULL;
	}

	struct epoll_event events[MAX_BUFFER_SIZE];
	struct epoll_event event1;
	event1.events = EPOLLIN; // focus on read event
    event1.data.fd = client_fd;
	struct epoll_event event2;
	event2.events = EPOLLIN; // focus on read event
    event2.data.fd = pipe_fd[0];
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event1);
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, pipe_fd[0], &event2);

	send_to_all(room, msg);
	pthread_mutex_unlock(&room_list_mutex);

	int pass = 1;

	while (pass)
	{
		// epoll
		int num_events = epoll_wait(epoll_fd, events, MAX_BUFFER_SIZE, -1);
		if (num_events == -1)
		{
			// have sth wrong
			continue;
		}
		// handle event
		for (int i = 0; i < num_events; i++)
		{
			int fd = events[i].data.fd;
			if (fd == client_fd)
			{
				// read
				if (read(client_fd, msg, MAX_BUFFER_SIZE) < 0)
				{
					pass = 0;
					break;
				}

				printf("%s\n", msg->message);

				if (strcmp(msg->message, "!q") == 0)
				{
					pass = 0;
					break;
				}

				// send to all clients in this room
				pthread_mutex_lock(&room_list_mutex);
				send_to_all(room, msg);
				pthread_mutex_unlock(&room_list_mutex);
			}
			else
			{
				// write to client_fd
				if (read(fd, msg, MAX_BUFFER_SIZE) < 0)
				{
					pass = 0;
					break;
				}
				if (write(client_fd, msg, MAX_BUFFER_SIZE) < 0)
				{
					pass = 0;
					break;
				}
			}
		}
		memset(&events, 0, MAX_BUFFER_SIZE * sizeof(struct epoll_event));
	}
	client_list_remove(room->client_list, client_fd);
	close(client_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	free(msg);
	pthread_exit(NULL);
}
```