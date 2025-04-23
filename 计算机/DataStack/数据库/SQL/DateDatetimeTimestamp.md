# Date Datetime Timestamp

1. [Date Datetime Timestamp](#date-datetime-timestamp-1)
   1. [DATETIME和TIMESTAMP 区别](#datetime和timestamp-区别)
2. [Datetime函数](#datetime函数)
   1. [datediff](#datediff)
   2. [datepart](#datepart)
   3. [format](#format)


## Date Datetime Timestamp

| Type      | Range                                                 | Remark                                       |
| --------- | ----------------------------------------------------- | -------------------------------------------- |
| DATE      | ‘1000-01-01’ to ‘9999-12-31’                          | 只有日期部分，没有时间部分                   |
| DATETIME  | ‘1000-01-01 00:00:00’ to ‘9999-12-31 23:59:59’        | 时间格式为 YYYY-MM-DD hh:mm:ss，默认精确到秒 |
| TIMESTAMP | ‘1970-01-01 00:00:01’ UTC to '2038-01-19 03:14:07’UTC | 默认精确到秒                                 |

### DATETIME和TIMESTAMP 区别
1. 时间范围不一样，TIMESTAMP 要小很多 ，且最大范围为2038-01-19 03:14:07.999999，到期也不远了。
2. datetime与时区无关、timestamp与时区有关
   1. 对于TIMESTAMP，它把客户端插入的时间从当前时区转化为UTC（世界标准时间）进行存储。查询时，将其又转化为客户端当前时区进行返回。
   2. 而对于DATETIME，不做任何改变，基本上是原样输入和输出。
3. datetime和timestamp都可以当作时间戳使用
4. datetime和timestamp都可以设置默认值，并且在其他列值更新时更新为当前时间，DEFAULT CURRENT_TIMESTAMP和ON UPDATE CURRENT_TIMESTAMP

## Datetime函数
### datediff
### datepart
```sql
select Route.ID_R,datediff(day,'20220120',DepartureTime) as ID_Date, datepart(hh,DepartureTime)* 60 + datepart(mi,DepartureTime) + 1 as ID_Time, ID_Train,70 as Distance,Amount_Seat,op from Route,
(
	select b.ID_R, cast((cast(sd as float)/ss) as decimal(2,2)) as op from
	(
		select ID_R, sum(dis) as sd from 
		(
			select ID_R, count(ID_Ticket) * ABS(Ordinal_Start - Ordinal_End)*10 as dis from Ticket,SubsetOfRoute
			where Ticket.ID_SR = SubsetOfRoute.ID_SR
			group by ID_R, Ordinal_Start,Ordinal_End
		)a
		group by ID_R
	)b,
	(
		select ID_R, Amount_Seat * 70 as ss from Route
	)c
	where b.ID_R = c.ID_R
)d
where d.ID_R = Route.ID_R
order by ID_R
```

### format
```sql
SELECT Route.ID_R, Departure_Hub_EndName, CASE SIGN(Amount_Seat - 420) WHEN 1 THEN CASE SIGN(Amount_Seat - 480) WHEN - 1 THEN 'medium' ELSE 'large' END ELSE 'small' END AS cathegory_amount, B.cathegory_dist, ID_Train, CASE format(DepartureTime,'mm') WHEN '00' THEN 0 ELSE 1 END AS isdelay, DepartureTime
FROM Route,(SELECT ID_R, CASE SIGN(Route_Dist - 50) WHEN 1 THEN CASE SIGN(Route_Dist - 80) WHEN 1 THEN 'long' ELSE 'medium' END ELSE 'short' END AS cathegory_dist
FROM (SELECT ID_R, MAX(Distance) AS Route_Dist
    FROM SubsetOfRoute
    GROUP BY ID_R) AS A) AS B
WHERE Route.ID_R = B.ID_R
ORDER BY ID_R
```