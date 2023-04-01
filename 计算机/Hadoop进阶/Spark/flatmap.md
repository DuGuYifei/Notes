# flatmap

flatMap 操作对于 RDD 中的每个元素都应用一个返回迭代器的函数，返回一个新的 RDD，新 RDD 中的元素是原 RDD 中的元素经过该函数返回的迭代器中包含的所有元素。

```python
words = ["Hello Spark", "I love Spark", "Spark is great"]

words_mapped = words.map(lambda x: x.split(" "))
# [["Hello", "Spark"], ["I", "love", "Spark"], ["Spark", "is", "great"]]

words_flatmapped = words.flatMap(lambda x: x.split(" "))
["Hello", "Spark", "I", "love", "Spark", "Spark", "is", "great"]
```