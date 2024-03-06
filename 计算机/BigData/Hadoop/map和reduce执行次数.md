# map和reduce执行次数

在Hadoop的MapReduce框架中，map函数是由框架调用的，而不是由用户显式调用。map函数会被用于每个输入分片中的每一条记录。因此，**如果有多个输入分片，map函数将被调用多次，每次都处理一个输入分片。**

在map函数内部，您可以使用循环处理当前输入分片中的所有记录，但这通常是不必要的，因为MapReduce框架会自动迭代每个输入记录，并将其传递给map函数进行处理。

一旦所有输入记录都已经经过map函数处理后，它们将被传递给reduce函数进行聚合处理。**reduce函数只会被每个reducer调用一次**，并且处理整个map输出的数据集。在reduce函数中，您可以使用循环迭代map输出的键值对，但这也不是必需的，因为Hadoop框架会自动迭代它们，并将它们按键排序分组。

因此，可以说是reduce函数循环执行，但不是用户手动控制的循环，而是由框架自动迭代。

当多个 Mapper 任务的输出被传输到 Reduce 阶段时，Hadoop 会将所有具有相同 key 的 value 组合在一起，然后传递给 Reduce 函数进行处理。

Reduce 函数的输入分为两个阶段：**shuffle 阶段和 reduce 阶段**。在 shuffle 阶段中，Hadoop 会将相同 key 的 value 分组，按照 key 进行排序，并将结果写入本地磁盘或者网络传输给 Reduce 任务。在 reduce 阶段中，Reduce 任务会从 shuffle 阶段输出的中间结果中读取数据，并对每个 key 的所有 value 进行处理。如果有多个 key-value 组合，Reduce 函数就会被调用多次。

通常情况下，Reduce 函数的调用次数与 reducer 的数量有关。如果设置了多个 reducer，Reduce 函数就会被调用多次，每个 reducer 处理不同的数据分片。如果只设置了一个 reducer，Reduce 函数就只会被调用一次。

**所以每种key只会出现在一个reduce里**