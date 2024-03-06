# sparksession.table()

sparksession.table()返回一个DataFrame，这个DataFrame是一个已经注册的表的引用。这个DataFrame可以用来查询这个表。

比如`spark.table("flights")`是一个Spark SQL语句，用于从SparkSession中的默认数据库中获取名为"flights"的表。这里使用的是Spark SQL语言中的表查询语句，它会将指定的表作为一个DataFrame返回。在这个DataFrame上可以执行各种数据操作和转换。