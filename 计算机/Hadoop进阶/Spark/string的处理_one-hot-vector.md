# string的处理_one-hot-vector

## 结构
```
string --StringIndexer--> index --OneHotEncoder--> one-hot vector
             / \                   / \
			/   \                 /   \
		   /     \               /     \
		  /       \      一样的，Estimator + Transformer
		 /         \
Estimator(string) -> Transformer(string) -> index i.e. df
```

## 案例
```python
# Create a StringIndexer
carr_indexer = StringIndexer(inputCol="carrier", outputCol="carrier_index")

# Create a OneHotEncoder
carr_encoder = OneHotEncoder(inputCol="carrier_index", outputCol="carrier_fact")
########################################
# Create a StringIndexer
dest_indexer = StringIndexer(inputCol="dest", outputCol="dest_index")

# Create a OneHotEncoder
dest_encoder = OneHotEncoder(inputCol="dest_index", outputCol="dest_fact")
```
