# __init__包

目录结构
```
my_package/
    __init__.py
    module1.py
    module2.py
```


`__init__.py` 文件的内容如下：
```python
# __init__.py

# 导入子模块
from .module1 import some_function
from .module2 import MyClass
```

使用
```python
# 使用 my_package 包中的函数和类
from my_package import some_function, MyClass

# 调用函数
some_function()

# 创建类的实例
obj = MyClass()
```