# go

## 语法
```go
go func(a int, b int) {
    // do something with a and b
}(10, 20)
```

## 启动goroutine
"goroutine"是 Go 语言中非常重要的概念，它是一种轻量级的线程，能够在单个程序中同时运行多个任务。在 Go 语言中，使用关键字 "go" 来启动一个新的goroutine，例如：

```go
go func() {
    // code to be executed concurrently
}()
```

上述代码中，使用了 "go" 关键字启动了一个新的goroutine，这样该函数就能够在另一个线程中异步执行，而不会影响主线程的执行。

```go
func main() {
    go printHello() // Start a new Goroutine
    fmt.Println("Main function")
}

func printHello() {
    fmt.Println("Hello from Goroutine")
}


// 输出
//Main function
//Hello from Goroutine
```