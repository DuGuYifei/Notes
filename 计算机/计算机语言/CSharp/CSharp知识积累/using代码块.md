# using代码块

在 C# 中，使用 using 关键字可以创建一个代码块，在这个代码块中创建的对象可以自动地被垃圾回收机制释放掉。同时，也可以使用 using 关键字来导入命名空间，让代码中可以直接使用命名空间中的类型，而不需要每次都输入完整的命名空间和类型名称。

使用 using 导入命名空间后，就可以直接使用命名空间中的类型，而不需要每次都输入完整的命名空间和类型名称。例如：

```csharp
using( var stream = new FileStream("test.txt", FileMode.Open))
{
	// ...
}
```

```csharp
using var stream = new FileStream("test.txt", FileMode.Open);
// ...
```
第二种形式是当前代码块的结束位置释放。