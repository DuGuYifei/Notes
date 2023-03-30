# sort

## sort.Slice
注意sort.Slice中的比较函数，放的是索引，不是里面的实体

`nums []int`:
```go
sort.Ints(nums)

// 递增排序
sort.Slice(players, func(i, j int) bool {
	if players[i][0] < players[j][0]{
		return true
	}else if players[i][0] > players[j][0]{
		return false
	}
	return players[i][1] < players[j][1]
})
```

## sort.Search + Ints/...

[二分搜索sortSearch](二分搜索sortSearch.md)