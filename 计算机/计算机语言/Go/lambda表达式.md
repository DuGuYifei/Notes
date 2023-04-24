# lambda表达式

```go
func sortPeople(names []string, heights []int) []string {
	n := len(names)
	idx := make([]int, n)
	for i := 0; i < n; i++ {
		idx[i] = i
	}
	sort.Slice(idx, func(i, j int) bool {
		return heights[idx[i]] > heights[idx[j]]
	})

	ans := make([]string, n)
	for i := 0; i < n; i++ {
		ans[i] = names[idx[i]]
	}
	return ans
}
```

