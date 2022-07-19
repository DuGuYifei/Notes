# using
## 用于定义一个范围，在此范围的末尾将释放对象
```c#
string[] names = new string[] { "Zara Ali", "Nuha Ali" };
using (StreamWriter sw = new StreamWriter("names.txt"))
{
    foreach (string s in names)
    {
        sw.WriteLine(s);
    }
}

Fontfont2 = new Font("Arial", 10.0f);
using(font2)
{
//use font2
}
//2.可以有多个对象与using语句一起使用，但是必须在using语句内部声明这些对象，如下所示：
using(Fontfont3 = new Font("Arial", 10.0f),font4 = new Font("Arial", 10.0f))
{
//Use font3 and font4.
}
```


## 用于为命名空间创建别名或导入其他命名空间中定义的类型
`using System` 在开头