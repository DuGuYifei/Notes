# accept队列

在 TCP 协议中，服务器端使用 listen 函数来等待客户端的连接请求。在 listen 函数的实现中，服务器端会创建一个被称为 accept 队列（Accept Queue）的数据结构，用于存储已经到达服务器端但尚未被 accept 函数处理的连接请求。

当客户端向服务器端发起连接请求时，请求会被存储在 accept 队列中，直到服务器端调用 accept 函数来处理该请求。在 accept 函数被调用之前，连接请求已经进入了 accept 队列，等待被处理。