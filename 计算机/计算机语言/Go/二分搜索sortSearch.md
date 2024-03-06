# 二分搜索sortSearch



## sort.Search
```go
func Search(n int, f func(int) bool) int

queries[i] = sort.Search(n, func(j int) bool { return prefix[j] > queries[i] })
```
按条件查找符合条件的第一索引

### 参数
其中，n 是切片中的元素数量，f 是一个函数。该函数：
* **返回 true，向左查找**
* **参数是索引**

## sort.Search + Ints/...
查找第一个**大于等于**寻找的值的索引

```go
for _, q := range queries {
    idx := sort.SearchInts(f, q+1)
}
```