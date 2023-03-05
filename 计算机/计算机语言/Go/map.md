# map

```go
func main() {
    // 创建一个空的字符串类型的 map
    m := make(map[string]int)

    // 添加一些键值对
    m["apple"] = 1
    m["banana"] = 2
    m["cherry"] = 3

    // 访问一个键的值
    fmt.Println(m["banana"])  // 输出 2

    // 遍历所有键值对
    for k, v := range m {
        fmt.Println(k, v)
    }
}
```

