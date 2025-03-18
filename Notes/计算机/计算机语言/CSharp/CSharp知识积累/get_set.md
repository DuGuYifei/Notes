# get_set

## 简写法
```csharp
public string Name { get; set; }
```
等价于

```csharp
private string _name;
public string Name
{
    get { return _name; }
    set { _name = value; }
}
```

## 写法1
```csharp
public class Person
{
	private string _name;
	public string Name
	{
		get { return _name; }
		set { _name = value; }
	}
}
```

## 写法2
```csharp
    public string Name
    {
        get => _name;
        set
        {
            if(_name != value)
            {
                _name = value;
                OnPropertyChanged(nameof(Name));
            }
        }
    }
```

总结关键点在于`_name=value`，其他的想怎么加怎么加

其中上面
1. 第一种是get set独有的写法
2. 第二种叫[lambda表达式](lambda表达式.md)