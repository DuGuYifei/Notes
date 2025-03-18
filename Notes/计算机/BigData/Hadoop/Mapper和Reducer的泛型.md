# Mapper和Reducer的泛型

## 四个泛型
`Mapper/Reducer<Object, Text, Text, IntWritable>`

1. 输入键类型（Key in）：通常为 Object。
2. 输入值类型（Value in）：通常为 Text，表示每个输入键对应的值。
3. 输出键类型（Key out）：通常为 Text，表示 Mapper 阶段的输出键，也就是中间键。
4. 输出值类型（Value out）：通常为 IntWritable，表示 Mapper 阶段的输出值，也就是中间值。

## 第一个Mapper的泛型
在 MapReduce 编程模型中，第一个 Mapper 的输入键是 Object，这是一个通用类型，表示输入键可以是任何类型。但通常情况下，第一个 Mapper 的输入键类型是 `LongWritable`，表示输入文件的字节偏移量，即每行数据在文件中的位置，第二个泛型类型是 Text，表示输入数据类型为文本数据。因此，第一个 Mapper 的泛型类型通常是：
`Mapper<LongWritable, Text, Text, IntWritable>`

## Writable 接口的原因
在 MapReduce 中，输入数据和中间数据的类型必须是可序列化的（serializable）和可比较的（comparable），这样才能在分布式环境下进行传输和排序。在 Hadoop 中，WritableComparan;e 接口就是为此而设计的，因为它是可序列化的和可比较的。

[WritableComparable接口](WritableComparable接口.md)
