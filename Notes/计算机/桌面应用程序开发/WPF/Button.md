# Button


## IsDefault属性
Button控件的IsDefault属性用于指示按钮是否是默认按钮。默认按钮是指在一个窗口中，用户按下回车键时会自动触发的按钮，而非默认按钮则不会。如果一个窗口中有多个按钮，那么只有一个按钮可以被指定为默认按钮，这个按钮可以通过设置IsDefault属性来实现。

当IsDefault属性被设置为true时，按钮将被标记为默认按钮。此时，当用户按下回车键时，将自动触发按钮的Click事件。如果没有按钮被指定为默认按钮，则用户按下回车键不会触发任何按钮的Click事件。

以下是一个简单的示例，演示如何将Button控件设置为默认按钮：

```xml
<Window>
    <StackPanel>
        <Button Content="Save" IsDefault="True" Click="Save_Click"/>
        <Button Content="Cancel" Click="Cancel_Click"/>
    </StackPanel>
</Window>
```

## IsCancel属性

按ESC