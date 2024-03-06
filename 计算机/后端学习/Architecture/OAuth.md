# OAuth

## OAuth 2.0

就是用来让用户能够使用第三方账户登录自己服务的协议。

## 举个数据库例子方便理解
```
 id | username | password | weibo_id | weibo_access_token | weibo_expires | name等其他字段
----+----------+----------+----------+--------------------+---------------+----------------
 A1 | bob      | a1b23f2c | W-012345 | xxxxxxxxxx         | 604800        | ...
 A2 | adam     | c0932f32 | W-234567 | xxxxxxxxxx         | 604800        | ...
 ```

 这里用了微博的OAuth，当然这不是一个好的数据库设计，我们可以：
 [数据库设计：用户登录系统数据库表设计_djaaa123456的博客-CSDN博客](https://blog.csdn.net/djaaa123456/article/details/101514436)