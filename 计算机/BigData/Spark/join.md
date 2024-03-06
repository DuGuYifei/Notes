# join

连接操作是将两个不同的表按照共有列（即关键列）进行合并。例如，可以通过航班表中的tailnum和carrier列作为关键列，来合并另外一张只包含每架飞机信息的表planes，将两个表合并后，得到的新表包含了飞行每个航班的所有信息和对应的飞机信息。


1. Inner Join：只返回两个表中键匹配的行，这是默认的 join 类型；
2. Outer Join：返回左表和右表中的所有行，如果键在另一个表中没有匹配，则对应的值为 NULL；
3. Left Join：返回左表中的所有行和右表中的匹配行，如果右表中没有匹配，则对应的值为 NULL；
4. Right Join：返回右表中的所有行和左表中的匹配行，如果左表中没有匹配，则对应的值为 NULL；
5. Left Semi Join：只返回左表中的匹配行，不返回右表的数据；
6. Left Anti Join：只返回左表中不匹配的行，不返回右表的数据；
7. Cross Join：又称笛卡尔积，返回两个表中所有的行组合。

## join()除了笛卡尔积外
`join(df, on="", how="")`

how的取值，可以省略`_`
1. "inner"：内连接，返回两个表中都存在的行
2. "outer" 或 "full"：外连接，返回两个表中所有的行
3. "left_outer" 或 "left"：左外连接，返回左表中所有的行以及右表中能够和左表匹配的行
4. "right_outer" 或 "right"：右外连接，返回右表中所有的行以及左表中能够和右表匹配的行
5. "left_semi"：左半连接，只返回左表中能够和右表匹配的行
6. "left_anti"：左反连接，只返回左表中没有能够和右表匹配的行

```python
# Examine the data
print(airports.show())

# Rename the faa column
airports = airports.withColumnRenamed("faa", "dest")

# Join the DataFrames
flights_with_airports = flights.join(airports, "dest", "leftouter")

# Examine the new DataFrame
print(flights_with_airports.show())
```

## crossJoin()

```python
# Join the DataFrames
flights_with_airports = flights.crossJoin(airports)
```