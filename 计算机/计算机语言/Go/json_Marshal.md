# json_Marshal

json.Marshal 函数用于将数据**结构**转换为 **JSON 格式的字符串**。

```go
import (
    "encoding/json"
    "fmt"
)

type Person struct {
    Name string `json:"name"`
    Age  int    `json:"age"`
}

func main() {
    p := Person{
        Name: "Alice",
        Age:  25,
    }
    b, err := json.Marshal(p)
    if err != nil {
        fmt.Println("error:", err)
    }
    fmt.Println(string(b)) // 输出 {"name":"Alice","age":25}
}
```