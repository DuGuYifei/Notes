# Spark简介

## Motivation behind Apache Spark

### MapReduce 缺点
- MapReduce relies on a rigid map-then-reduce format
- Using MapReduce for complex jobs involves a lot of disk I/O
- MapReduce is suitable only for batch processing jobs (中文：MapReduce只适合批处理作业)
	- it does not provide an interactive shell

### MapReduce and Spark Differences

|                  | Apache Hadoop Map Reduce | Apache Spark                                              |
| ---------------- | ------------------------ | --------------------------------------------------------- |
| Storage          | Disk only                | In-memory or on disk                                      |
| Operations       | Map and Reduce           | Many transformation and actions, including Map and Reduce |
| Execution model  | Batch                    | Batch, interactive, streaming                             |
| Language support | Java                     | Java, Python, Scala, R                                    |

## Spark Components
- Spark Core
  - contains the basic functionality of Spark, including components for task scheduling, memory management, fault recovery, interacting with storage systems
  - provides many APIs for building and manimupalting RDDs
- Spark SQL
  - is Spark's package for working with structured data
  - allows querying data via SQL and HQL
  - supports many sources of data, including Hive tables, Parquet, and JSON
- Spark Streaming
  - enables processing of live streams of data
- MLlib (Machine Learning Library)
  - provides multiple types of machine learning algorithms (including classification, regression, clustering)
- GraphX
  - is a library for manipulating graphs (e.g., a social network's graph of friends and followers)

## Data interfaces
- Resilient Distributed Dataset ([RDD](./RDD.md))
  - a collection of elements partitioned across the nodes of the cluster that can be operated in parallel
- DataFrames
  - is conceptually equivalent to a table in a relational database (翻译：概念上等同于关系数据库中的表)
- Dataset
  - provides the typed interface for working with semi-structured and structured data (翻译：提供半结构化和结构化数据的类型化接口)
  - is available only to Java and Scala

## The architecture of a Spark application
- Spark Driver
  - creates a `SparkSession` object, which represents a connection to a cluster
  - launches various parallel tasks on executor JVMs (翻译：在执行器JVM上启动各种并行任务)
- Spark Executors
  - perform tasks assigned by the driver
  - report back their state and results to the Driver


