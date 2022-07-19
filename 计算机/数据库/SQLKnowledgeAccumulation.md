# 知识积累 SQL

1. [definition](#definition)
2. [Escape通配符的转义符](#escape通配符的转义符)
3. [顺序排列](#顺序排列)
4. [DECIMAL(a,b)](#decimalab)
5. [IS NULL 和 = NULL](#is-null-和--null)
6. [ORDER BY 1](#order-by-1)
7. [dbo](#dbo)
8. [CASE WHEN](#case-when)
9. [SIGN](#sign)
10. [WHILE](#while)
11. [变量_@_Declare_SET](#变量__declare_set)
12. [Datetime](#datetime)
   1. [datediff](#datediff)
   2. [datepart](#datepart)
   3. [format](#format)

## definition

***SQL = DDL + DML + DCL*** Structured Query Language

**DDL:** Data Definition Language\
**DML:** Data Manipulation Language\
**DCL:** Data Control Language

component|whole name|key word
:-:|-|-
DDL|Data Definition Language|Create,Alter,Drop
DML|Data Manipulation Language|Select,Insert,Update,Delete
DCL|Data Control Language|Grant,Revoke

Tip:
Select is also **DQL：Data Query Language**

## Escape通配符的转义符
定义转义符
```sql
LIKE "J$?%%" ESCAPE "?"
-- denotes the string that 
-- begins with the letter “J” 
-- followed by one dollar sign 
-- followed by one percent sign 
-- followed by any string of 0 or more characters.
```

## 顺序排列
`ASC` 升序，ascending\
`DESC` 降序，descending

## DECIMAL(a,b)
其中`a`是指一共多少位，包括小数点后的`b`位, 后面的必须大于等于前面的数字

## IS NULL 和 = NULL
`= NULL` can't find the result\
`IS NULL` can

## ORDER BY 1
根据第一列排序

## dbo
dbo是每个数据库的默认用户，具有所有者权限，全称：datebaseOwner ，即DbOwner 。

在数据库中，新建对象时，默认对象的所有者为当前登录的账号。

如果通过用dbo作为所有者来定义对象，能够使数据库中的任何用户引用而不必提供所有者名称。

比如：你以User1登录进去并建表Table，而未指定dbo， 当用户User2登进去想访问Table时就得知道这个Table是你User1建立的，要写上User1.Table，如果他不知道是你建的，则访问会有问题。 如果你建表时把所有者指给了dbo，则别的用户进来时写上Dbo.Table就行了，不必知道User1。 

不光表是如此，视图等数据库对象建立时也要如此才算是好。 所以在创建对象时，指定所有者为dbo，任何一个用户都可以引用。

建表、存储过程、视图等数据库对象时，其对应的所有者是创建它的用户。则除了该用户其他登录用户要引用这些东东时，都要加上前缀，很是麻烦。而且，程序因此易出错，你查来查去问题确出在这，浪费你时间。


## CASE WHEN
## SIGN
```sql
SELECT Route.ID_R, Departure_Hub_EndName, CASE SIGN(Amount_Seat - 420) WHEN 1 THEN CASE SIGN(Amount_Seat - 480) WHEN - 1 THEN 'medium' ELSE 'large' END ELSE 'small' END AS cathegory_amount, B.cathegory_dist, ID_Train, CASE format(DepartureTime,'mm') WHEN '00' THEN 0 ELSE 1 END AS isdelay, DepartureTime
FROM Route,(SELECT ID_R, CASE SIGN(Route_Dist - 50) WHEN 1 THEN CASE SIGN(Route_Dist - 80) WHEN 1 THEN 'long' ELSE 'medium' END ELSE 'short' END AS cathegory_dist
FROM (SELECT ID_R, MAX(Distance) AS Route_Dist
    FROM SubsetOfRoute
    GROUP BY ID_R) AS A) AS B
WHERE Route.ID_R = B.ID_R
ORDER BY ID_R
```

## WHILE
## 变量_@_Declare_SET
```cpp
DECLARE @date INT
SET @date = 20220120
WHILE @date <= 20220131
BEGIN
	insert into [Date] values(cast(@date as char), 2022, 1, @date - 20220100,'January')
	SET @date = @date + 1
END
SET @date = 20220201
WHILE @date <= 20220228
BEGIN
	insert into [Date] values(cast(@date as char), 2022, 1, @date - 20220100,'February')
	SET @date = @date + 1
END
SET @date = 20220301
WHILE @date <= 20220320
BEGIN
	insert into [Date] values(cast(@date as char), 2022, 1, @date - 20220100,'March')
	SET @date = @date + 1
END
```

## Datetime
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
