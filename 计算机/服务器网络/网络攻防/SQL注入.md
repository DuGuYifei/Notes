# SQL注入

[bilibili:SQL注入攻击原理，方法和类型](https://www.bilibili.com/video/BV1ZR4y1Y745)

## 报错与注释
将用户名带个单引号，注释号等
```SQL
SELECT * FROM allusers
WHERE username='eggpain' OR 1=1 --' AND password='mima'
```

## UNION
```SQL
SELECT * FROM products
WHERE name='egg'
UNION SELECT NULL, username, password FROM allusers
--'
```

## 盲注
### 布尔
```sql
SELECT cookieId FROM allusers
WHERE cookieId='1jiAn3lIan'
AND SUBSTRING((SELECT password FROM users WHERW user='admin'), 1, 1)='m'
--'
```

### 时间延迟
`sleep(10)`
因为可能界面不返回查询结果，但是我们可以用时间延迟的方式确认是否查询正确等。

## 外通道
比如向MySQL系统`LOAD_FILE()`函数，提供域名出发DNS查询，即查询ip地址。

把要查询的密码和域名拼接，可以直接发给黑客的服务器。


## 防止
[## Prepared statement](../../数据库/SQL/SQLKnowledgeAccumulation.md)