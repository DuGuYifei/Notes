# first

用于获取DataFrame中的第一行数据，并将其作为一个Row对象返回。
```PYTHON
# create a DataFrame
df = spark.createDataFrame([(1, 'John', 25), (2, 'Mike', 30), (3, 'Sara', 22)], ['id', 'name', 'age'])

# get the first row
first_row = df.first()

# print the first row
print(first_row)
```