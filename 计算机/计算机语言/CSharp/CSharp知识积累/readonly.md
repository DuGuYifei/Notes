# readonly

在 C# 中，readonly 是一个关键字，用于声明只读字段。只读字段只能在定义时或在构造函数中进行初始化，之后就无法修改它们的值。

需要注意的是，只读字段和常量 (const) 有所不同。常量在声明时必须进行初始化，并且不能在后续代码中修改。只读字段可以在构造函数中进行初始化，并且可以有不同的值，但一旦初始化之后就不能再修改了。

```csharp
public class MyClass
{
    public readonly int MyReadOnlyField;

    public MyClass(int value)
    {
        MyReadOnlyField = value;
    }
}
```