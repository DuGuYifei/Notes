# 读取json的时间为time类型

```go
type CustomTime struct {
	time.Time
}

// UnmarshalJSON 自定义 JSON 的解码方法
func (ct *CustomTime) UnmarshalJSON(b []byte) error {
	var s string
	if err := json.Unmarshal(b, &s); err != nil {
		return err
	}
	t, err := time.Parse("15:04", s)
	if err != nil {
		return err
	}
	ct.Time = t
	return nil
}
```