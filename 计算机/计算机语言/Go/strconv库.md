# strconv库

用于字符串和基本数据类型之间的转换

* strconv.Itoa(i int) string：将一个整数转换为对应的字符串。
* strconv.Atoi(s string) (int, error)：将一个字符串转换为对应的整数。如果转换失败，返回一个错误。
* strconv.ParseBool(str string) (bool, error)：将一个字符串解析为对应的布尔值（true/false）。
* strconv.ParseInt(s string, base int, bitSize int) (int64, error)：将一个字符串解析为对应的整数。其中，base 表示字符串表示的进制数（2 到 36），bitSize 表示返回值的位数（即 int8、int16、int32 或 int64）。
* strconv.ParseUint(s string, base int, bitSize int) (uint64, error)：将一个字符串解析为对应的无符号整数。其中，base 表示字符串表示的进制数（2 到 36），bitSize 表示返回值的位数（即 uint8、uint16、uint32 或 uint64）。
* strconv.ParseFloat(s string, bitSize int) (float64, error)：将一个字符串解析为对应的浮点数。其中，bitSize 表示返回值的位数（即 float32 或 float64）。



```go
pathSegments := strings.Split(r.URL.Path, "/")
id, err := strconv.Atoi(pathSegments[2])
```