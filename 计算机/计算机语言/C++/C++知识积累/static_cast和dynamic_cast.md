# static_cast 和 dynamic_cast
[static_cast和dynamic_cast详解_的博客-CSDN博客_static_cast](https://blog.csdn.net/u014624623/article/details/79837849)

相当于传统的C语言里的强制转换，该运算符把expression转换为new_type类型

- 基本类型
  ```cpp
  char a = 'a';
  int b = static_cast<int>(a);//正确，将char型数据转换成int型数据

  double *c = new double;
  void *d = static_cast<void*>(c);//正确，将double指针转换成void指针

  int e = 10;
  const int f = static_cast<const int>(e);//正确，将int型数据转换成const int型数据

  const int g = 20;
  int *h = static_cast<int*>(&g);//编译错误，static_cast不能转换掉g的const属性
  ```

上面转换为const int的例子并不能用于生成数组

- 类
  ```cpp
  class Base{};

  class Derived : public Base{}

  Base* pB = new Base();
  if(Derived* pD = static_cast<Derived*>(pB)){}//下行转换是不安全的(坚决抵制这种方法)

  Derived* pD = new Derived();
  if(Base* pB = static_cast<Base*>(pD)){}//上行转换是安全的
  ```

尽量少使用转型操作，尤其是dynamic_cast，耗时较高，会导致性能的下降，尽量使用其他方法替代。