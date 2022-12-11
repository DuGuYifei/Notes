# Hive_DataWarehouse_Example

## design
comment: 
* external table xxxx_ext
* xxxx_parquet _orc
* parquet and orc need select from an external table XXX_csv
* `profile STRUCT <>` employee user
* `rate STRUCT <helpful: int, experience: int>`
* `category_discount UNIONTYPE<string, int>`
* not drop all external table, said as these table's data are created by ERP software.

1. time: 
   1. parquet
2. Date:
   1. parquet
3. user: 
   1. partition: age_category
   2. table 
   3. parquet
   4. bucket: user_id 5
4. employee 
   1. textfile (because in the design, it read from excel)
   2. external table
5. promo_code:
   1. external table
   2. textfile
   3. category_discount -> ADD discount number
   4. no_promo_code -> is_used -> boolean
6. junk_chat:
   1. textfile
   2. modify into boolean value
7. junk_booking:
   1. textfile
   2. modify into boolean value
8. chatting: 
   * why not partitioned by date-year? because we would likely to analyse employee's personal performance more in this table)
   * Why dynamic, Because its origin file not divide into different files by employee, it divide by year in real life(but here, we have already generate data into only one file, but doesn't matter, because we are dynamic partition)
   1. ORC
   2. partition: employee id
   3. bucket: chat_date_id 5
9. booking: 
   * why not partitioned by date? because our query use junk_booking_id more
   * Why dynamic? Because its origin file not divide into different files by junk_booking_id, it divide by year in real life(but here, we have already generate data into only one file, but doesn't matter, because we are dynamic partition)
   1. ORC
   2. partition: junk_booking_id
   3. bucket: booking_date_id 10
10. signing_in:
    * why static? because it's already divide into different year.
   1. ORC
   2. partition: static -> year
   3. external table
   4. static partitioned by `ALTER TABLE testdb.table1 ADD PARTITION (dept='dept1') LOCATION '/path/to/dataFile/dept1';`
   5. year divide:
      1. 2015:1-365
      2. 2016:366-731
      3. 2017:732-1096
      4. 2018:1097-1461
      5. 2019:1462-1826
      6. 2020:1827-2192
      7. 2021:2193-2557


## 前戏
```bash
ssh atndb13@153.19.52.196
beeline
# beeline里
!connect jdbc:hive2://
# 用户名
atndb13
#密码
AT-NDB
# 数据库
use liu_osama;
```

## 上传数据
```bash

```

## 创建表格-加载数据
### 创建表格
```sql
create external table booking_csv(
    transaction_no int,
    user_id int,
    booking_date_id int,
    junk_booking_id int
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
location 'hdfs:///user/liu_osama/database/booking'
TBLPROPERTIES ("skip.header.line.count"="1");

create table booking_orc(
    transaction_no int,
    user_id int,
    booking_date_id int
)
PARTITIONED BY (junk_booking_id INT)
CLUSTERED BY (booking_date_id) INTO 10 buckets
STORED AS ORC;

--------------------------------------------

create external table chatting_csv(
    duration int,
    helpful int,
    experience int,
    response_time int,
    user_id int,
    starting_time_id int,
    junk_chat_id int,
    employee_id int,
    chat_date_id int,
    ending_time_id int
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
location 'hdfs:///user/liu_osama/database/chatting'
TBLPROPERTIES ("skip.header.line.count"="1");

create table chatting_orc(
    user_id int,
    rate STRUCT<helpful: int, experience: int>,
    duration int,
    response_time int,
    junk_chat_id int,
    chat_date_id int,
    starting_time_id int,
    ending_time_id int
)
PARTITIONED BY (employee_id INT)
CLUSTERED BY (chat_date_id) INTO 5 buckets
STORED AS ORC;

-----------------------------------------

create external table date_csv(
    date_id int,
    dt date,
    year int,
    month string,
    month_no int,
    day_of_week string,
    day_of_week_no int
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
location 'hdfs:///user/liu_osama/database/date'
TBLPROPERTIES ("skip.header.line.count"="1");

create table date_par(
    date_id int,
    dt date,
    year int,
    month string,
    month_no int,
    day_of_week string,
    day_of_week_no int
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
STORED AS PARQUET;

------------------------------------------

-- External table
create external table employee_ext(
    employee_id int,
    profile struct<name_and_surname:string,sex:char(1),pesel_bk:string>,
    age_category string,
    is_current boolean
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
COLLECTION ITEMS TERMINATED BY '|'
location 'hdfs:///user/liu_osama/database/employee'
TBLPROPERTIES ("skip.header.line.count"="1");

-------------------------------------------

-- External table
create external table junk_booking_ext(
    Junk_booking_ID int,
    app_or_web char(3),
    is_successful boolean,
    is_employee_needed boolean
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
location 'hdfs:///user/liu_osama/database/junk_booking'
TBLPROPERTIES ("skip.header.line.count"="1");

-------------------------------------------

-- External table
create external table junk_chat_ext(
    Junk_chat_ID int,
    is_customer_service_called boolean,
    is_problem_solved boolean
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
location 'hdfs:///user/liu_osama/database/junk_chat'
TBLPROPERTIES ("skip.header.line.count"="1");

--------------------------------------------

-- External table
create external table promo_code_ext(
    Promo_code_ID int,
    category_discount UNIONTYPE<string, int>,
    is_used boolean
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
COLLECTION ITEMS TERMINATED BY '|'
location 'hdfs:///user/liu_osama/database/promo_code'
TBLPROPERTIES ("skip.header.line.count"="1");

--------------------------------------------

-- external + static partition
create external table signing_in_ext(
    discount int,
    sign_in_date_id int,
    promo_code_id int,
    user_id int
)
PARTITIONED BY (year INT)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
COLLECTION ITEMS TERMINATED BY '|'
location 'hdfs:///user/liu_osama/database/signing_in';

--------------------------------------------

create external table time_csv(
    time_id int,
    hours int,
    minutes int,
    seconds int,
    time_of_day string
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
location 'hdfs:///user/liu_osama/database/time'
TBLPROPERTIES ("skip.header.line.count"="1");

create table time_par(
    time_id int,
    hours int,
    minutes int,
    seconds int,
    time_of_day string
)
STORED AS PARQUET;

--------------------------------------------

create external table user_csv(
    user_id int,
    profile struct<name_and_surname:string,sex:char(1),pesel_bk:string>,
    age_category string
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
COLLECTION ITEMS TERMINATED BY '|'
location 'hdfs:///user/liu_osama/database/user'
TBLPROPERTIES ("skip.header.line.count"="1");

create external table user_par(
    user_id int,
    profile struct<name_and_surname:string,sex:char(1),pesel_bk:string>
)
PARTITIONED BY (age_category string)
CLUSTERED BY (user_id) INTO 5 buckets
STORED AS parquet;

```

### 加载数据
```bash
# external table
hdfs dfs -copyFromLocal ./* /user/liu_osama/database;
# exterbak table + static partition
ALTER TABLE signing_in_ext ADD PARTITION (year='2015') LOCATION '/user/liu_osama/database/signing_in/2015';
ALTER TABLE signing_in_ext ADD PARTITION (year='2016') LOCATION '/user/liu_osama/database/signing_in/2016';
ALTER TABLE signing_in_ext ADD PARTITION (year='2017') LOCATION '/user/liu_osama/database/signing_in/2017';
ALTER TABLE signing_in_ext ADD PARTITION (year='2018') LOCATION '/user/liu_osama/database/signing_in/2018';
ALTER TABLE signing_in_ext ADD PARTITION (year='2019') LOCATION '/user/liu_osama/database/signing_in/2019';
ALTER TABLE signing_in_ext ADD PARTITION (year='2020') LOCATION '/user/liu_osama/database/signing_in/2020';
ALTER TABLE signing_in_ext ADD PARTITION (year='2021') LOCATION '/user/liu_osama/database/signing_in/2021';
# internal table
INSERT INTO TABLE booking_orc partition(junk_booking_id)
SELECT * FROM booking_csv;

INSERT INTO TABLE chatting_orc partition(employee_id)
SELECT user_id,named_struct("helpful",helpful,"experience",experience),duration,response_time,junk_chat_id,chat_date_id,starting_time_id,ending_time_id,employee_id FROM chatting_csv;

INSERT INTO TABLE date_par
SELECT * FROM date_csv;

INSERT INTO TABLE time_par
SELECT * FROM time_csv;

INSERT INTO TABLE user_par partition(age_category)
SELECT * FROM user_csv;
```