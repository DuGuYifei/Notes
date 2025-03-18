# Combiner 和 Reducer

Combiner 函数是一个可选的中间函数，发生在 Map 阶段，Mapper 执行完成后立即执行。使用 Combiner 有如下两个优势：

* Combiner 可以用来减少发送到 Reducer 的数据量，从而提高网络效率。
* Combiner 可以用于减少发送到 Reducer 的数据量，这将提高 Reduce 端的效率，因为每个 reduce 函数将处理相比于未使用 Combiner 之前更少的记录。

## 区别
Combiner 需要实现 Reducer 接口。Combiner 只能用于特定情况：

1. 与 Reducer 不同，Combiner 有一个约束，**Combiner 输入/输出键和值类型必须与 Mapper 的输出键和值类型相匹**配。而 **Reducer 只是输入键和值类型与 Mapper 的输出键和值类型相匹配**。
2. Combiner 只能用于满足交换律（a.b = b.a）和结合律（a.(b.c)= (a.b).c）的情况。这也意味着 Combiner 可能只能用于键和值的一个子集或者可能不能使用。
3. Reducer 可以从多个 Mapper 获取数据。Combiner 只能从一个 Mapper 获取其输入。

## 能复用吗
**Combiner 与 Reducer 结构相同**，因为 Combiner 和 Reducer 都是对 Mapper 的输出进行处理。这给了我们一个复用 Reducer 作为 Combiner 的好机会。但问题是，复用 Reducer 作为 Combiner 总是可行的吗？

```
A:[1,2,3]
B:[4,5]
```

求最大值可以，求平均值不行。
1. 先combiner对文件A，B的Map记过分别求最大值然后发送到Reducer，
2. 然后Reducer对两个最大值求最大值。
