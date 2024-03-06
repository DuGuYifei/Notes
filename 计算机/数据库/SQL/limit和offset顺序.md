# limit和offset顺序

## 顺序

limit在前，减少offset内存选择大量再抛弃

## 例子

```sql
select * from table limit 1000 offset 1000000;
```