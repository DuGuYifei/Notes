# AQS

## 简介

AQS 是 AbstractQueuedSynchronizer 的简称，是一个用来构建锁和同步器的框架，使用一个 int 成员变量表示同步状态，通过内置的 FIFO 队列来完成资源获取线程的排队工作。

悟：就像是一个用semaphore实现的monitor。

![](2023-06-17-18-22-49.png)