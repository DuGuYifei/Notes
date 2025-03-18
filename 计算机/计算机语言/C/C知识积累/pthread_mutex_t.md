# pthread_mutex_t

互斥锁

```C
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //但是这种初始化方式只能在定义的时候使用，不能在函数中使用

pthread_mutex_init(&mutex, NULL); //初始化互斥锁

pthread_mutex_lock(&mutex); //加锁

pthread_mutex_unlock(&mutex); //解锁
```