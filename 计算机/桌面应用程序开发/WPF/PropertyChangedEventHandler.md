# PropertyChangedEventHandler

在 C# 中，PropertyChangedEventHandler.Invoke 方法用于触发 PropertyChanged 事件。PropertyChanged 事件是一个常用的事件，用于通知数据绑定系统属性的值已经发生改变。

## PropertyChangedEventHandler.Invoke
在 C# 中，PropertyChangedEventHandler.Invoke 方法是一个同步方法，它会阻塞调用线程，直到所有事件处理程序执行完成。

PropertyChangedEventHandler 是一个委托类型，它定义了一个接收两个参数的方法，第一个参数是事件源，第二个参数是 PropertyChangedEventArgs 类型的参数，PropertyChangedEventArgs 类型的对象包含了有关属性更改的信息，例如属性名称和旧值和新值。

在使用 PropertyChangedEventHandler.Invoke 方法时，需要传递一个 PropertyChangedEventArgs 类型的参数作为参数。例如：
```csharp
public void Invoke(object sender, PropertyChangedEventArgs e);
```

```csharp
public event PropertyChangedEventHandler PropertyChanged;

protected virtual void OnPropertyChanged(string propertyName)
{
    var handler = PropertyChanged;
    if (handler != null)
    {
        handler.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
```

```csharp
public class ViewModelBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
```
