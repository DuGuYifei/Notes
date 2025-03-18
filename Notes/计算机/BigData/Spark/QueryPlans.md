# QueryPlans

## Explain
provides detailed plan information about the query without running

instead of the usual table of data, it returns a query execution plan, also called a query plan
```sql
EXPLAIN SELECT * FROM table;
```

```PYTHON
df = spark.read.load('/temp/df.parquet')
df.registerTempTable('df')
spark.sql('EXPLAIN SELECT * FROM df').first()
``` 

![](_attachments/old/2023-03-24-04-00-43.png)

```PYTHON
df.explain()
```
![](_attachments/old/2023-03-24-04-23-26.png)

```PYTHON
spark.sql("SELECT * from df").explain()
```

![](_attachments/old/2023-03-24-04-23-59.png)

```PYTHON
df.cache()
df.explain()
```
![](_attachments/old/2023-03-24-04-24-40.png)
