# Builder和lombok优化
[java中的.builder()方法实现详解_Keson Z的博客-CSDN博客_.builder()](https://blog.csdn.net/weixin_44009447/article/details/118526794)

## 场景模拟
假如有一结果api结果返回值的类Result，其在代码中频繁被使用：
```java
public class Result<T> {
    private int code;
    private String message;
    private T data;

    public Result(int code, String message, T data) {
        this.code = code;
        this.message = message;
        this.data = data;
    }

    public Result() {
    }

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }

    @Override
    public String toString() {
        return "Result{" +
                "code=" + code +
                ", message='" + message + '\'' +
                ", data=" + data +
                '}';
    }
}
```

如果要使用它，一般的方法是：
```java
public class Main {
    public static void main(String[] args) {
        //方法1，使用全量的构造函数
        Result<String> result1 = new Result<>(200, "success", "");

        //方法2，使用空的构造函数加setter函数赋值
        Result<String> result2 = new Result<>();
        result2.setCode(200);
        result2.setMessage("success");
        result2.setData("");
    }
}
```
这两种使用方法的弊端有：

（1）方法一：当只需要部分参数的时候需要再定义个**构造函数**（比如失败的情况只需要code和message，结果肯定是空，因此不需要data），且一旦参数较多，则构造函数冗长；

（2）方法二：**setter冗长**；

因此我们需要builder来解决这个问题。

## java实现builder

```java
    public static final class Builder<T> {
        private int code;
        private String message;
        private T data;

        private Builder() {
        }

        public Builder code(int val) {
            code = val;
            return this;
        }

        public Builder message(String val) {
            message = val;
            return this;
        }

        public Builder data(T val) {
            data = val;
            return this;
        }

        public Result build() {
            return new Result(this);
        }
    }
```

使用：
```java
Result<String> result3 = new Result.Builder<>().code(404).message("failure").build();
Result<String> result4 = Result.newBuilder().code(404).message("failure").build();
```

## 使用lombok优化

```java
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;


@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class Result<T> {
    private int code;
    private String message;
    private T data;
}
```

使用
```java
Result<String> result5 = Result.<String>builder().code(404).message("failure").build();
```