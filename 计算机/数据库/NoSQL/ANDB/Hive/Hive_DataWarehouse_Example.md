# Hive_DataWarehouse_Example

## design
comment: 
* external table xxxx_ext
* xxxx_parquet _orc
* parquet and orc need select from an external table XXX_csv
* `profile STRUCT <>` employee user
* `rate STRUCT <helpful: int, experience: int>`
* `category_discount struc<string, int, array<string>>`
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
   1. partition: static -> year
   2. external table
   3. static partitioned by `ALTER TABLE testdb.table1 ADD PARTITION (dept='dept1') LOCATION '/path/to/dataFile/dept1';`
   4. year divide:
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
    channel char(3),
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
    is_call_service_needed boolean,
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
    category_discount struct<category:string, dicount:int, conditions:array<string>>,
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
## 谓词下推(Predicate Pushdown)
```
set hive.optimize.ppd = true;
```

## query
1. How many customers used special promo code which have no conditions and get discount for new users during sign in, compare last two subsequent years.
    ```sql
    with t as (
        select promo_code_id
        from promo_code_ext
        where category_discount.conditions is null and is_used = true
    )
    select year, count(year) as user_cnt
    from signing_in_ext, t
    where year = 2021 and signing_in_ext.promo_code_id = t.promo_code_id
    GROUP BY year
    UNION ALL
    select year, count(year) as user_cnt
    from signing_in_ext, t
    where year = 2020 and signing_in_ext.promo_code_id = t.promo_code_id
    GROUP BY year;
    ```
