# RowKey设计
## 教程链接一

[用大白话彻底搞懂 HBase RowKey 详细设计](https://blog.csdn.net/FL63Zv9Zou86950w/article/details/106066082)

### 问题

热点现象：

我们知道HBase中的行是按照rowkey的字典顺序排序的，这种设计优化了 scan操作，可以将相关的行以及会被一起读取的行存取在临近位置，便于 scan读取。

然而万事万物都有两面性，在咱们实际生产中，当大量请求访问HBase集群的一个或少数几个节点，造成少数RegionServer的读写请求过多，负载过大，而其他RegionServer负载却很小，这样就造成热点现象（吐槽：其实和数据倾斜类似，还整这么高大上的名字）。

掌握了热点现象的概念，我们就应该知道大量的访问会使热点Region所在的主机负载过大，引起性能下降，甚至导致Region不可用。所以我们在向HBase中插入数据的时候，应优化RowKey的设计，使数据被写入集群的多个region，而不是一个。尽量均衡地把记录分散到不同的Region中去，平衡每个Region的压力。  
 

#### 方法

1. **反转（Reversing）**
2. **加盐（Salting）**
3. **哈希（Hashing）**

#### 原则

1. **长度原则**
2. **唯一原则**
3. **排序原则**
4. **散列原则**

## 教程链接哔哩哔哩两个系列

1. [HBase实际应用案例](https://www.bilibili.com/video/BV1yb411X7hE)
2. [40分钟搞定HBase的设计使用](https://www.bilibili.com/video/BV1iP4y1t7CM?p=1)