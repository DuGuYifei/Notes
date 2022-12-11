# lambda表达式


```Java
// 大括号要return，括号里两个参数代表要用的参数，一个参数就不用括号
Arrays.sort(cuboids, (a,b)->{int s = (a[2] - b[2]); return s == 0? (a[1] - b[1] == 0? a[0] - b [0] : a[1] - b[1]): s;});
// 没有括号不用return直接表示return
Arrays.sort(cuboids, (a,b)->a[2] - b [2]);
```