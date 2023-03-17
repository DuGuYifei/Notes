# DataContract

DataContract 特性用于标记一个类，表示这个类可以被**序列化和反序列化**。在 DataContract 中，我们可以设置一些序列化的选项，例如是否启用数据成员的顺序，是否序列化基类等等。

DataMember 特性用于标记类中**需要进行序列化和反序列化的属性或字段**，表示这些属性或字段是要在序列化和反序列化中进行处理的。在 DataMember 中，我们可以设置一些序列化的选项，例如成员名称、顺序、是否必需等等。

下面是一个使用 DataContract 和 DataMember 的示例：
```csharp
[DataContract]
public class Person
{
    [DataMember(Name = "ID")]
    public int Id { get; set; }

    [DataMember(Name = "Name")]
    public string Name { get; set; }

    [DataMember(Name = "Age")]
    public int Age { get; set; }

    public Person(int id, string name, int age)
    {
        Id = id;
        Name = name;
        Age = age;
    }
}
```