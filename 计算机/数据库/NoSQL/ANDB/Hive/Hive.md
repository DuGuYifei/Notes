# Hive


## 定义
Apache Hive 是一个建立在 Apache Hadoop 之上的数据仓库软件项目，用于提供数据查询(query)和分析(analysis)。

我们可以将 HIVE 视为允许访问存储在 HDFS 中的数据的层。

Hive 的独特部署是为了在处理**大量数据（large volumes of data）**时提供数据查询、强大的数据分析和数据汇总 （querying of data, powerful data analysis, and data summarization）。

Hive 的组成部分是 **HiveQL**，它是一个类似于 SQL 的接口，广泛用于查询存储在数据库中的数据。

## Hive components
![](2022-11-21-10-47-03.png)
展示了 HIVE 组件(components)和查询执行过程(query execution process)的总体思路。

Components: 
* UI – The user interface for users to **submit queries and other operations** to the system.
* Driver – The component which **receives the queries**. This component implements the notion of **session handles** and provides **execute and fetch APIs** modeled on **JDBC/ODBC interfaces**.
* Compiler – The component that **parses the query**, does **semantic（语义学的） analysis** on the different query blocks and query expressions and eventually **generates an execution plan** with the help of the table and partition metadata looked up from the **metastore**.
* Metastore – The component that **stores all the structure information** of the various **tables** and **partitions** in the warehouse including **column and column type information**.
* Execution Engine – The component which **executes the execution plan** created by the **compiler**.

**How a typical query flows through the system?**
The UI calls the execute interface to the Driver (step 1). The Driver creates a session handle for the query and sends the query to the compiler to generate an execution plan (step 2 and 5). The compiler gets the necessary metadata from the metastore (steps 3 and 4). The execution engine executes the query (big blue arrow)

## Storing data
### 可以创建的两种table
1. Internal
  - 数据是**临时**的 
  - 您希望 Hive **管理表和数据的生命周期**。
