# 消息队列和msg相关函数

## 函数

### msgget

用来创建和访问一个消息队列，或者访问一个已经存在的消息队列。

```c
int msqid = msgget(IPC_PRIVATE, 0600 | IPC_CREAT);
```

### msgsnd

用来向消息队列发送消息。

```c
typedef struct message{
	long mtype;
	char mtext;
} message;

message msg;

msg.mtype = 1L;

msgsnd(msqid, &msg, sizeof(message), 0);
```

### msgrcv

用来从消息队列中接收消息。

```c
typedef struct message{
	long mtype;
	char mtext;
} message;

message msg;

msgrcv(msqid, &msg, sizeof(message), 1L, 0);
```

### msgctl

用来对消息队列进行一些控制操作。

#### 获取配置 和 设置长度（也可以用来限制接收多少消息）
长度只有一个消息的长度就限制了只有一个消息。

```c
struct msqid_ds queue_info;
if(msgctl(msqid, IPC_STAT, &queue_info)){
	perror("msgctl");
}

queue_info.msg_qbytes = sizeof(message);
if(msgctl(msqid, IPC_SET, &queue_info) == -1){
	perror("msgctl");
}
```

#### 销毁

```c
if (msgctl(sem->semaphore_id, IPC_RMID, NULL) == -1) // remove the message queue
    return errno;
```


## 消息队列模拟二进制信号量
[信号量_C](信号量_C.md) 中有直接使用信号量的案例，这里使用消息队列模拟信号量。

`binary_semaphore.h`
```c
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>

#define SEM_MSG_TYPE 1L

typedef struct binary_semaphore{
    int semaphore_id;
} binary_semaphore_t;


int binary_semaphore_init(binary_semaphore_t* sem, int init_state);
int binary_semaphore_wait(binary_semaphore_t* sem);
int binary_semaphore_post(binary_semaphore_t* sem);
int binary_semaphore_destroy(binary_semaphore_t* sem);
```

`binary_semaphore.c`
```c
#include "binary_semaphore.h"
#include <stdio.h>

typedef struct message{
	long mtype;
	char mtext;
} message;

// init_state 0/1
int binary_semaphore_init(binary_semaphore_t* sem, int init_state) {
    int msqid = msgget(IPC_PRIVATE, 0600 | IPC_CREAT);
    if (msqid == -1)
        return errno;
	
	// get status and set the max size of the queue to 1
    sem->semaphore_id = msqid;
	struct msqid_ds queue_info;
	if(msgctl(msqid, IPC_STAT, &queue_info)){
		perror("msgctl");
	}
	
	queue_info.msg_qbytes = sizeof(message);
	if(msgctl(msqid, IPC_SET, &queue_info) == -1){
		perror("msgctl");
	}

	if(init_state == 1){
		if(binary_semaphore_post(sem) == -1){
			printf("binary_semaphore_post\n");
		}
	}

    return 0;
}

int binary_semaphore_wait(binary_semaphore_t* sem) {
    message msg;

	// // check length of the queue
	// struct msqid_ds queue_info;
	// if(msgctl(sem->semaphore_id, IPC_STAT, &queue_info)){
	// 	perror("msgctl");
	// }
	// printf("queue_info.msg_qnum: %ld\n", queue_info.msg_qnum);

	// read, if no message, block!!!!!!!!
    // fd, buf, len, type, flag
    if (msgrcv(sem->semaphore_id, &msg, sizeof(message), SEM_MSG_TYPE, 0) == -1){
		printf("errno: %d have had msg\n", errno);
        return errno;
	}

    return 0;
}

int binary_semaphore_post(binary_semaphore_t* sem) {
    message msg;
	msg.mtext = 'v';
	msg.mtype = SEM_MSG_TYPE;

    // fd, buf, len, flag
    if (msgsnd(sem->semaphore_id, &msg, sizeof(message), IPC_NOWAIT) == -1){
		if (errno == EAGAIN) {
            //printf("Message queue is full.\n");
        } else {
            perror("msgsnd");
        }
	}

    return 0;
}

int binary_semaphore_destroy(binary_semaphore_t* sem) {
    if (msgctl(sem->semaphore_id, IPC_RMID, NULL) == -1) // remove the message queue
        return errno;

    return 0;
}
```