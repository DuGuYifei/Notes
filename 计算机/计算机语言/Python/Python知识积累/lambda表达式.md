# lambda表达式

```PYTHON
lambda arguments: expression
lambda x: x**2
lambda x, y: x + y
lambda: "Hello, world!"
func = lambda x: x**2
result = func(3)
print(result)  # 输出 9
```

```PYTHON
map(lambda <argument>:<expression>, iter)

# Square all numbers in my_list
squared_list_lambda = list(map(lambda x: x * x, my_list))
```