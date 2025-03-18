# string


## 函数
[strconv库](strconv%E5%BA%93.md)
[string相关函数](string%E7%9B%B8%E5%85%B3%E5%87%BD%E6%95%B0.md)

## 不能更改 
在 Go 语言中，字符串是不可变的，也就是说，一旦创建了一个字符串变量，就不能更改其中的任何字符。因此，以下语句是非法的：
```go
s[i] = byte('*')
```

如果您要更改字符串中的字符，可以将字符串转换为 []byte 类型的可变字节切片，然后修改其中的元素。例如：
```go
s := "hello"
b := []byte(s)
b[1] = '*'
s = string(b)
fmt.Println(s) // 输出: h*llo
```
