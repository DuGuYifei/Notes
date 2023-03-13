# C语言基础操作



1. int sem_init(sem_t *sem,int pshared,unsigned int value);
   1. pshared控制信号量的类型，如果其值为0，就表示这个信号量是当前进程的局部信号量，否则信号量就可以在多个进程之间共享，
   2. value为sem的初始值。
   3. 调用成功时返回0，失败返回-1.
2. int sem_wait(sem_t *sem);  
   1. 原子操作就是，如果两个线程企图同时给一个信号量加1或减1，它们之间不会互相干扰。
   2. 该函数用于以原子操作的方式将信号量的值减1。
   3. 等待信号量，如果信号量的值大于0,将信号量的值减1,立即返回。如果信号量的值为0,则线程阻塞。相当于P操作。
   4. 成功返回0,失败返回-1。
3. int sem_post(sem_t *sem);  
   1. 该函数用于以原子操作的方式将信号量的值加1。
   2. 释放信号量，相当于V操作。
4. int sem_destroy(sem_t *sem); 
   1. 成功时返回0，失败时返回-1.

```C
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

int global_countrt =0;
sem_t sem;

#define counter 400000

void* thread_f(void *vp)
{
    int i = conter;
    
    While( i--){
        //entry protocal
        sem_wait(&sem);
        global_countrt++;   //critical section
        //exit protocal
        sem_post(&sem);
    }
} 

int main(){
    printf(%d,globl);
    //cout<<global;
    pthread_t t1,t2,t3,t4;

    if (sem_init(&sem,0,1) != 0){
        prttor("sem_inint failed! \n");
        return 1;        
    }
    

    Pthread_create(&t1,null,inc,null);
    Pthread_create(&t2,null,inc,null);
    Pthread_create(&t3,null,inc,null);
    Pthread_create(&t4,null,inc,null);

    Pthread_join(t1,null);
    Pthread_join(t2,null);
    Pthread_join(t3,null);
    Pthread_join(t4,null);

    printf(%d,globl);
    //Cout< global;

}
```