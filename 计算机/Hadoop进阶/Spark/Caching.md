# Caching

## What is caching
* keeping data in memory
* Spark tends to unload memory aggressively
  
## Eviction Policy
* LRU (least recently used)
* Eviction happens independently on each worker
* Depends on memory available to each worker

## Caching a dataframe
* `df.cache()` 
  * Dataset = `df.persist(pyspark.StorageLevel.MEMORY_AND_DISK)`
  * RDD = `df.persist(StorageLevel.MEMORY_ONLY)`
* `df.unpersist()`
* `df.is_cached`
* `df.storageLevel` => output e.g.: `StorageLevel(True, True, False, True, 1)` =>
  * useDisk
  * useMemory
  * useOffHeap
  * deserialized
  * replication
  * useDisk specifies whether to move some or all of the dataframe to disk if it needed to free up memory. 
  * useMemory specifies whether to keep the data in memory. 
  * useOffHeap tells Spark to use off-heap storage instead of on-heap memory. (堆内, 堆外)
    * The on-heap store refers to objects in an in-memory data structure that is fast to access. 
    * The off-heap store is also in memory, but is slightly slower than the on-heap store. 
    * However, off-heap storage is still faster than disk. 
    * Even though the best performance is obtained when operating solely in on-heap memory, Spark also makes it possible to use off-heap storage for certain operations. 
    * The downside is that the user has to manually deal with managing the allocated memory.
  * deserialized True is faster but uses more memory. 
    * Serialized data is more space-efficient but slower to read. 
    * This option only applies to in-memory storage.
    * Disk cache is always serialized. 
  * replication is used to tell Spark to replicate data on multiple nodes. This allows faster fault recovery when a node fails.

## caching a table
```python
df.createOrReplaceTempView('df')
spark.catalog.isCached(tableName='df') # False
spark.catalog.cacheTable(tableName='df')
spark.catalog.isCached(tableName='df') # True

spark.catalog.uncacheTable(tableName='df')
spark.catalog.isCached(tableName='df') # False

spark.catalog.clearCache()
```

## Tips
* Caching is lazy (只有操作了cache才会cache)
* Only cache if more than one operation is to be performed
* Unpersist when you no longer need the object
* Cacge selectively