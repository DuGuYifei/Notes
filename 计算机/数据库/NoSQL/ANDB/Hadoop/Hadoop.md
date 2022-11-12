# Hadoop

## 简介
建立在 Google 的 [BigTable](../BigTable/BigTable.md) 的基础上，即文件系统的组织及其分布式处理。 它最初的用途是 Nutch 网络搜索引擎的存储子系统。

Doug Cutting 是第一个在系统上工作的人，他也是“Hadoop”这个名字的作者。

### Assumtions
• From the very beginning, the two main parts of Hadoop are  the distributed file system (HDFS) and the system of  distributed processing MapReduce.
• Hadoop is intented for files that hold large amounts of data  (Big Data), 
• Hadoop focuses on lowering the amount of data that need to  be sent during distributed processing. Its aim is to process  the data „near the data”, 
• A very important aspect of Hadoop is to offer *horizontal  scalability* while being reliable and resistant to faults of single  nodes – it is achieved by redundancy in storing and  processing data.

• 从一开始，Hadoop 的两个主要部分就是分布式文件系统（HDFS）和分布式处理系统 MapReduce。
• Hadoop 旨在用于保存大量数据（大数据）的文件， 
• Hadoop 专注于降低分布式处理期间需要发送的数据量。 其目的是处理“靠近数据”的数据。 
• Hadoop 的一个非常重要的方面是提供水平可扩展性，同时可靠并能抵抗单个节点的故障——它是通过存储和处理数据的冗余来实现的。

疑问：[hdfs集群中的每个datanode中的数据是否是相同的？ - 知乎](https://www.zhihu.com/question/40590258/answer/90302673)

hdfs是否类似mysql的复制，将一个节点的实例复制到其他节点，之后每次读取数据都会从合适的节点取出合适的数据，再组合成数据结果？
还是将数据打散后均匀分布到集群中的每一个节点上，每个节点上的数据都不同，但是每次读取数据都会从namenode的类似普通文件系统的inode的结构中找到数据存放的指针（类似的东西）？

答：有复制行为 复制单元为具体每个文件，不是整个节点作为一个实例读取确实会考虑data locality根据文件大小是否大于block size决定是否将文件数据打散打散后并没有一定均匀分布说法，Loadbalance可以人为触发每个节点上的数据确实可能会不同，视datanode数量和replica指定数量而定

## HDFS
• HDFS (Hadoop Distributed File System) is the file system  offered and handled by Hadoop, 
• The capabilities of HDFS are slightly reduced in comparison to  standard file systems, 
• HDFS is indended to hold very large files (giga- and terabytes  and larger), 
• HDFS is integrated with MapReduce, 
• HDFS is horizontally scalable – one can scale up the system  by adding nodes to it, 
• HDFS is prepared (by redundancies) for failures or sudden  performance decreases of single nodes.

• HDFS（Hadoop 分布式文件系统）是 Hadoop 提供和处理的文件系统， 
• 与标准文件系统相比，HDFS 的功能略有降低， 
• HDFS 旨在保存非常大的文件（giga- and terabytes以及更大）  , 
• HDFS 与 MapReduce 集成， 
• HDFS 是水平可扩展的——可以通过向系统添加节点来扩展系统， 
• HDFS （通过冗余）为单个节点的故障或突然性能下降做好准备。

### HDFS organization
