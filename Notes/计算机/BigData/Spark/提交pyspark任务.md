# 提交pyspark任务

## 1. 使用Python Shell

1. 在SSH控制台中输入以下命令启动Python Spark Shell：

```shell
pyspark
```

2. 当Python Spark Shell启动后（可能需要一些时间并显示大量信息），请注意Spark上下文会自动导入为sc。

3. 输入以下命令来实现一个简单的单词计数应用程序：
```python
txt = sc.textFile("/user/adampap/tutorial")
wordCounts = txt.flatMap(lambda line: line.split(" ")).map(lambda word: (word, 1)).reduceByKey(lambda a, b: a + b)
wordCounts.take(30)
```

## 2. 使用 spark-submit 脚本在集群上启动应用程序

1. 使用以下命令运行应用程序，并等待其完成：
```shell
spark-submit ./wordcount.py /user/adampap/tutorial /user/adampap/out
```

2. 应用程序的输出将在HDFS上：
```shell
hdfs dfs -ls /user/adampap/out
```

## 3. 使用Jupyter Notebook

```shell
jupyter notebook --no-browser --port <numer portu>
```

```shell
jupyter notebook
```

会自动打开浏览器的

上传并运行tutorial.ipynb文件。

