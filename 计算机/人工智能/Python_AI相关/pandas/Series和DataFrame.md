# Series和DataFrame

## Series
Series是一种一维的标签数组，类似于带有标签的列表。每个Series对象包含两个数组，一个是标签数组，也称为索引，用于访问数据，另一个是实际数据数组。

```python
import pandas as pd

# 创建一个Series对象
# 使用默认整数索引
s = pd.Series([1, 3, 5, 7, 9])
print(s)

# output
# 0    1
# 1    3
# 2    5
# 3    7
# 4    9
# dtype: int64

# 显式指定索引
s1 = pd.Series([1, 2, 3, 4], index=['a', 'b', 'c', 'd'])
print(s1)
# output
# a    1
# b    2
# c    3
# d    4
# dtype: int64
```

## DataFrame
DataFrame是一个二维的表格结构，可以看作是由多个Series对象组成的。它有行索引和列索引，可以存储不同类型的数据。在DataFrame中，每列可以是不同的数据类型（如数字，字符串和日期等），并且可以针对每个列执行不同的操作。

```python

# 创建一个DataFrame对象
data = {'name': ['Alice', 'Bob', 'Charlie', 'David'],
        'age': [25, 30, 35, 40],
        'country': ['US', 'UK', 'Canada', 'Australia']}
df = pd.DataFrame(data)
print(df)


# output
#        name  age    country
# 0     Alice   25         US
# 1       Bob   30         UK
# 2   Charlie   35     Canada
# 3     David   40  Australia
```