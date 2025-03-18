# pthread_t

## pthread_create
`pthread_create`函数的
1. 第一个参数是`pthread_t`类型的指针，用来返回创建的线程ID。
2. 第二个参数是`pthread_attr_t`类型的指针，用来设置线程属性，一般设置为`NULL`。
3. 第三个参数是线程运行函数的地址，即新线程从这里开始执行。
4. 第四个参数是运行函数的参数，是void*类型的

## pthread_join
`pthread_join`函数的
1. 第一个参数是`pthread_t`类型的变量，即要等待的线程ID，
2. 第二个参数是`void**`类型的指针，用来返回线程的返回值。

## pthread_exit
`pthread_exit`函数的
1. 第一个参数是`void*`类型的指针，用来返回线程的返回值。
2. 对应的`pthread_join`函数的第二个参数是`void**`类型的指针，用来返回线程的返回值。

## 案例

```C
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define THREAD_NUM 4
#define ELEMENT_NUM 25000


typedef struct Node
{
	int data;
	struct Node *next;
} Node;

typedef struct List
{
	struct Node *head;
	pthread_mutex_t mutex;
} List;

typedef struct Arg{
	List* list;
	int id;
}Arg;

List *createList()
{
	List *list = (List *)malloc(sizeof(List));
	list->head = NULL;
	pthread_mutex_init(&list->mutex, NULL);
	return list;
}

void *addNode(List *list, int data)
{
	pthread_mutex_lock(&list->mutex);
	Node *newNode = (Node *)malloc(sizeof(Node));
	if (list->head == NULL)
	{
		newNode->data = 0;
		list->head = newNode;
	}
	else
	{
		newNode->data = data;
		newNode->next = list->head;
		list->head = newNode;
	}

	pthread_mutex_unlock(&list->mutex);
}

void *removeNode(List* list)
{
	pthread_mutex_lock(&list->mutex);

	Node *cur = list->head;
	list->head = cur->next;
	free(cur);
	pthread_mutex_unlock(&list->mutex);
}

void *insert_nodes(void* arg)
{
	List* list = ((Arg*)arg)->list;
	int id = ((Arg*)arg)->id;
	free(arg);
	for(int i = 1; i <= ELEMENT_NUM; i++){
		int data = i * id;
		addNode(list, data);
	}
	pthread_exit(NULL);
}

void *remove_nodes(void* arg){
	List* list = (List*)arg;
	for(int i = 0; i < ELEMENT_NUM; i++){
		removeNode(list);
	}
	pthread_exit(NULL);
}



int main()
{
	List* list = createList();

	pthread_t threads[THREAD_NUM];

	for (int i = 0; i < THREAD_NUM; i++)
	{
		Arg* arg = (Arg*)malloc(sizeof(Arg));
		arg->list = list;
		arg->id = i + 1;
		pthread_create(&threads[i], NULL, insert_nodes, arg);
	}

	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("Finishing inserting nodes. Last id: %d\n", list->head->data);

	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_create(&threads[i], NULL, remove_nodes, list);
	}

	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_join(threads[i], NULL);
	}

	if (list->head != NULL)
		printf("ERROR!");
	else
		printf("We removed all elements added.\n");

	return 0;
}
```