# list

## map filter
```python
# Square all numbers in my_list
squared_list_lambda = list(map(lambda x: x * x, my_list))

# Filter numbers divisible by 10
filtered_list = list(filter(lambda x: (x%10 == 0), my_list2))
```