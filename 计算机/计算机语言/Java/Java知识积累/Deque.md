# Deque

```Java
Deque<int[]> q = new ArrayDeque<int[]>();
q.empty();
q.peekLast();
q.peekFirst();
q.poll(); // 返回并删除第一个元素
q.pollFirst(); // 返回并删除第一个元素，列表空返回null
q.pollLast();// 返回并删除最后一个元素，列表空返回null
q.add(); //addLast
q.addFirst();
q.addLast();
```