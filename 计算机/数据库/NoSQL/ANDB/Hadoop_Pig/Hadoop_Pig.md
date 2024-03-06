# Hadoop_Pig

## introduction and operations teaching
[课件](AZTNBD_Pig.pdf)

## 操作

```bash
# max_temp.pig 文件
set pig.temp.dir /user/Liu/pigtmp
recs = load '/user/Liu/austin_daily_weather.tsv';
recs2 = FOREACH recs GENERATE $2, $3;
recs3 = FOREACH recs2 GENERATE SUBSTRING($0,0,4), (double)$1;
recs4 = GROUP recs3 BY $0;
recs5 = FOREACH recs4 GENERATE group, MAX(recs3.$1);
dump recs5;
```

获得每年的最高华氏度温度：（$2 即第三列，第三列是包含年月日的日期，第四列是当日最高温度）
```bash
hadoop jar pig-withouthadoop.jar
grunt>run max_temp.pig
```

自定义命令
1. 最高摄氏度
```bash
recs6 = FOREACH recs4 GENERATE group, (MAX(recs3.$1)-32)/1.8;
# 或者
recs10 = FOREACH recs5 GENERATE group, ($1-32)/1.8;
dump recs6;
```

1. 差异最大的一年
```bash
recs7 = FOREACH recs GENERATE $2, $5;
recs8 = FOREACH recs7 GENERATE SUBSTRING($0,0,4), (double)$1;
recs9 = GROUP recs8 BY $0;
recs10 = FOREACH recs9 GENERATE group, MIN(recs8.$1);
recs11 = JOIN recs5 by $0, recs10 by $0;
recs12 = FOREACH recs11 GENERATE $0, $1-$3;
recs13 = ORDER recs12 BY $1;
dump recs13;
```
或
```bash
set pig.temp.dir /user/Liu/pigtmp
recs = load '/user/Liu/austin_daily_weather.tsv';
recs7 = FOREACH recs GENERATE $2, $3, $5;
recs8 = FOREACH recs7 GENERATE SUBSTRING($0,0,4), (double)$1, (double)$2;
recs9 = GROUP recs8 BY $0;
recs10 = FOREACH recs9 GENERATE group, MAX(recs8.$1), MIN(recs8.$2);
recs11 = FOREACH recs10 GENERATE $0, $1-$2;
recs12 = GROUP recs11 ALL;
recs13 = FOREACH recs12 GENERATE MAX(recs11.$1);
recs14 = FILTER recs11 BY $1==recs13.$0;
dump recs14;
```