# lambda表达式


## 基础
```Java
// 大括号要return，括号里两个参数代表要用的参数，一个参数就不用括号
Arrays.sort(cuboids, (a,b)->{int s = (a[2] - b[2]); return s == 0? (a[1] - b[1] == 0? a[0] - b [0] : a[1] - b[1]): s;});
// 没有括号不用return直接表示return
Arrays.sort(cuboids, (a,b)->a[2] - b [2]);
```

## 局部变量问题
局部变量不能用于lamda表达式

### 报错
`Local variable res defined in an enclosing scope must be final or effectively final`
```Java
    public int countUnexpiredTokens(int currentTime) {
        int res = 0;
        ttmap.forEach((k, v) -> {
            if(v > currentTime)
                res++;
        });
        return res;
    }
```

### 无报错
```Java
    private int res;
    public int countUnexpiredTokens(int currentTime) {
        res = 0;
        ttmap.forEach((k, v) -> {
            if(v > currentTime)
                res++;
        });
        return res;
    }
```