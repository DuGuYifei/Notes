# set


`list(set(x) - TRIVIAL_TOKENS)`

在这段代码中，假设x是一个列表，TRIVIAL_TOKENS是一个集合，代码的作用是去除x中的所有在TRIVIAL_TOKENS中出现过的元素，并返回去重后的列表。

具体来说，这段代码的执行过程如下：

1. set(x)将列表x转换为集合，去除其中的重复元素。
2. TRIVIAL_TOKENS是一个集合，表示需要去除的元素。
3. set(x) - TRIVIAL_TOKENS表示将TRIVIAL_TOKENS从set(x)中去除。这是通过集合的差集操作实现的，即将TRIVIAL_TOKENS中出现过的元素从set(x)中删除。
4. list(set(x) - TRIVIAL_TOKENS)将得到的集合转换回列表，并返回该列表。这里使用了list()函数将集合转换为列表。

