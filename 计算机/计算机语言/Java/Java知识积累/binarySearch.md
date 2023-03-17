# binarySearch

## 讲解
binarySearch 方法是在Java中 `Arrays` 和 `Collections` 类中定义的静态方法，它可以用于在有序数组或列表中查找指定元素。

使用 binarySearch 方法需要注意以下几点：

1. 在使用 binarySearch 方法查找元素之前，必须将数组或列表按**升序或降序排序**。

2. 如果指定的元素在数组或列表中**存在**，则 binarySearch 方法将**返回元素的索引**。否则，它将返回一个**负数**，表示**无法找到元素**。

3. 返回值的负数表示插入元素的位置（即将指定元素插入到数组或列表中时，应该放置在哪个位置）。具体来说，返回的负数是 `(-(插入点) - 1)`，其中插入点是将指定元素插入到数组或列表中的索引位置。


## 举例：
1 3 5 7 9

* 查询4，返回 -(2) - 1 = -3
* 查询6，返回 -(3) - 1 = -4

## 代码
```java
for(int i = 0; i < m; i++){
    int res = Arrays.binarySearch(prefix, queries[i]);
    if(res < 0){
        queries[i] = -res - 1;
    }else{
        queries[i] = res + 1;
    }
}
```
