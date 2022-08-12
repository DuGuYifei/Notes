# Type

```csharp
Type type = typeof(Person);
Person person = new Person();
Type type2 = person.GetType();



使用typeof运算符，如
Type t = typeof(int);

使用GetType()方法，如
int i;Type t = i.GetType();

使用Type类的静态方法GetType()，如
Type t = Type.GetType("System.Double");
```

剩下的唯一问题就是要知道装箱和拆箱在什么时候发生。拆箱一般很明细的，因为要在代码中明确地显示一个强制类型转换。装箱则可能在没有意识的时候发生。如上面代码的第二行。但是，为了一个类型的值调用ToString,Equals或GetHashCode方法时，如果该类型没有覆盖这些方法，也会发生装箱。（**同时，当你调用类型变量值的GetType()方法时，也会伴随着装箱的过程。如果处理为装箱形式的变量，你应该已经知道了具体类型，因此使用typeof替代即可。**）别外，将值作为接口表达式使用时——把它赋值给一个接口类型的变量，或者把它作为接口类型的参数来传递——也会发生装箱。例如，Icomparable x = 5；语句会对5进行装箱。