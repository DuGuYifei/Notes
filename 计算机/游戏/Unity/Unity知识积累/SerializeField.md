# SerializeField

## 作用

在Unity中，如果想要在Inspector面板中显示一个私有变量，可以使用`[SerializeField]`标签。

## 用法

```c#
[SerializeField] PlayerState[] states;
```

C#不写类成员不写修饰符的话，默认是private的