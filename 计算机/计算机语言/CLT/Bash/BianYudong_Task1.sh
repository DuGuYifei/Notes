#!/bin/bash

# 根据日期
grep . $1 | cut -d '[' -f 2 | cut -d ':' -f 1 | uniq -c

# 根据ip地址：grep提取文件，$1是第一个参数，也就是再linux中输入 "BianYudong_Task1.sh access.log" 空格分隔参数，从第0个参数开始， access.log是第1个参数 cut 分割，-d 选择分隔符，-f 取第几块。 uniq -c c表示count。
grep . $1 | cut -d '-' -f 1 | uniq -c