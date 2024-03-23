# Pokemoney

## 项目介绍
Pokemoney = poke + money = pocket + money = 宝可梦 :)

可离线加联网并且多设备登录的记账软件，一个设备可切换账户，创建多个资金源和不同账本以及不同目录。

后台支持大量用户并创建连接大数据平台，以及创建自己的数据仓库。

## 项目图片

### 技术栈
1. APP：Flutter + sqlite
2. 后端：
   1. (deprecated) SpringCloud + Eureka + SpringCloudGateway
   2. Dubbo
   3. Nacos
   4. Higress
   5. Redis cluster
   6. MySQL cluster + Shardingsphere
      1. Sharding
      2. Read/Write Splitting
   7. Zookeeper (分布式锁)
   8. Leaf (美团分布式ID基于Snowflake)
   9. 大数据平台
      1.  Kafka
      2.  Hadoop
      3.  HBase
      4.  Hive
      5.  Spark
      6.  Nifi
      7.  Doris
   10. 部署：Docker
   11. 语言：java

### 难点
1. 有限时间内迅速上手并使用每个技术
2. docker部署自己的大数据平台
3. 项目可离线加联网并且多设备登录的同步方式
4. 其他常规：分布式锁，异步，kafka消息队列

### 手机端 flutter

<div style="text-align:center;">
    <img src="./attachments/Pokemoney/login_page.png" width="30%" style="display:inline-block;">
    <img src="./attachments/Pokemoney/Ledger_books.png" width="30%" style="display:inline-block;">
    <img src="./attachments/Pokemoney/The app navigation.png" width="30%" style="display:inline-block;">
    <img src="./attachments/Pokemoney/main page 1.png" width="30%" style="display:inline-block;">
    <img src="./attachments/Pokemoney/Funds_main.png" width="30%" style="display:inline-block;">
    <img src="./attachments/Pokemoney/Funds_MoreDetails.png" width="30%" style="display:inline-block;">
</div>

### 后端架构
1. v1: SpringClould + Eureka + SpringCloudGateway
![alt text](attachments/Pokemoney/Frame_1.png)
2. v2: Dubbo + Nacos + SpringCloudGateway
![alt text](attachments/Pokemoney/Frame_2.png) 
3. v3: Dubbo + Nacos + Higress
![alt text](attachments/Pokemoney/Frame_6.png)

### 大数据架构
1. v1
![alt text](attachments/Pokemoney/Frame_3.png)
2. v2
![alt text](attachments/Pokemoney/Frame_4.png) 

## 代码链接
未开源：
[Pokemoney记账软件](https://github.com/DuGuYifei/Pokemoney)