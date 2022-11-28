# Nonrelational Database
• Multi-Model,
• Easily scalable, 
• Easily distributed, 
• Flexibility, 
• ACID is not a rule.

• 多模型,
• 易于扩展， 
• 易于分布， 
• 灵活性， 
• ACID 不是规则。

[Graph database - neo4j](GraphDatabase_neo4j.md)
[Key Value database - Redis](KeyValueDatabase_Redis.md)
[Document database](DocumentDatabase.md)

----------------------------------------------------------------------------------------------------

1. [CAP 理论](#cap-理论)
   1. [Consistency 在 CAP 和 ACID 理论里不同](#consistency-在-cap-和-acid-理论里不同)
   2. [CA, CP/AP](#ca-cpap)
2. [BASE](#base)
3. [distributed database 分布式数据库](#distributed-database-分布式数据库)
   1. [Replication and sharding 复制和分片](#replication-and-sharding-复制和分片)
      1. [Peer-to-peer replication 点对点复制](#peer-to-peer-replication-点对点复制)
      2. [Master-slave replication 主从复制](#master-slave-replication-主从复制)
4. [Key-value database](#key-value-database)
   1. [when use](#when-use)
5. [Document database](#document-database)
   1. [when use](#when-use-1)
6. [Graph database](#graph-database)
   1. [when use](#when-use-2)

----------------------------------------------------------------------------------------------------

## CAP 理论
1. Consistency: A guarantee that every node in a distributed cluster returns  the same, most recent, successful write. Consistency refers to  every client having the same view of the data.
2. Availability: Every request received by a non-failing node in the system  must result in a response.
3. Partition tolerance: The cluster continues to function even if there is a "partition"  (communication break) between two nodes (both nodes are  up, but can't communicate).

### Consistency 在 CAP 和 ACID 理论里不同
CAP: Consistency in CAP theory means consistency between nodes of the system.

ACID: data is in a consistent state when a transaction  starts and when it ends.. At no time, after failure, the database (or more precisely the  data contained in it) is inconsistent. The letter C here refers to the transactional operations!

### CA, CP/AP
* 分布式系统应该具有分区容错性，
* 连接中断是一个可能因多种原因而发生的事件，因此这种情况不会损坏整个系统。 
* 因此，分布式系统通常构建在 CP 或 AP 类中

## BASE
While the **relational databases** work according to **ACID** paradigm, the **NoSQL databases** work according to **BASE** paradigm.

1. Basically Available – indicates that the  system does guarantee availability, in terms of the CAP  theorem.
2. Soft state – indicates that the state of the system may change  over time, even without input. This is because of the  eventual consistency model.
3. Eventual consistency – indicates that the system will become  consistent over time, given that the system doesn't receive  input during that time.

1. 基本可用——表明系统确实保证了可用性，根据 CAP 定理。 
2. 软状态——表示系统的状态可能会随着时间而改变，即使没有输入。 这是因为最终一致性模型。 
3. 最终一致性——表示系统将随着时间的推移变得一致，假设系统在这段时间内没有接收到输入。

## distributed database 分布式数据库
### Replication and sharding 复制和分片
1. 复制：银行柜台有多个同种服务项目的窗口。
复制涉及在每个节点上制作数据副本。 为了什么？ 在相同的数据集上启用并行操作。
2. 分片：银行柜台也会分不同服务项目的窗口。
根据特定标准对数据集进行划分。 每个节点只包含一些满足特定限制的数据。
#### Peer-to-peer replication 点对点复制
1. Peer-to-peer replication allows writing to any node.
2. The node coordinates data synchronization with other nodes.

1. 点对点复制允许写入任何节点。 
2. 节点协调与其他节点的数据同步。

![](2022-10-08-14-42-31.png)

#### Master-slave replication 主从复制
1. Writting is possible only through the master node.
2. The master node is responsible for data synchronization  between slave nodes.
3. Reading is possible from any node.

1. 只能通过主节点进行写入。 
2. 主节点负责从节点之间的数据同步。 
3. 可以从任何节点读取。

![](2022-10-08-14-43-25.png)


## Key-value database
1. Distributed hash table.
2. Storing key-value pairs.
3. Database is not aware of the value structure (black box).
4. Durability and extremely high performance and scalability.
5. Performance and scalability achieved by distribution.


1. 分布式哈希表。 
2. 存储键值对。 
3. 数据库不知道值结构（黑匣子）。 
4. 耐用性和极高的性能和可扩展性。 
5. 通过分发实现的性能和可扩展性。

### when use
1. To store large data of various types, the content of which we  do not want to analyze, but only search for it by a given key.
2. When we need very efficient data access.
3. When we need an extremely scalable solution.

1. 存储各种类型的大数据，我们不想分析其内容，而只是通过给定的键搜索它。 
2. 当我们需要非常高效的数据访问时。 
3. 当我们需要一个极具可扩展性的解决方案时。

## Document database
• Stores collections of JSON-like documents 
• Operates on the same document model as used in  applications (objects) 
• Flexible, semistructural and hierarchical nature of  documents allows them to evolve  depending on the needs of the application 
• Enable flexible indexing, efficient ad hoc  queries, and analysis of document sets 

• 存储类 JSON 文档的集合 
• 在与应用程序（对象）中使用的相同文档模型上运行 
• 文档的灵活、半结构化和分层特性允许它们根据应用程序的需要而发展 
• 启用灵活的索引，高效的临时 查询和分析文档集

### when use
1. When we need to store semi-structured documents.
2. When we need to analyse the semantics of data.
3. When the schema of data is not rigid.
4. When we need data model corresponding to applicational  model.

1. 当我们需要存储半结构化文档时。 
2. 当我们需要分析数据的语义时。 
3. 当数据的模式不是刚性的。 
4. 当我们需要应用模型对应的数据模型时。

## Graph database
1. Stores and operates on graphs  
2. It is possible to add and delete nodes and edges at any time.
3. The database can traverse and analyse a graph.
4. Effective traversing and analysis operations.
5. Constant calculation complexity for some operations.

1. 对图进行存储和操作。
2. 可以随时添加和删除节点和边。 
3. 数据库可以遍历和分析一个图。 
4. 有效的遍历和分析操作。 
5. 某些操作的恒定计算复杂度。

### when use
1. Data is strongly related - there are many relationships  between data.
2. Often queries concerns a long chain of relationships.
3. You can add a new type of data (node or edge) at any  time, without migrating the database to a new schema  version.
4. When we want to use graph analysis algorithms.

1. 数据是强相关的——数据之间有很多关系。 
2. 查询通常涉及一长串关系。
3. 您可以随时添加新类型的数据（节点或边），而无需将数据库迁移到新的架构版本。 
4. 当我们要使用图分析算法时。