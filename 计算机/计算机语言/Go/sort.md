# sort

## sort
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