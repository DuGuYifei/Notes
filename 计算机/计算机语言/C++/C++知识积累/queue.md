# queue

FIFO

`queue.push()` 从队尾

`queue.pop()` 从队头

`queue.empty()`

`queue.size()`

`q.front()` 返回队头元素

`q.back()` 返回队尾元素

`q.size()` 返回队列中元素个数

queue只能从队首删除元素,但是两端都能访问。

循环时注意pop了之后会改变size，所以要在循环之前先将size赋值给一个变量