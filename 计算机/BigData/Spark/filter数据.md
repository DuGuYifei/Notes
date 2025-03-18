# filter数据

```python
flights.filter("air_time > 120").show()
flights.filter(flights.air_time > 120).show()
```