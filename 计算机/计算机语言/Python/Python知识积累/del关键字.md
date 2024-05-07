# del

在 Python 中，del 是一个关键字，用来删除对象。使用 del 关键字可以从内存中删除一个或多个对象，也可以删除对象中的某一部分，例如列表中的元素或字典中的键值对。这是一个非常有用的特性，尤其是当你需要优化内存使用或确保某些数据在接下来的代码中不再可用时。

```python
x = 10
print(x)  # 输出 10
del x
print(x)  # 这里会引发错误，因为 x 已经被删除

a = [1, 2, 3, 4, 5]
del a[1]  # 删除索引为 1 的元素，即删除 2
print(a)  # 输出 [1, 3, 4, 5]
del a[1:3]  # 删除索引从 1 到 2 的元素，即删除 3 和 4
print(a)  # 输出 [1, 5]

d = {'a': 1, 'b': 2, 'c': 3}
del d['b']  # 删除键为 'b' 的项
print(d)  # 输出 {'a': 1, 'c': 3}

class MyClass:
    def __init__(self):
        self.x = 10
        self.y = 20
obj = MyClass()
del obj.x
print(obj.x)  # 这里会引发错误，因为属性 x 已经被删除
```