# string相关函数

## Split

```go
pathSegments := strings.Split(r.URL.Path, "/")
```

## ToLower 和 ToLowerSpecial
```go
func ToLower(s string) string
func ToLowerSpecial(c unicode.SpecialCase, s string) string
```
special:ToLowerSpecial 函数也执行类似的操作，但它还接受一个 unicode.SpecialCase 参数，该参数指定应如何将某些特定字符转换为小写形式。这对于非 ASCII 字符的转换非常有用，因为它允许您指定如何将 Unicode 字符转换为小写形式。

## IndexByte
作用: 返回字符串 s 中第一次出现 c 的位置，如果 s 中没有出现 c 则返回 -1。
```go
func IndexByte(s string, c byte) int
```

## Contains
作用: 返回字符串 s 是否包含子串 substr。
```go
string.Contains(s, substr string) bool
```

```go
func queryString(s string, n int) bool {
	if n > 1000 {
		return false
	}
	for i := (n >> 1) + 1; i <= n; i++ {
		if !strings.Contains(s, strconv.FormatInt(int64(i), 2)) {
			return false
		}
	}
	return true
}
```