# rdd案例_创建_MapReduceCombineSort



```python
import findspark

findspark.init()
```


```python
import pyspark

sc = pyspark.SparkContext(appName="lab")
spark = pyspark.SQLContext(sc)
```


```python
from pyspark.sql import SparkSession

spark = SparkSession.builder.getOrCreate()
input_rdd = spark.sparkContext.textFile("/user/adampap/stackOverflow/shortStackOverflow.txt")

for line in input_rdd.collect():
    print(line)

```

    1,100,102,,2,Python
    2,101,,100,5,
    2,102,,100,9,
    2,103,,100,3,
    1,104,,,2,Python
    2,105,,104,8,
    2,106,,104,5,
    1,200,,,2,C#
    2,201,,200,5,
    2,202,,200,1,
    2,203,,200,8,
    2,204,,200,8,
    2,205,,200,8,
    1,206,,,1,C#
    2,207,,206,11,
    2,208,,206,6,
    1,300,,,9,Java
    1,301,304,,7,Java
    2,302,,301,9,
    2,303,,301,3,
    2,304,,301,9,
    1,305,306,,3,Java
    2,306,,305,5,
    1,307,309,,3,Java
    2,308,,307,5,
    2,309,,307,5,
    1,400,402,,2,PHP
    2,401,,400,2,
    2,402,,400,7,
    1,403,404,,2,PHP
    2,404,,403,2,



```python
data = input_rdd.map(lambda line: line.split(","))
for row in data.collect():
    print(row)
```

    [u'1', u'100', u'102', u'', u'2', u'Python']
    [u'2', u'101', u'', u'100', u'5', u'']
    [u'2', u'102', u'', u'100', u'9', u'']
    [u'2', u'103', u'', u'100', u'3', u'']
    [u'1', u'104', u'', u'', u'2', u'Python']
    [u'2', u'105', u'', u'104', u'8', u'']
    [u'2', u'106', u'', u'104', u'5', u'']
    [u'1', u'200', u'', u'', u'2', u'C#']
    [u'2', u'201', u'', u'200', u'5', u'']
    [u'2', u'202', u'', u'200', u'1', u'']
    [u'2', u'203', u'', u'200', u'8', u'']
    [u'2', u'204', u'', u'200', u'8', u'']
    [u'2', u'205', u'', u'200', u'8', u'']
    [u'1', u'206', u'', u'', u'1', u'C#']
    [u'2', u'207', u'', u'206', u'11', u'']
    [u'2', u'208', u'', u'206', u'6', u'']
    [u'1', u'300', u'', u'', u'9', u'Java']
    [u'1', u'301', u'304', u'', u'7', u'Java']
    [u'2', u'302', u'', u'301', u'9', u'']
    [u'2', u'303', u'', u'301', u'3', u'']
    [u'2', u'304', u'', u'301', u'9', u'']
    [u'1', u'305', u'306', u'', u'3', u'Java']
    [u'2', u'306', u'', u'305', u'5', u'']
    [u'1', u'307', u'309', u'', u'3', u'Java']
    [u'2', u'308', u'', u'307', u'5', u'']
    [u'2', u'309', u'', u'307', u'5', u'']
    [u'1', u'400', u'402', u'', u'2', u'PHP']
    [u'2', u'401', u'', u'400', u'2', u'']
    [u'2', u'402', u'', u'400', u'7', u'']
    [u'1', u'403', u'404', u'', u'2', u'PHP']
    [u'2', u'404', u'', u'403', u'2', u'']



```python
# step1:
data1 = data.map(lambda x: ((int(x[1]) if x[0] == '1' else int(x[3])),
                                  (
                                      ((1 if x[0] == '1' else 0), 
                                       (0 if x[0] == '1' else 1))
                                      if x[0] == '2' 
                                      else
                                      ((1 if x[0] == '1' else 0), 
                                       (0 if x[0] == '1' else 1),
                                       (True if x[2] != '' else False),
                                       x[5])
                                  )
                                 ))
for row in parsed_data.collect():
    print(row)
```

    (100, (1, 0, True, u'Python'))
    (100, (0, 1))
    (100, (0, 1))
    (100, (0, 1))
    (104, (1, 0, False, u'Python'))
    (104, (0, 1))
    (104, (0, 1))
    (200, (1, 0, False, u'C#'))
    (200, (0, 1))
    (200, (0, 1))
    (200, (0, 1))
    (200, (0, 1))
    (200, (0, 1))
    (206, (1, 0, False, u'C#'))
    (206, (0, 1))
    (206, (0, 1))
    (300, (1, 0, False, u'Java'))
    (301, (1, 0, True, u'Java'))
    (301, (0, 1))
    (301, (0, 1))
    (301, (0, 1))
    (305, (1, 0, True, u'Java'))
    (305, (0, 1))
    (307, (1, 0, True, u'Java'))
    (307, (0, 1))
    (307, (0, 1))
    (400, (1, 0, True, u'PHP'))
    (400, (0, 1))
    (400, (0, 1))
    (403, (1, 0, True, u'PHP'))
    (403, (0, 1))



