# push和emplace区别

[emplace](emplace.md)

```cpp
stack<pair<int, int>> run;

run.push(idx, timestamp); // 会报错
run.emplace(idx, timestamp); // 不会报错
```

```cpp
class Person
{
 public:
    int m_age;
    string m_name; 
};
stack<Person> s2;
//对于这种自定义数据类型还能进行如下的插入操作吗?
s2.push(18,"貂蝉");❌
//答案是否定的
//若想用push进行插入，只能先将这个对象构造出来，再将这个对象插入
Person p1(18,"西施");✅
s2.push(p1);
//或
s2.push(Person(19,"杨玉环"))//传入时构造对象

s2.emplace(20,"张三") //可以
```
