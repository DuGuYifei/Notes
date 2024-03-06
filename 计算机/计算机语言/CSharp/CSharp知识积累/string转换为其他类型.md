# string转换为其他类型

arse 和 TryParse 方法会忽略字符串开头和末尾的空格，但所有其他字符都必须是组成合适数值类型（int、long、ulong、float、decimal 等）的字符。 如果组成数字的字符串中有任何空格，都会导致错误。 例如，可以使用 decimal.TryParse 分析“10”、“10.3”或“ 10 ”，但不能使用此方法分析从“10X”、“1 0”（注意嵌入的空格）、“10 .3”（注意嵌入的空格）、“10e1”（float.TryParse 在此处适用）等中分析出 10。 无法成功分析值为 null 或 String.Empty 的字符串。 在尝试通过调用 String.IsNullOrEmpty 方法分析字符串之前，可以检查字符串是否为 Null 或为空。

```c#
temp.x = float.Parse(sr.ReadLine());
```