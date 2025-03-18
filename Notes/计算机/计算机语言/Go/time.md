# time

## time.After()
    
```go
func main() {
    ch := make(chan int)
    go func() {
        time.Sleep(3 * time.Second)
        ch <- 1
    }()
    select {
    case <-ch:
        fmt.Println("case1")
    case <-time.After(2 * time.Second):
        fmt.Println("case2")
    }
}
```

## time.Sleep()

```go
func main() {
    fmt.Println("start")
    time.Sleep(3 * time.Second)
    fmt.Println("end")
}
```

## time.Now()

```go
func main() {
    fmt.Println(time.Now())
}
```

### time.Now().UnixNano()
作用是返回当前时间的纳秒数

```go
if time.Now().UnixNano() > item.Expiration {
	talkCache.Delete(key)
	return msg, true
} else {
	talkCache.Set(key, msg, cache.DefaultExpiration)
	return "", false
}
```