# new和make

## new
new 函数用于创建一个指定类型的指针，并返回该指针。它的参数是一个类型，返回值是一个指向该类型零值的指针。例如：

```go
var p *int = new(int)
```

在上述示例中，变量 p 是一个指向 int 类型的指针，它指向的值为 0。可以通过 *p 来访问该指针指向的值。

## make
make 函数用于创建一个特定类型的对象，例如 slice、map 和 channel 等。它的参数是一个类型和一些参数，返回值是一个已经初始化之后的对象。例如：

```go
s := make([]int, 0, 10)  // 创建一个长度为 0，容量为 10 的 int 类型切片
```

在上述示例中，变量 s 是一个 int 类型的切片，长度为 0，容量为 10，它已经被初始化。

## 二维数组声明
```Go
	n, m := len(rowSum), len(colSum)
	ans := make([][]int, n)
	for i:=range ans{
		ans[i] = make([]int, m)
	}

	connect := make([][]int, n, n)
```