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
11. [变量\_@\_Declare\_SET](#变量__declare_set)
12. [DELETE](#delete)
	 1. [删除所有](#删除所有)
13. [Union](#union)
	 1. [Union ALL 和 Union](#union-all-和-union)
14. [Join](#join)
	 1. [Natural join](#natural-join)
	 2. [Full outer join](#full-outer-join)
	 3. [left join](#left-join)
15. [UPDATE](#update)
16. [with](#with)
17. [aggregation](#aggregation)
	 1. [count](#count)
		 1. [group by 问题](#group-by-问题)


## definition

***SQL = DDL + DML + DCL*** Structured Query Language

**DDL:** Data Definition Language\
**DML:** Data Manipulation Language\
**DCL:** Data Control Language

| component | whole name                 | key word                    |
| :-------: | -------------------------- | --------------------------- |
|    DDL    | Data Definition Language   | Create,Alter,Drop           |
|    DML    | Data Manipulation Language | Select,Insert,Update,Delete |
|    DCL    | Data Control Language      | Grant,Revoke                |

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
`ASC` 升序，ascending

`DESC` 降序，descending
```sql
order by 表字段 desc
```

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

## DELETE
### 删除所有
```sql
DELETE FROM TABLE_NAME
DELETE * FROM TABLE_NAME
```
第二个不一定在所有数据库可用

## Union
### Union ALL 和 Union
union all 不管重复行

union 要去重，但是是先合并再去重，效率低，好的操作是先去重再union all

## Join

### Natural join
每一位相等

### Full outer join
两边都保留，补null

### left join
左边保留行，右边Null表


## UPDATE

```sql
UPDATE table_name
SET column1 = value1, column2 = value2, ...
WHERE condition;
```


## with
```sql
With 
	Subtable1 as (select 1...), //as和select中的括号都不能省略
	Subtable2 as (select 2...), //后面的没有with，逗号分割，同一个主查询同级别地方，with子查询只能定义一次
	…
	Subtablen as (select n...) //与下面的实际查询之间没有逗号
Select ….

--hive 注意 from t
with 
    t as (
        select date_id
        from date_par
        where month_no > 6
    )
select year, count(year) as account_num
from signing_in_ext, t
where 
    year = 2021 and
    signing_in_ext.sign_in_date_id = t.date_id
group by year
UNION ALL
select year, count(year) as user_cnt
from signing_in_ext, t
where 
    year = 2020 and 
    signing_in_ext.sign_in_date_id = t.date_id
GROUP BY year;
```


## aggregation

### count
#### group by 问题
当count有其他列时，需要group by
