# TextBlock和TextBox

TextBlock 是一个只读的文本控件，用于显示静态文本内容。它支持设置文本的字体、颜色、对齐方式等属性，并且可以自动换行和调整文本大小以适应控件大小。TextBlock 不支持编辑或输入文本，因此适用于显示不可编辑的文本内容，例如文本标签、说明文本等。

TextBox 是一个可编辑的文本控件，用于输入和显示用户输入的文本内容。它支持设置文本的字体、颜色、对齐方式等属性，并且可以自动换行和调整文本大小以适应控件大小。用户可以通过键盘或鼠标输入文本内容，并且可以使用剪贴板复制和粘贴文本。TextBox 通常用于实现用户输入和编辑功能，例如输入框、搜索框、编辑器等。

```xaml
<!-- TextBlock 示例 -->
<TextBlock Text="这是一个文本标签" FontSize="16" Foreground="Black" />

<!-- TextBox 示例 -->
<TextBox Text="请输入文本" FontSize="16" Foreground="Black" />
```