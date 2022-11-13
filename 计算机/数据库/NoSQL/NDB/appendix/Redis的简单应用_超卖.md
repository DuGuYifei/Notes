# Redis的简单应用 - 超卖


## Introduction
###	Scenario – Lighting Deal
11.11 (11th of November) of each year is E-commerce shopping carnival in China. In each electronic commerce platform, there will be many Lighting Deal activities. For the huge amount of population in China, we need solve the high concurrency when many people snap up items at the same time. Therefore, we can do like this:
1. Before Lighting Deal, synchronize product inventory from database to Redis.
2. During Lighting Deal, we decrease inventory and publish the data of orders by Pub/Sub.
3. The subscriber of order’s data handle the order.

###	Features Analysis in simple case:
1. Data type: For the key-value pair of goods, we only need String. But for users, we can use set which can help us to make sure that one user can only attempt once in the Lighting Deal of each type of goods.
2. Sub/Pub: Publish the data of order. The subscriber handle with the data. 
3. Analysis of Transaction: Before this point, the high concurrency of order at the same time, so it may cause the problem of over sell. In order to solve this problem, we can use WATCH to monitor inventory. Without WATCH, transaction in Redis doesn’t guaranteed atomicity. WATCH will provide CAS (compare and swap). If at least one of the monitored keys is modified before the EXEC command is executed, the entire transaction will be rolled back without performing any actions, thereby ensuring atomicity. However, it may cause another problem – remaining inventory if use transaction here: Although there are many concurrent requests, due to the optimistic locks (CAS), a large number of simultaneous concurrent requests fail, and the inventory is still left in the end.
4. Lua script: Since Redis 2.6, it embeds with support of Lua environment, so we can use Lua script to solve the problem above and keep the atomicity at the same time. Also, it can reduce the frequency of linking to Redis.
5. Stream: Stream can also be used in such activity. Because in real life, sometimes only the users who have the coupon which can be used in the Lighting Deal can attend to snap up. In such case, we can use Stream to realize purpose asynchronously.

##	Operations (simple version)
###	Preparation
Add inventory amount into Redis.
-	ld – Lighting Deal, the name of the activity this time
-	product_id – the id of product .
-	qt – quantity
-	amount – amount of inventory
```bash
SET ld:product_id:qt amount
SET ld:1111:qt 1000
```
Sometimes we also need check the remaining amount:
1.	nil -> hasn’t started
2.	0 -> finished
```bash
GET ld:product_id:qt
GET ld:1111:qt
```

###	Data
When a user snapped up an item, insert user’s information and decrease the amount of inventory.
```bash
DECR ld:product_id:qt
DECR ld:1111:qt
SADD ld:product_id:user user_id
SADD ld:1111:user 9527
```

If someone cancel the order:
```bash
INCR ld:product_id:qt
INCR ld:1111:qt
SREM ld:product_id:user user_id
SREM ld:1111:user 9527
```

Check whether we have had this user in set.
```bash
SISMEMBER ld:product_id:user user_id
SISMEMBER ld:1111:user 9527
```
Other operations in set maybe used here:
```bash
SUNIONSTORE sumset product1_set product2_set (…)
SCARD ld:product_id:user
SMEMBERS ld:product_id:user
```


###	Sub/Pub
Subscribe a channel which will publish the order data to subscriber server which will be used to handle data of order.
a)	In subscriber client
```bash
SUBSCRIBE publisher
```
b)	In publish client
```bash
PUBLISH publisher “order_id user_id”
PUBLISH publisher “xyz1111 9527”
```


###	WHATCH
Use WATCH (optimistic locks) of Redis transaction to solve over sell. But will be replaced in next point (1.5).
```bash
WATCH ld:product_id:qt
MULTI
DECR ld:product_id:q
SADD ld:product_id:user user_id
EXEC
```
But it will lead many people fail to operate.

###	Final version to solve problems above (Lua + Java)
script.lua: 
-	Check user exists in the set by sismember
-	Check remaining inventory to solve over sell.
-	Each time execute the whole script in one command which will not let others fail when this user fail. Solve the problem of optimistic lock.

```lua
local userid=KEYS[1]; 
local product_id=KEYS[2];
local qtKey="ld:"..product_id..":qt";
local usersKey="ld:"..product_id..":user'; 
local userExists=redis.call("sismember", usersKey, user_id);
if tonumber(userExists)==1 then 
    return 2;
end
local num= redis.call("get" ,qtKey);
if tonumber(num)<=0 then 
    return 0; 
else 
    redis.call("decr", qtKey);
    redis.call("sadd", usersKey,user_id);
end
```

Depending on the different return value in lua script, we can handle the result in back-end.
```java
// Load script
String script = jedis.scriptLoad(scriptAbove);
// Execute script
Object result= jedis.evalsha(script, 2, uid, prodid);
// Handle return value
String returnValue=String.valueOf(result);
if ("0".equals( returnValue ) ) {
	System.err.println("Sold out");
}else if("1".equals( returnValue )) {
	System.out.println("Snap up sucessfully");
}else if("2".equals( returnValue )) {
	System.err.println("This user has bought one");
}else{
	System.err.println("Exception");
}
```
###	Stream
Use Stream of Redis to store coupon information and order_id(ld:order:coupon_id).
The code below respectively are create the consumer group, add new order information and send message to the stream when user snap up successfully.
```bash
XGROUP CREATE streamKey groupname 0 MKSTREAM
XGROUP CREATE stream.orders consumer-group1 0 MKSTREAM
--------------------------------------------------------
SADD  ld:order:coupon_id  user_id
--------------------------------------------------------
XADD  key ID field value
XADD  stream.orders  user_id  coupon_id  ld:order:coupon_id 
```
