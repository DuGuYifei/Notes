# DocumentDatabase

1. [Document store](#document-store)
2. [常见文档数据库](#常见文档数据库)
3. [MongoDB](#mongodb)
   1. [MongoDB features](#mongodb-features)
   2. [Tools](#tools)
   3. [JSON](#json)
      1. [JSON format](#json-format)
   4. [BSON format](#bson-format)
   5. [Representing related document](#representing-related-document)
      1. [Embedding](#embedding)
      2. [Referencing](#referencing)


## Document store
* semi-structured data
  * XML
  * JSON
  * YAML
  * HTML
* No data schema enforced
  * Each document different
* No relations between data
* No transactions
* Similar documents grouped in collections
  * Capped collections 固定大小的集合(**见下**)
* Data format readable by the database
  * updates of parts of documents possible
  * searching by contents of documents possible （数据库能解释文档内容）
  * retrieving portion of document possible
* Unstandardised CRUD operations
  * creation
  * retrieval
  * updates
  * deletion
* 尽管for XML Stores有很多标准化query（接上点）
  * XQuery (XML Query)
  * XQuery Update
  * XQuery Full Text
  * EXPath Extensions
  * EXQuery Extensions
  * XSLT
  * XForms
  * XProc

文档被分组为**集合**（关系表的等价物）。 从数据库机制的角度来看，**任何不同的文档都可以添加到一个集合中，尽管这会阻碍对以这种方式收集的数据进行有效的查询写入**。 因此，“逻辑上”将不同集合之间的不同文档类型分开符合用户的利益，尽管不需要所有文档都具有完全相同的结构。 在某些数据库中，还可以选择创建**Capped collections上限集合**（元素数量有限的集合）。

## 常见文档数据库
* ArangoDB
* BaseX
* Couchbase Server
* CouchDB
* Cosmos DB
* Dynamo DB
* MarkLogic
* MongoDB
* OrientDB
* RavenDB
* SimpleDB

其中 MongoDB 最常见，这些类都是基于它的

## MongoDB
* Document database
* Uses **BSON** format
* **MongoDB Query language**
* Community and Enterprise Editions
* MongoDB Atlas
* Version 1.0 released on February 2009

The mongo database is available in community (free), enterprise (with support) and atlas editions. Atlas is a cloud-based data storage service based on the mongo database.

mongo 数据库有社区（免费）、企业（有支持）和 atlas 版本。 **Atlas**是基于mongo数据库的**云端数据存储服务**

### MongoDB features
1. Aggregation
   1. Aggregation pipeline
   2. Map-Reduce
2. Indexes
3. Change Streams
4. Schema validation
   1. Json Schema
   2. Query Expression
5. Replication
6. Sharding
7. Security
   1. Authentication
   2. Authorisation
   3. Encryption
8. transactions
9. Suite(套件) of tools

解释：
1. aggregation (one of two mechanisms to choose from), i.e. obtaining information on the basis of a set of documents (e.g. average / total field value for all documents from a collection)
    聚合（可供选择的两种机制之一），即基于一组文档获取信息（例如，集合中所有文档的平均/总字段值）
2. change streams (the database informs you on an ongoing basis about changes in  "observed" data) 
   变化流（数据库持续通知您“观察到”数据的变化）
4. schema validation (optional), validation can be performed based on **JSON** schema or native query language (MongoDB Query language)
   schema验证（可选），验证可以基于JSON schema或原生查询语言（MongoDB Query language）
5. 复制（数据复制——在多台服务器上存储相同的数据）
6. sharding (division of data into subsets stored on different servers; can be combined  with replication, then each of the subsets is stored on more than one server)
   分片（将数据分成存储在不同服务器上的子集；可以与复制相结合，然后每个子集存储在多个服务器上）

### Tools
1. Atlas Kubernetes Operator
2. Charts
3. Database Tools
4. Connector for BI
5. Compass
6. Kafka Connector
7. Shell

这是部分工具，对我们来说最重要的是允许我们与数据库 (shell) 通信的文本工具。

MongoDB charts
![](2022-11-28-14-46-47.png)

### JSON
* JavaScript Object Notation
* Lightweight data interchange format
* Based On JavaScript
* Language independent

JSON 语言在 W3C 编写的 RFC 7159 中定义。 该名称来自“JavaScript Object Notation（符号）”一词，该语言本身是一种用于数据交换的轻量级格式。 尽管该语言基于 JavaScript，但它独立于编程语言。

#### JSON format
* Object - `{name/value pairs}`
* Name/value pairs - `"name":value`
* Value - object, array/string, string, number, boolean(true/false), empty(null)
* Array - `[(value)*]`

### BSON format
* **Bianry JSON**
* Binary-encoded JSON-like documents
* Additional value types
  * ObjectID: 12bytes id
    * ({_id: ObjectId("5099803df3f4948bd2f98391")})
  * Date: unix encoded 64-bit value
    * ({birth: new Date('Jun 23, 1912')},
    * {timestamp: new Date()})

The BSON format is derived from the JSON format. The name is derived from **"Binary  encoded JSON"** and describes the essence of the format well. The BSON format is **an optimization of the JSON format** for efficient storage / search.
For the database user, the differences between the formats are small and come down to **two new data types (ObjectID and date)** and **no need to use quotation marks in field names when these names are single-word**.

对于数据库用户来说，格式之间的差异很小，归结为**两种新的数据类型（ObjectID 和日期）**，当这些名称是**单个单词时，不需要在字段名称中使用引号**。

### Representing related document
1. Embedding
   1. storing related documents together
2. Referencing
   1. storing a combination of unique fields from one document in another 将一个文档中的唯一字段组合存储在另一个文档中
3. Data structure and access characteristic dependant 数据结构和访问特性依赖

The Mongo database does not support dependencies between documents, which  means it will not check consistency between related documents (there is no  equivalent for a foreign key constraint). This does not mean, however, that these  relationships cannot be expressed.
Mongo 数据库不支持文档之间的依赖关系，这意味着它不会检查相关文档之间的一致性（没有外键约束的等效项）。 然而，这并不意味着这些关系无法表达。

Two approaches are possible here:
1. nesting(Embedding) (due to the fact that the value of a field in a JSON document may be another  document, the related element can be added as a field of the document with which it  is related to) | 嵌套（由于JSON文档中某个字段的值可能是另一个文档，所以可以将相关元素添加为与其相关的文档的字段
2. referencing (you can also store a combination of fields in one of the related  documents that will allow you to uniquely identify (and search for) the second one). | 引用（您还可以将字段组合存储在一个相关文档中，这样您就可以唯一标识（和搜索）第二个文档）。

The choice of strategy will depend not only on the data structure or the nature of the  dependency expressed, but also on the typical method of accessing related data. | 策略的选择不仅取决于数据结构或所表达的依赖关系的性质，还取决于访问相关数据的典型方法。 

#### Embedding
* For "contains" relationships
* For one-to-many relationships
* Single CRUD operation for the whole document set
  * Faster reads?
* Data duplication
* Data manipulation anomalies(异常)
* Privileged top document
* Maximum document size: 16MB

优点：
a single read/write operation allows both related documents to be retrieved/modified, which has the  potential to speed up the read operation if typically both documents are retrieved  together.
**单个读/写操作允许检索/修改两个相关文档，如果通常同时检索两个文档，这有可能加快读取操作。**

Additionally, manipulating (writing queries) on the containing document is easier than on the nested element.
此外，对包含文档的操作（编写查询）比对嵌套元素的操作更容易。


缺点：
The disadvantage of this approach is the need to **duplicate** the same data in the case  of a **many-to-many** relationships (the same document must be nested in many related documents), which **increases memory consumption**, and may also cause **data manipulation anomalies** (in the case when a nested document is being modified and it is contained in many parent documents, it is possible to **skip some copies of the document during the update operation**).
这种方式的缺点是在**多对多**关系的情况下需要复制相同的数据（同一个文档必须嵌套在很多相关的文档中），增加了内存消耗，也可能导致**数据操作异常**（在修改嵌套文档并且它包含在许多父文档中的情况下，可以在更新操作期间**跳过文档的某些副本**）。

In addition, the maximum document size in MongoDB (16 MB) may limit the  applicability of the method。
此外，MongoDB 中的最大文档大小 (16 MB) 可能会限制该方法的适用性

#### Referencing
* For many-to-many relationships
* For more complicated data structures
* Uni- or bi- directional 单或双向操作
* Separate CRUD operations for each document in a set
  * Faster updates?
* Limit on reference array size?
  * Reference documents possible
* No support for foreign keys

参考文献是多对多相关文档的自然候选者，当**两种以上的文档相互关联**时。 引用（标识相关文档的值）可以只放在**一个文档**中，也可以放在**两个文档**中。

If you use a reference, CRUD operations on each of the related documents will have to be performed separately. As a result, the operation of **updating only one of the related documents may be faster** due to the smaller size of the modified document.
For references, the **maximum document size is also a potential limitation** (especially  when referencing multiple documents), but it is **less severe than for nesting**. It is also  possible to use separate documents to **indicate relationships** between documents  (like relationship tables in relational databases).
如果您使用引用，则必须分别对每个相关文档执行 CRUD 操作。 结果，由于修改后的文档的尺寸较小，仅更新其中一个相关文档的操作可能会更快。
对于引用，最大文档大小也是一个潜在的限制（尤其是在引用多个文档时），但它没有嵌套那么严重。 也可以使用单独的文档来指示文档之间的关系（如关系数据库中的关系表）。

The Mongo database does not support foreign keys, so it may happen that the inserted values ​that point to another document will not actually point to anything, or that the document will be deleted despite the existence of a reference to it. When using references, it is the user's responsibility to maintain referential consistency.
Mongo 数据库不支持外键，因此可能会发生指向另一个文档的插入值实际上不会指向任何内容，或者尽管存在对它的引用，但该文档将被删除。 使用引用时，用户有责任保持引用的一致性。

