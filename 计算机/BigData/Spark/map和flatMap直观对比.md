# map和flatMap直观对比

## data
```python
for line in contributions.collect():
    print(line)
```
```
(u'A', ([u'B', u'C', u'D'], 0.25))
(u'D', ([u'B', u'C'], 0.25))
(u'C', ([u'C'], 0.25))
(u'B', ([u'A', u'D'], 0.25))
```

## map
```python
contributions = contributions.map(lambda x: [(otherPage, x[1][1] / len(x[1][0])) for otherPage in x[1][0]])
for line in contributions.collect():
    print(line)
print(contributions.collect())
```
```
[(u'B', 0.08333333333333333), (u'C', 0.08333333333333333), (u'D', 0.08333333333333333)]
[(u'B', 0.125), (u'C', 0.125)]
[(u'C', 0.25)]
[(u'A', 0.125), (u'D', 0.125)]

[[(u'B', 0.08333333333333333), (u'C', 0.08333333333333333), (u'D', 0.08333333333333333)], [(u'B', 0.125), (u'C', 0.125)], [(u'C', 0.25)], [(u'A', 0.125), (u'D', 0.125)]]
```

## flatMap
注意lamda里是个`[]`列表，而不是`()`元组
```python
contributions = contributions.flatMap(lambda x: [(otherPage, x[1][1] / len(x[1][0])) for otherPage in x[1][0]])
for line in contributions.collect():
    print(line)
print(contributions.collect())
```

```
(u'B', 0.08333333333333333)
(u'C', 0.08333333333333333)
(u'D', 0.08333333333333333)
(u'B', 0.125)
(u'C', 0.125)
(u'C', 0.25)
(u'A', 0.125)
(u'D', 0.125)
[(u'B', 0.08333333333333333), (u'C', 0.08333333333333333), (u'D', 0.08333333333333333), (u'B', 0.125), (u'C', 0.125), (u'C', 0.25), (u'A', 0.125), (u'D', 0.125)]
```