2. Compare the number of accounts that were signed-in in later half of year of last two subsequent years.
    ```sql
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
   
3. Compare the number of appointments that were set up through web registration in last two subsequent years.
    ```sql
    with 
        t as (
            select junk_booking_id
            from junk_booking_ext
            where 
                channel = "web" and
                is_successful = true
        ),
        y as(
            select date_id, year
            from date_par
            where year = 2021 or year = 2020
        )
    select 2021, count(transaction_no) as appointment_num
    from booking_orc, t, (
            select date_id
            from y
            where year = 2021
        ) as y1
    where 
        booking_orc.junk_booking_id = t.junk_booking_id and
        booking_orc.booking_date_id = y1.date_id
    UNION ALL
    select 2020, count(transaction_no) as appointment_num
    from booking_orc, t, (
            select date_id
            from y
            where year = 2020
        ) as y2
    where 
        booking_orc.junk_booking_id = t.junk_booking_id and
        booking_orc.booking_date_id = y2.date_id;
    ```
4. Compare the number of users who at least twice made an appointment through online registration (compare two subsequent years).
    ```sql
    with 
        t as(
            select junk_booking_id
            from junk_booking_ext
            where 
                channel = "web" and
                is_successful = true
        ),
        y as(
            select date_id, year
            from date_par
            where year = 2021 or year = 2020
        )
    select 2021, count(user_id) as gt2_num
    from(
        select user_id, count(transaction_no) as user_num
        from booking_orc, t, (
                select date_id
                from y
                where year = 2021
            ) as y1
        where
            booking_orc.junk_booking_id = t.junk_booking_id
        group by user_id
    ) as t1 
    where user_num > 2
    union all
    select 2020, count(user_id) as gt2_num
    from(
        select user_id, count(transaction_no) as user_num
        from booking_orc, t, (
                select date_id
                from y
                where year = 2020
            ) as y2
        where
            booking_orc.junk_booking_id = t.junk_booking_id
        group by user_id
    ) as t2
    where user_num > 2;
    ```
5. Compare the proportion of opened web registration sessions (means contact with employee) which end up with making an appointment for two subsequent years.
    ```sql
    with 
        t as (
            select junk_booking_id
            from junk_booking_ext
            where 
                channel = "web" and
                is_successful = true and
                is_employee_needed = true
        ),
        y as(
            select date_id, year
            from date_par
            where year = 2021 or year = 2020
        )
    select 2021, count(transaction_no) as appointment_num
    from booking_orc, t, (
            select date_id
            from y
            where year = 2021
        ) as y1
    where 
        booking_orc.junk_booking_id = t.junk_booking_id and
        booking_orc.booking_date_id = y1.date_id
    UNION ALL
    select 2020, count(transaction_no) as appointment_num
    from booking_orc, t, (
            select date_id
            from y
            where year = 2020
        ) as y2
    where 
        booking_orc.junk_booking_id = t.junk_booking_id and
        booking_orc.booking_date_id = y2.date_id;
    ```
    
6. What was the people’s average rate (rate = helpful + experience) about our chatting with customer service in two consecutive years?
    ```sql
    with y as (
        select date_id, year
        from date_par
        where year = 2021 or year = 2020
    ) 
    select 2021, avg(rate.helpful + rate.experience) as avg_rate
    from chatting_orc, (
                select date_id
                from y
                where year = 2021
            ) as y1
    where chatting_orc.chat_date_id = y1.date_id
    union all
    select 2020, avg(rate.helpful + rate.experience) as avg_rate
    from chatting_orc, (
                select date_id
                from y
                where year = 2020
            ) as y2
    where chatting_orc.chat_date_id = y2.date_id;
    ```
7. How do people evaluate the average rate (rate = helpfulness + experience) of chatters, compare last two consecutive years of each employee?
    ```sql
    with
        y as (
            select date_id, year
            from date_par
            where year = 2021 or year = 2020
        ) 
    select t1.employee_id, t2.employee_id, t1.avg_rate as rate_2021, t2.avg_rate as rate_2022
    from
    (
        (
            select avg(rate.helpful + rate.experience) as avg_rate, employee_id
            from chatting_orc, (
                select date_id
                from y
                where year = 2021
            ) as y1
            where chatting_orc.chat_date_id = y1.date_id
            group by employee_id
        )as t1
        full outer join
        (
            select avg(rate.helpful + rate.experience) as avg_rate, employee_id
            from chatting_orc, (
                select date_id
                from y
                where year = 2020
            ) as y2
            where chat_date_id = y2.date_id
            group by employee_id
        ) as t2
        on t1.employee_id = t2.employee_id
    );
    ```
8. What was the average response time for the first message in the chat of employees?Sort Jonathan Mitchell, Shannon Santos and Carl Fox.
    ```sql
    select name, avg(response_time) as avg_res
    from chatting_orc, (
        select employee_id, profile.name_and_surname as name
        from employee_ext
        where 
            profile.name_and_surname = "Carl Fox" or 
            profile.name_and_surname = "Jonathan Mitchell" or
            profile.name_and_surname = "Shannon Santos"
    ) as t
    where
        chatting_orc.employee_id = t.employee_id
    group by name
    order by avg_res desc;
    ```
9.  What was the average time of the chats for each employee of female whose average helpful rate and experience rate not less than 3?
    ```sql
    select t1.employee_id as employee_id, sex as sex, avg_duration as avg_duration
    from 
    (
        select employee_id, profile.sex as sex
        from employee_ext
        where profile.sex = 'F'
    ) as t1
    LEFT JOIN    
    (
        select 
            employee_id,
            avg(duration) as avg_duration,
            avg(rate.helpful) as avg_helpful, 
            avg(rate.experience) as avg_experience
        from chatting_orc
        GROUP BY employee_id
    ) as t2
    ON 
        t2.avg_helpful >= 3 and 
        t2.avg_experience >= 3 and 
        t1.employee_id = t2.employee_id
    where avg_duration is not NULL;
    ```
10. How many cases the customer wanted to call rather than continue chatting for employee from 22-29 years old? 
    ```sql
    select count(chatting_orc.junk_chat_id)
    from chatting_orc, (
        select junk_chat_id 
        from junk_chat_ext
        where 
            is_problem_solved = false and 
            is_call_service_needed = true
    ) as t1,(
        select employee_id
        from employee_ext
        where age_category = "from 22 to 29"
    ) as t2
    where 
        chatting_orc.junk_chat_id = t1.junk_chat_id and
        chatting_orc.employee_id = t2.employee_id;
    ```