```python
# step2
data2 = data1.reduceByKey(lambda x, y: (
    x[0] + y[0],
    x[1] + y[1],
    x[2],
    x[3]
))
for row in data2.collect():
    print(row)
```

    (100, (1, 3, True, u'Python'))
    (104, (1, 2, False, u'Python'))
    (300, (1, 0, False, u'Java'))
    (206, (1, 2, False, u'C#'))
    (400, (1, 2, True, u'PHP'))
    (200, (1, 5, False, u'C#'))
    (305, (1, 1, True, u'Java'))
    (307, (1, 2, True, u'Java'))
    (403, (1, 1, True, u'PHP'))
    (301, (1, 3, True, u'Java'))



```python
# step3
data3 = data2.map(lambda x: ((x[1][3], x[1][2]), x[1][1]))

for row in data3.collect():
    print(row)
```

    ((u'Python', True), 3)
    ((u'Python', False), 2)
    ((u'Java', False), 0)
    ((u'C#', False), 2)
    ((u'PHP', True), 2)
    ((u'C#', False), 5)
    ((u'Java', True), 1)
    ((u'Java', True), 2)
    ((u'PHP', True), 1)
    ((u'Java', True), 3)



```python
# step4
createCombiner = lambda x: (x, 1)
mergeValue = lambda accum, x: (accum[0] + x, accum[1] + 1)
mergeCombiners = lambda accum1, accum2: (accum1[0] + accum2[0], accum1[1] + accum2[1])

data4 = data3.combineByKey(createCombiner, mergeValue, mergeCombiners)

for row in data4.collect():
    print(row)
```

    ((u'C#', False), (7, 2))
    ((u'Python', False), (2, 1))
    ((u'PHP', True), (3, 2))
    ((u'Java', False), (0, 1))
    ((u'Python', True), (3, 1))
    ((u'Java', True), (6, 3))



```python
# step5
data5 = data4.map(lambda x: (str(x[0][0]), 
                             (
                                 (x[1][1] if x[0][1] else 0),
                                 (float(x[1][0])/x[1][1] if x[0][1] else None),
                                 (0 if x[0][1] else x[1][1]),
                                 (None if x[0][1] else float(x[1][0])/x[1][1])
                             )))

for row in data5.collect():
    print(row)
```

    ('C#', (0, None, 2, 3.5))
    ('Python', (0, None, 1, 2.0))
    ('PHP', (2, 1.5, 0, None))
    ('Java', (0, None, 1, 0.0))
    ('Python', (1, 3.0, 0, None))
    ('Java', (3, 2.0, 0, None))



```python
# step6
data6 = data5.reduceByKey(lambda x, y: (
    (0 if x[0] == None else x[0]) + (0 if y[0] == None else y[0]),
    (0 if x[1] == None else x[1]) + (0 if y[1] == None else y[1]),
    (0 if x[2] == None else x[2]) + (0 if y[2] == None else y[2]),
    (0 if x[3] == None else x[3]) + (0 if y[3] == None else y[3])
))

for row in data6.collect():
    print(row)
```

    ('C#', (0, None, 2, 3.5))
    ('Python', (1, 3.0, 1, 2.0))
    ('Java', (3, 2.0, 1, 0.0))
    ('PHP', (2, 1.5, 0, None))



```python
# step7
res_data = data6.sortBy(lambda x: x[1], ascending=False)

for row in res_data.collect():
    print(row)
```

    ('Java', (3, 2.0, 1, 0.0))
    ('PHP', (2, 1.5, 0, None))
    ('Python', (1, 3.0, 1, 2.0))
    ('C#', (0, None, 2, 3.5))

