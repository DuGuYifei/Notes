# alias

```python
avg_speed = (flights.distance/(flights.air_time/60)).alias("avg_speed")
```

返回一个新的df，包含一个列名为avg_speed的列