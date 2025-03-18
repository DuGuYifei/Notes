# defer

`defer` 是 Go 语言中的一个关键字，用于**将一个函数调用延迟到当前函数执行完成之后再执行**。在 Go 语言中，defer 通常用于释放资源、关闭文件、解锁锁定的资源等清理操作，以保证这些操作一定会被执行，即使函数出现异常也不例外。

```Go
func main() {
    defer fmt.Println("1")
    fmt.Println("2")
    defer fmt.Println("3")
    fmt.Println("4")
    defer fmt.Println("5")
}

// 输出 24531
```