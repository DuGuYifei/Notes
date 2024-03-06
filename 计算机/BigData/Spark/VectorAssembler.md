# VectorAssembler

Pipeline的最后一步是将包含特征的所有列合并为一个单独的列。在建模之前必须这样做，因为每个Spark建模程序都期望数据以这种形式出现。您可以通过将来自列的每个值存储为向量中的一个条目来完成此操作。然后，从模型的角度来看，每个观测值都是一个向量，其中包含有关它的所有信息以及告诉建模者该观测值对应的值的标签。

因此，pyspark.ml.feature子模块包含一个称为VectorAssembler的类。此转换器接受您指定的所有列，并将它们组合成一个新的向量列。

VectorAssembler不仅可以将列简单叠加，还可以将它们转换成更高维度的向量。具体来说，它可以接受包含不同数据类型的列，如数值型、布尔型和分类型等，然后将它们组合成一个向量类型的列，这个向量的维度就是所有输入列中数据的总数。当所有的输入列都是数值型时，这个向量就是一个稠密向量；当存在分类型的输入列时，这个向量就是一个稀疏向量，其中每一个元素都对应了某个分类值在输入数据中出现的次数。这个向量列就是最终可以输入到机器学习算法中的特征向量。

```python
# Make a VectorAssembler
vec_assembler = VectorAssembler(inputCols=["month", "air_time", "carrier_fact", "dest_fact", "plane_age"], outputCol="features")
```