2. External
   - the data is also **used outside** of Hive, for example, the data files are updated by another process (that doesn't lock the files); 
   - data needs to **remain in the underlying location（底层）**, even after **dropping** the  table; 
   - you need a **custom location**, such as a non-default storage account; 
   - a program **other** than hive **manages the data format, location, and so on**.

### 数据可以如何储存
#### TextFile
```
"Last name","First name","Student number","Test1","Test2","Test3","Test4","Final","Grade"
"Alfalfa","Aloysius","123-45-6789",40.0,90.0,100.0,83.0,49.0,"D-"
"Alfred","University","123-12-1234",41.0,97.0,96.0,97.0,48.0,"D+"
"Gerty","Gramma","567-89-0123",41.0,80.0,60.0,40.0,44.0,"C"
"Android","Electric","087-65-4321",42.0,23.0,36.0,45.0,47.0,"B-"
"Bumpkin","Fred","456-78-9012",43.0,78.0,88.0,77.0,45.0,"A-"
```
第一个解决方案是一个文本文件。 包含来自特定表的数据的文件示例，该表存储有关学生的分数和最终成绩的信息。

#### SequenceFile
##### 基本介绍
Sequence files:
- binary files containing serialized key/value pairs,
- you can **compress** a sequence file at the **record** (key-value pair) or **block** levels,
- binary files provide **faster** read/write than that of text file format.
序列文件： 
- 包含序列化键/值对的二进制文件， 
- 您可以在记录（键值对）或块级别压缩序列文件， 
- 二进制文件提供比文本文件格式更快的读/写。

三种 sequence files:
1. Uncompressed key/value records.
2. **Record** compressed key/value records - **only 'values'** are compressed here.
3. **Block** compressed key/value records - **both keys and values** are collected in 'blocks' **separately** and compressed. **The size of the 'block' is configurable**.
1. 未压缩的键/值记录。
2. 记录压缩的键/值记录——这里只压缩“值”。
3. 块压缩键/值记录——键和值分别收集在“块”中并压缩。 “块”的大小是可配置的。

PS：性能:处理大量小文件 < 处理少量大文件，所以有了sequence file

We know that Hadoop's performance is drawn out when we work with a small  number of files with big size rather than a large number of files with small size. If the  size of a file is smaller than the typical block size in Hadoop, we consider it as a small  file. Due to this, a number of metadata increases which will become an overhead to  the NameNode. To solve this problem sequence files are introduced in Hadoop.
**Sequence files act as a container to store the small files.**

Sequence files are flat files consisting of binary key-value pairs. When Hive converts  queries to MapReduce jobs, it decides on the appropriate key-value pairs to be used  for a given record. Sequence files are in the binary format which can be split and the  main use of these files is to club two or more smaller files and make them as a one  sequence file.
序列文件是由二进制键值对组成的平面文件。 当 Hive 将查询转换为 MapReduce 作业时，它会决定将适当的键值对用于给定记录。 **序列文件是可以分割的二进制格式，这些文件的主要用途是将两个或多个较小的文件组合成一个序列文件。**

In Hive we can create a sequence file by specifying `STORED AS SEQUENCEFILE` in 
the end of a `CREATE TABLE` statement.

##### the structure of sequence file
根据压缩和块压缩是否处于活动状态，序列文件基本上有 3 种不同的文件格式。

然而，所有上述格式共享一个共同的标题：
Header:
- version - A byte array: 3 bytes of magic header 'SEQ', followed by 1 byte of actual version no. (e.g. SEQ4 or SEQ6)
- keyClassName - String
- valueClassName - String
- compression - A boolean which specifies if compression is turned on for keys/values in this file.
- blockCompression - A boolean which specifies if block compression is turned on for keys/values in this file.
- compressor class - The classname of the CompressionCodec which is used to compress/decompress keys and/or values in this SequenceFile (if compression is enabled).
- metadata - SequenceFile.Metadata for this file (key/value pairs)
- sync - A sync marker to denote end of the header.

标头：
- 版本 - 一个字节数组：3 个字节的魔术标头“SEQ”，后跟 1 个字节的实际版本号。  （例如 SEQ4 或 SEQ6） 
- keyClassName - String 
- valueClassName - String 
- compression - 一个布尔值，指定是否为此文件中的键/值打开压缩。
- blockCompression - 一个布尔值，指定是否为此文件中的键/值打开块压缩。
- compressor class - CompressionCodec 的类名，用于压缩/解压缩此 SequenceFile 中的键和/或值（如果启用压缩）。
- 元数据 - 此文件的 SequenceFile.Metadata（键/值对） 
- sync - 一个同步标记来表示标头的结尾。

Uncompressed & RecordCompressed Writer Format:
```
Header
(version, metadata, compressed, …)
Record
- record length
- key length
- key
- value (compressed - 1 or not - 2)
A sync-marker every few k bytes or so.
```
未压缩和记录压缩的编写器格式：
- 标头 
- 记录 
  - 记录长度
  - 密钥长度 
  - 密钥 
  - (压缩？)值 
- 每隔几 k 字节左右的同步标记

The sync marker permits seeking to a random point in a file and then re-synchronizing input with record boundaries. This is required to be able to efficiently split large files for MapReduce processing.
同步标记允许查找文件中的随机点，然后将输入与记录边界重新同步。 这是为了能够有效地拆分大文件以进行 MapReduce 处理所必需的。

The format for the BlockCompressedWriter is as follows:
```
Header
(version, metadata, compressed, …)
Record Block
- A sync-marker 
- CompressedKeyLengthsBlockSize
- CompressedKeyLengthsBlock
- CompressedKeysBlockSize
- CompressedKeysBlock
- CompressedValueLengthsBlockSize
- CompressedValueLengthsBlock
- CompressedValuesBlockSize
- CompressedValuesBlock
```
键长度和值长度的压缩块由以 ZeroCompressedInteger 格式编码的各个键/值的实际长度组成。

##### 为什么使用它
Now, one of the main problem that sequence file format solves is the problem  of processing too many small files in Hadoop. As you know Hadoop is not  good for processing large number of small files as referencing (memory) large  amounts of small files generates a lot of overhead for the namenode. Besides  this memory overhead, the second problem arises in terms of number of  mappers as more number of mappers will be executed for each files (as the file  size is smaller than that of block).

现在，序列文件格式解决的主要问题之一是**Hadoop中处理过多小文件的问题**。 如您所知，**Hadoop 不适合处理大量小文件**，因为引用（内存）大量小文件会为名称节点产生大量开销。 除了这个内存开销之外，**第二个问题是映射器（Mapper）的数量**，因为每个文件将执行更多的映射器（因为文件大小小于块的大小）。

### RCFile
#### Horizontal row-store
![](2022-11-22-21-29-22.png)

Now, let me remind the idea of **horizontal row-store**. **The set of rows is stored in one block. The whole block is always stored on the same node**
现在，让我提醒一下水平行存储的概念。 一组行存储在一个块中。 整个区块总是存储在同一个节点上

1. Disadvantages: 
   - **cannot provide fast query** processing due to unnecessary column reads if  only a subset of columns in a table  are needed in a query; 
   - it is **not easy** for row-store to **achieve a high data compression ratio** due to mixed columns with different data domains.

缺点： 
- 如果查询中只需要表中列的子集，则由于不必要的列读取而无法提供快速查询处理；  
- 由于具有不同数据域的混合列，行存储不容易实现高数据压缩比。

1. Advantages: 
   - it has **fast data loading**, what is  important in Hadoop file system; 
   - strong **adaptive** ability to **dynamic  workloads**; 
   - row-store guarantees that all fields in  the **same record** is located in the  **same cluster node** since they are in  the **same HDFS block**.

优点： 
- 它具有快速的数据加载，这在 Hadoop 文件系统中很重要；  
- 对动态工作负载的适应能力强； 
- 行存储保证同一记录中的所有字段位于同一集群节点中，因为它们位于同一 HDFS 块中。

#### Parquet: Column-store

![](2022-11-22-21-35-44.png)

1. Disadvantages: 
- **cannot** provide **fast query** processing in Hadoop-based systems due to high  overhead of a tuple reconstruction; 
- **cannot** guarantee that all fields in the  **same** record are located in the **same**  cluster node.

缺点： 
- 由于元组重建的高开销，无法在基于 Hadoop 的系统中提供快速查询处理；  
- 无法保证同一记录中的所有字段都位于同一集群节点中。

2. Advantages: 
- can **avoid** reading **unnecessary**  columns during a query execution;
- can **easily** achieve a **high  compression ratio** by compressing  each column within the same data  domain;

优点： 
- 可以避免在查询执行期间读取不必要的列；  
- 可以通过压缩同一数据域内的每一列轻松实现高压缩率；

#### Row Columnar File 行列式文件
![](2022-11-22-21-39-48.png)
问题是如何提供快速查询处理并确保同一记录的所有字段都位于同一节点中。 这个需求的答案是Row Columnar File，**它把所有的记录分成行组，每个行组存储在同一个节点上，但是是以列的方式。**

- has comparable data loading speed and workload adaptivity with the row-store, 
- is read-optimized by avoiding unnecessary column reads during table scans, 
- uses column-wise compression and thus provides efficient storage space utilization.

- 具有与行存储相当的数据加载速度和工作负载适应性， 
- 通过在表扫描期间避免不必要的列读取来进行读取优化，
- 使用列式压缩，从而提供高效的存储空间利用率。

#### Optimized Row Columnar File
- complex types are supported (struct, list, map, union) 
- simple indexes stored within the file (skip row groups that do not pass  predicate filtering, seek to a given row) 
- compression depending on the data types 
- ...

- 支持复杂类型（结构、列表、映射、联合） 
- 存储在文件中的简单索引（跳过不通过谓词过滤的行组，查找给定行） 
- 根据数据类型进行压缩 
- ...

### Json
The other way of storing the data are JSON files.

## AVRO - data serialization system
### 介绍
Serialization is the **process of converting an object into a stream of bytes to store the object or transmit it to memory, a database, or a file.**
Its main purpose is to save the **state of an object** in order to be able to **recreate it when needed**.
The **reverse process** is called **deserialization**.

![](2022-11-22-21-48-12.png)

The producer provides **binary data** and **data schema**. The consumer according to data  schema **deserialize** binary data.
生产者提供二进制数据和数据模式。 消费者根据数据模式反序列化二进制数据。

### The example of Avro schema 
![](2022-11-22-21-49-44.png)
An Avro schema is created using JSON format.

* type: identifies the JSON field type.
For Avro schemas, this must always be **record** when it is specified at the schema's top level. **The type record means that there will be multiple fields defined**.
* namespace: identifies the namespace in which the object  lives.
Essentially, this is meant to be a URI that has meaning to you  and your organization. It is used to differentiate one schema  type from another should they share the same name.
* name: the schema name which, when combined with the  namespace.
Uniquely identifies the schema within the store. In the above  example, the fully qualified name for the schema is  com.example.FullName.
* fields: the actual schema definition.
It defines what fields are contained in the value, and the data  type for each field. A field can be a simple data type, such as an  integer or a string, or it can be complex data. 

* type：标识JSON字段类型。
对于 Avro 模式，当它在模式的顶层指定时，它必须始终被记录。 类型记录意味着将定义多个字段。
* 命名空间：标识对象所在的命名空间。
本质上，这是一个对您和您的组织有意义的 URI。 如果它们共享相同的名称，它用于将一种模式类型与另一种模式类型区分开来。
* 名称：模式名称，当与名称空间组合时。
唯一标识商店中的架构。 在上面的示例中，架构的完全限定名称是 com.example.FullName。
* fields：实际的模式定义。
它定义值中包含哪些字段，以及每个字段的数据类型。 字段可以是简单的数据类型，例如整数或字符串，也可以是复杂的数据。
