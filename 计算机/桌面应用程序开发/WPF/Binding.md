# Binding

```xaml
<!-- <UserControl.DataContext>
    <local:NewProject />
</UserControl.DataContext> -->
<!-- 或 -->
<UserControl ...
d:DataContext="{d:DesignInstance Type=local:NewProject, IsDesignTimeCreatable=True}" ... />
```
`IsDesignTimeCreatable` 是一个 XAML 属性，用于指示是否应在设计时**创建某个控件的实例**。它通常用于设计时预览和数据绑定。
```xaml
<TextBox Width="550" Text="{Binding Name}"/>
```

Name来自NewProject
