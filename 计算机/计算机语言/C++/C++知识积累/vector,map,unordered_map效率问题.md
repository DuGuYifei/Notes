# vector,map,unordered_map效率问题

[vector、map还是unordered_map？_Rechar_Deng的博客-CSDN博客](https://blog.csdn.net/acaiwlj/article/details/49781877)

1. 内存：
   1. 少量时候用vector
   2. 大量就map,再unordered_map
2. 查询效率:
   1. 二分法`vector<pair<>>`跟另两个差不多，但终究还是hash map快
   2. map很慢