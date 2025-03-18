# deque以及和queue对比

Deque是双端队列，可以从队头队尾入队出队。 
Queue是单向队列 只能从对尾入队，队头出队。(FIFO)

## queue
[queue](queue.md)


## deque

deque**双端队列的操作**(可以在队头队尾进行入队出队操作)

`deque<int> dq` 创建一个数双端队列dq

`dq.empty()` 判断队列是否为空，为空返回true

`dq.push_front(s)` 将s从队头入队

`dq.push_back(s)` 将s从队尾入队，和普通队列方式一样

`dq.front()` 只返回队头元素

`dq.back()` 只返回队尾元素

`dq.pop_front()` 将队头元素弹出

`dq.pop_back()` 将队尾元素弹出

`dq.clear()` 将队列清空

deque可以访问两端并且可以在队首和队尾删除和插入元素

取数的话，queue和deque都可以从两端取，所以都是front()和back();