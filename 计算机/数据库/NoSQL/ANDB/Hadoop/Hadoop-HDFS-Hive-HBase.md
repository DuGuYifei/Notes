# Hadoop-HDFS-Hive-HBase

Hadoop：是一个分布式计算的开源框架。分布式文件系统(HDFS) + 分布式计算框架(Mapreduce) + 调度系统Yarn搭建起来的分布式大数据处理框架。

HDFS：是Hadoop的三大核心组件之一

Hive：用户处理存储在HDFS中的数据，hive的意义就是把好写的hive的sql转换为复杂难写的map-reduce程序。

Hbase：是一款基于HDFS的数据库，是一种NoSQL数据库，主要适用于海量明细数据（十亿、百亿）的随机实时查询，如日志明细、交易清单、轨迹行为等。

[Hive](../Hive/Hive.md)


Hadoop 可以做数据仓库，但不是OLAP，但是Apache推出了Kylin可以使它做OLAP，HDFS是一个帮助Hadoop做数据仓库的工具，可以ELT，还可以从Mysql中ELT。