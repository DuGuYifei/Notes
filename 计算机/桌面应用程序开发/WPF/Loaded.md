# Loaded

"Loaded"是WPF中的一个事件，它表示控件已经被加载到其视觉树中，但尚未被呈现。在WPF中，每个控件都具有一个名为"Loaded"的事件，当控件的"Loaded"事件被引发时，可以执行一些特定的操作，例如初始化控件的状态、注册事件处理程序等。

"Loaded"事件是在控件被加载后立即引发的，它是在控件的构造函数之后和在控件的"Initialized"事件之前引发的。可以使用"Loaded"事件执行某些初始化操作，例如在控件加载后为其设置默认值、填充控件的数据源等等。

"Loaded"事件的类型为"RoutedEventHandler"，因此可以使用常规的事件处理程序来处理它。在XAML中，可以通过添加"Loaded"属性和相应的事件处理程序来处理控件的"Loaded"事件，例如：

```xml
<Button Content="Click me!" Loaded="Button_Loaded" />
```

方法二：使用代码
```C#
private void Button_Loaded(object sender, RoutedEventArgs e)
{
    // 在控件加载时执行一些操作
    // 例如设置控件的初始状态、初始化控件的数据等等
}
// 在代码中注册事件处理程序
myButton.Loaded += new RoutedEventHandler(Button_Loaded);
```