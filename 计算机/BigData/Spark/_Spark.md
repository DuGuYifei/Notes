# Spark

## 结构
![](2023-03-31-17-17-22.png)

## 系统学习
注意教程里案例的spark变量其实SparkSession的实例。系统学习2里有提过。
1. [pyspark基础](pyspark基础.md)
2. [MovingWindowAnalysis](MovingWindowAnalysis.md)
3. [Caching](Caching.md)
4. [SparkUI](SparkUI.md)
5. [Spark_catalog_operations](Spark_catalog_operations.md)
6. [Logging](Logging.md)
7. [QueryPlans](QueryPlans.md)
8. [ExtractTransformSelect](ExtractTransformSelect.md)
9. [Creating feature data for classification](CreatingFeatureDataForClassification.md)
10. [Text classification](TextClassification.md)

## 系统学习2

### Getting to know PySpark
1. [SparkContext连接cluster](连接cluster.md)
2. [DataFrame—pandas-structure](DataFrame.md)
3. [read其他结构的数据](read其他结构的数据.md)

### Manipulation data
1. [创建列](创建列.md)
2. [filter数据](filter数据.md)
3. [select](select.md)
4. [groupBy和agg](groupBy和agg.md)
5. [join](join.md)

### Machine Learning Pipelines
1. [Transformers and Estimators](Transformers_Estimators.md)
2. [数据类型_cast](数据类型_cast.md)
3. [string的处理_one-hot-vector](string的处理_one-hot-vector.md)
4. [VectorAssembler](VectorAssembler.md)
5. [Pipeline](Pipeline.md)
6. [使用pipeline来Transform数据](使用pipeline来Transform数据.md)

### model tuning and selection
1. [Logistic Regression](Spark_LogisticRegression.md)
2. [Cross validation](CrossValidation.md)
3. [Evauator](Evaluator.md)
4. [grid](grid.md)
5. [fit](fit.md)
6. [预测_transform和评估模型_evaluate](预测_transform和评估模型_evaluate.md)

## 系统学习3
1. [训练和预测](过时的pyspark_mllib.md)
2. [classification](classification.md)
3. [cluster](kmeans.md)


## 积累
1. [%在query中的使用](%在query中的使用.md)
2. [ListTables](ListTables.md)
3. [registerTempTable](registerTempTable.md)
4. [first](first.md)
5. [array_contains](array_contains.md)
6. [withColoumn](withColoumn.md)
7. [drop](drop.md)
8. [where函数的参数](where函数的参数.md)
9. [lit](lit.md)
10. [toPandas()](toPandas.md)
11. [sparksession.table()](sparksession_table.md)
12. [alias](alias.md)
13. [withColumnRenamed](withColumnRenamed.md)
14. [udf](udf.md)
15. [randomwSplit](randomwSplit.md)
16. [sc.parallelize](parallelize.md)
17. [sc.textFile](sc_textFile.md)
18. [getNumPartitions](getNumPartitions.md)
19. [map](map.md)
20. [flatmap](flatmap.md)
21. [collect](collect.md)
22. [take](take.md)
23. [reduceByKey](reduceByKey.md)
24. [sortByKey](sortByKey.md)
25. [countByKey_items](countByKey_items.md)
26. [createDataFrame](createDataFrame.md)
27. [dropDuplicates](dropDuplicates.md)
28. [printSchema](printSchema.md)
29. [describe基础统计](describe基础统计.md)
30. [过时的pyspark.mllib](过时的pyspark_mllib.md)
31. [Classification](Classification.md)
32. [HashingTF](HashingTF.md)
33. [kmeans](kmeans.md)