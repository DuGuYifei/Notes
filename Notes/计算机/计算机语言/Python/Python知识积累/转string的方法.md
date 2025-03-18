# 转string的方法

## 使用字符串格式化将其他数据类型转换为字符串
### %
```python
a = 42
str_a = "The answer is %s." % a  # 使用%s占位符将整数42插入字符串中
print(str_a)  # 输出：'The answer is 42.'

b = [1, 2, 3]
str_b = "The list is %s." % b  # 使用%s占位符将列表插入字符串中
print(str_b)  # 输出：'The list is [1, 2, 3].'
```

### 使用f
```python
dates_range = [f"{d.year}-{d.month}-{d.day}" for d in dates_range]
```

## str()

将其他数据类型转换为字符串
```python
a = 42
str_a = str(a)  # 将整数42转换为字符串
print(str_a)  # 输出：'42'

b = [1, 2, 3]
str_b = str(b)  # 将列表转换为字符串
print(str_b)  # 输出：'[1, 2, 3]'
```

## repr()
```python
a = 42
repr_a = repr(a)  # 将整数42转换为字符串
print(repr_a)  # 输出：'42'

b = [1, 2, 3]
repr_b = repr(b)  # 将列表转换为字符串
print(repr_b)  # 输出：'[1, 2, 3]'
```