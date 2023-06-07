# RDD

RDD(Resilient Distributed Datasets),弹性分布式数据集,是分布式内存的一个抽象概念，RDD提供了一种高度受限的共享内存模型，即RDD是只读的记录分区的集合，**只能通过在其他RDD执行确定的转换操作（如map、join和group by）而创建（悟：想象string）**，然而这些限制使得实现容错的开销很低。

对开发者而言，RDD可以看作是Spark的一个对象，它本身运行于内存中，如读文件是一个RDD，对文件计算是一个RDD，结果集也是一个RDD ，不同的分片、 数据之间的依赖 、key-value类型的map数据都可以看做RDD。