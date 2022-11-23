# Hive Operations

## 连接
```bash
$ ssh atndb13@153.19.52.196
$ beeline
beeline> !connect jdbc:hive2://
Connecting to jdbc:hive2://
Enter username for jdbc:hive2://: atndb13
Enter password for jdbc:hive2://: ******
```

## 数据库
其实就是一文件夹
### 创建数据库
```bash
create database atndb13_liu_db;
```
### 使用指定数据库
```
0: jdbc:hive2://> use atndb13_liu_db;
```

### 表
#### 显示所有表或数据库
```bash
# Check if there are any tables created:
show tables;
show databases;
```
#### Create internal table:
```bash
create table if not exists simpletable(Number int)
stored as textfile;
```
#### 加载数据
**也可以加载对应存储形式的二进制文件，比如sequencefile，avro等**
```bash
# overwirte 可以去掉，如果要append模式的话
load data local inpath ‘simpleTableContent.txt’
overwrite into table prostatabela;
```

多列以及分隔符
```bash
create table tb 
(
    name1 int,
    name2 string
)
row format delimited
    fields terminated by '|'
stored as textfile;
```

#### create external table:
```bash
create external table simpleexternaltable(Numberint)
location ‘hdfs:///user/[login]/database’;
```
#### Display the description of newly created table:
```bash
describe simpletable;
describe formatted simpletable;
describe extended simpletable;
```
#### drop
```bash
drop table simpletable;
```

#### 文件夹变化
创建表后
`/user/hive/warehouse/atndb13_liu_db` 会出现以表名为名的文件夹

加入数据后，
该问价夹下还会出现子文件。

#### 各种storing type
##### TEXTFILE SEQUENCEFILE ORC PARQUET RCFILE
``` 
STORED AS TEXTFILE
STORED AS SEQUENCEFILE
STORED AS ORC
STORED AS PARQUET
STORED AS RCFILE
```

After using `describe extended [table]` and `describe formatted table`, the output is almost same between SEQUENCEFILE ORC PARQUET RCFILE.

![](2022-11-23-20-35-44.png)

![](2022-11-23-20-36-33.png) ![](2022-11-23-20-35-57.png)


But of course, they have different structures.

But of course, they have different structures.
1.	Sequencefile: 
Horizontal row-store. 
Divide into block. Have its own structure depend on compress configuration.
![](2022-11-23-20-40-30.png)
2.	Parquet: 
Column-store. Group columns then store block as column.
![](2022-11-23-20-40-36.png)
3.	RCfile: 
row column file. Group rows then store as block.
![](2022-11-23-20-40-43.png)
4.	ORC: 
column-oriented. 
Divide into stripes. Each stripe includes an index, data, and Footer. The index stores the maximum/minimum values of each column and the position of each row in the column.
![](2022-11-23-20-40-50.png)

##### AVRO
Create table for storing data in AVRO:
```bash
CREATE TABLE doctors
ROW FORMAT
SERDE 'org.apache.hadoop.hive.serde2.avro.AvroSerDe'
STORED AS
INPUTFORMAT
'org.apache.hadoop.hive.ql.io.avro.AvroContainerInputFormat'
OUTPUTFORMAT
'org.apache.hadoop.hive.ql.io.avro.AvroContainerOutputFormat'
TBLPROPERTIES ('avro.schema.literal'='{
"namespace": "testing.hive.avro.serde",
"name": "doctors",
"type": "record",
"fields": [
{
"name":"number",
"type":"int",
"doc":"Order of playing the role"
},
{
"name":"first_name",
"type":"string",
"doc":"first name of actor playing role"
},
{
"name":"last_name",
"type":"string",
"doc":"last name of actor playing role"
},
{
"name":"extra_field",
"type":"string",
"doc:":"an extra field not in the original file",
"default":"fishfingers and custard"
}
]
}');
```