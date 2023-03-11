# map

## 基础语法
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

```Go
indices := map[int]int{}
```

## 短声明问题
在 Go 语言中，使用短变量声明操作符 := 赋值时，如果左边至少有一个新的变量名，**则会将右边的值赋给这些变量，并返回一个 bool 类型的值，表示变量是否成功赋值。**

但是，这并不是说所有类型的变量都可以使用短变量声明方式来赋值并返回 bool 类型的值。只有在 map 类型中，当我们使用下标访问操作符 [] 时，如果该下标存在于 map 中，则会返回该键值对对应的值以及一个 bool 类型的值，表示该键值对是否存在于 map 中。

这个 bool 类型的值表示的是该键是否存在于 map 中，而不是变量是否成功赋值。因此，可以使用短变量声明操作符 := 来一次性获取键值对的值和存在性标志。

需要注意的是，这种方式只适用于 map 类型。其他类型的变量，如果你想要检查它们是否成功赋值，需要使用其他方式来实现，例如通过返回值、错误类型或其他变量来表示。

```go
if providerURLs, ok := p.services[patchEntry.Name]; ok {
    
}

m := make(map[int]int)
for i := 0; i < n; i++ {
	m[y] = i
	y = (y + nums[i]) % p
	if v, ok := m[(y-x+p)%p]; ok {
		ans = min(ans, i-v+1)
	}
}
```