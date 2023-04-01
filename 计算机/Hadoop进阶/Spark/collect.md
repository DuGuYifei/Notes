# collect

```python
# Create map() transformation to cube numbers
cubedRDD = numbRDD.map(lambda x: x * x * x)

# Collect the results
numbers_all = cubedRDD.collect()

# Print the numbers from numbers_all
for numb in numbers_all:
	print(numb)
```

