# channel

```go
var LoggedIn make(chan bool, 1)

select {
case <-config.LoggedIn:
	log.Info(config.Clients[clientId].WXAccount + "登录成功")
case <-time.After(30 * time.Second):
	log.Info(config.Clients[clientId].WXAccount + "登录超时")
	panic("登录超时")
}
```