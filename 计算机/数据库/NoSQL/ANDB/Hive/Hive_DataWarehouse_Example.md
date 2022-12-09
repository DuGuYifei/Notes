# Hive_DataWarehouse_Example

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
### 创建Textfile表格
```sql
create table booking_text(
    transaction_no int,
    user_id int,
    booking_date_id int,
    junk_booking_id int
)
ROW FORMAT DELIMITED
    FIELDS TERMINATED BY ','
STORED AS TEXTFILE;

create table chatting_text(
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
STORED AS TEXTFILE;

create table date_text(
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
STORED AS TEXTFILE;

create table employee_text(
    employee_id int,
    name_and_surname string,
    sex char(1),
    persel_bk string,
    age_category string,
    is_current string
)
ROW FORMAT DELIMITED
    FIELDS TERMINATED BY ','
STORED AS TEXTFILE;

create table junk_booking_text(
    Junk_booking_ID int,
    app_or_web string,
    successful_or_not string,
    employee_or_user_success string
)
ROW FORMAT DELIMITED
    FIELDS TERMINATED BY ','
STORED AS TEXTFILE;
```

### 去除第一行
```sql
ALTER TABLE booking_text SET TBLPROPERTIES ("skip.header.line.count"="1");
ALTER TABLE chatting_text SET TBLPROPERTIES ("skip.header.line.count"="1");
ALTER TABLE date_text SET TBLPROPERTIES ("skip.header.line.count"="1");
ALTER TABLE employee_text SET TBLPROPERTIES ("skip.header.line.count"="1");
ALTER TABLE junk_booking_text SET TBLPROPERTIES ("skip.header.line.count"="1");
```

### 加载数据
```sql
load data local inpath 'booking.csv' overwrite into table booking_text;
load data local inpath 'chatting.csv' overwrite into table chatting_text;
load data local inpath 'date.csv' overwrite into table date_text;
load data local inpath 'employee.csv' overwrite into table employee_text;
load data local inpath 'junk_booking.csv' overwrite into table junk_booking_text;
```