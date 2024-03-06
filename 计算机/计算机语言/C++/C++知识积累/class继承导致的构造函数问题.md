# class继承导致的构造函数问题

[C++子类继承父类时如何写构造函数_aquapisces的博客-CSDN博客_c++ 继承父类的构造函数](https://blog.csdn.net/aquapisces/article/details/104371658)

**构造方法**用来初始化类的对象，与父类的其它成员不同，**它不能被子类继承**（子类可以继承父类所有的成员变量和成员方法，但不继承父类的构造方法）。

因此，在创建子类对象时，为了初始化从父类继承来的数据成员，系统需要调用其父类的构造方法。
如果没有显式的构造函数，编译器会给一个默认的构造函数，并且该默认的构造函数仅仅在没有显式地声明构造函数情况下创建。

构造原则如下：
（注意下面的例子里，父类并没有属性，比如4，父类只是在有参构造函数里放了参数，则没有无参构造函数时，子类需要给这些参数赋值，原因是下3）
1. 如果子类没有定义构造方法，则调用父类的无参数的构造方法。
2. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类自己提供了无参构造函数，则会调用父类自己的无参构造函数。
3. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类只定义了自己的有参构造函数，则会出错（如果父类只有有参数的构造方法，则子类必须显示调用此带参构造方法）。
4. 如果子类调用父类带参数的构造方法，需要用初始化父类成员对象的方式。
5. 子类构造函数不用把父类构造函数的参数全放进去，写函数体时给子类不用的父类属性赋个值就行了。
   
## 例子
1. 如果子类没有定义构造方法，则调用父类的无参数的构造方法。
```cpp
#include <iostream>
using namespace std;
class ar 
{
public:				//不写public会报无法访问private的错误
    ar() 			//父类有无参数构造方法
    {
	    cout << "来了支自动步枪" << endl;
    }
};
class scar :public ar
{				    //子类没有定义构造方法
};
int main()
{
	ar Alice;
	scar Bob;
	return 0;
}
//输出
来了支自动步枪
来了支自动步枪
```


需要注意的是，如果在实例后加了圆括号, 则运行结果为空，但是也不报错：
```cpp
ar Alice();
scar Bob();
```

2. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类自己提供了无参构造函数，则会调用父类自己的无参构造函数。
```cpp
#include <iostream>
using namespace std;
class ar
{
public:
	ar()						//父类有无参数构造方法
	{
		cout << "来了支自动步枪" << endl;
	}
};
class scar :public ar
{
public:				
	scar()					   //子类有无参数构造方法
	{
		cout << "来了把Scar" << endl;
	}
};
int main()
{
	ar Alice;
	scar Bob;
	return 0;
}
//输出
来了支自动步枪
来了支自动步枪
来了把Scar
```
   
3. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类只定义了自己的有参构造函数，则会出错（如果父类只有有参数的构造方法，则子类必须显示调用此带参构造方法）。

正确写法：
```cpp
#include <iostream>
using namespace std;
class ar
{
public:
	ar(int dmg)							//父类有带参数的构造方法
	{
		cout << "来了支自动步枪,单发伤害为"<<dmg << endl;
	}
};
class scar :public ar
{
public:				
	scar(int dmg):ar(dmg)				//子类构造方法带了参数，且显式调用父类的构造方法
	{
		cout << "来了把Scar,单发伤害是"<<dmg << endl;
	}
};
int main()
{
	ar Alice(45);
	scar Bob(42);
	return 0;
}
//输出
来了支自动步枪,单发伤害为45
来了支自动步枪,单发伤害为42			//注意这里是42而不是45哦
来了把Scar,单发伤害是42
```
**注意是先父类输出，后子类输出**

4. 如果子类调用父类带参数的构造方法，需要用初始化父类成员对象的方式。
```cpp
#include <iostream>
using namespace std;
class ar
{
public:
	ar(int dmg)							//父类有带参数的构造方法
	{
		cout << "来了支自动步枪,单发伤害为"<<dmg << endl;
	}
};
class scar :public ar
{
public:				
	scar(int dmg):ar(dmg)				//子类构造方法带参数，且显式调用父类的构造方法
	{
		cout << "来了把Scar,单发伤害是"<<dmg << endl;
		ar(61);							//子类调用父类带参数的构造方法，需要用初始化父类成员对象的方式，且只能在这里调用
	}
};
int main()
{
	ar Alice(45);
	scar Bob(42);
	return 0;
}

//输出
来了支自动步枪,单发伤害为45
来了支自动步枪,单发伤害为42
来了把Scar,单发伤害是42
来了支自动步枪,单发伤害为61
```

5. 子类构造函数不用把父类构造函数的参数全放进去，写函数体时给子类不用的父类属性赋个值就行了。
```cpp
#include <iostream>
using namespace std;
class ar
{
public:
	ar(int dmg, int bullet)					    //父类有带2个参数的构造方法
	{
		cout << "来了支自动步枪,单发伤害为" << dmg;
		cout<<"，一个弹匣有"<<bullet<<"发子弹"<< endl;
	}
};
class scar :public ar
{
public:
	scar(int dmg);							    //声明子类的构造方法，它只带1个参数，可以吗？
};
scar::scar(int dmg) :ar(dmg, 30)				//定义子类构造方法，调用父类的构造方法时把另一个参数赋值
{
	cout << "来了把Scar,单发伤害是" << dmg << endl;
}
int main()
{
	ar Alice(61, 20);
	scar Bob(42);
	return 0;
}
//输出
来了支自动步枪,单发伤害为61，一个弹匣有20发子弹
来了支自动步枪,单发伤害为42，一个弹匣有30发子弹
来了把Scar,单发伤害是42
```

## 复杂案例
```cpp
#include <iostream>
using namespace std;
class ar
{
public:
	ar(int dmg,int bullet)					    //父类有带2个参数的构造方法
	{
		cout << "来了支自动步枪,单发伤害为"<<dmg << endl;
	}
	int v0=880;									//父类设一个成员属性“子弹初速”
};
class scar :public ar
{
public:				
	scar(int dmg);							    //声明子类的构造方法，它只带1个参数哦，可以吗？
	float caliber;								//子类设置个成员属性“口径”
};
scar::scar(int dmg) :ar(dmg, 30)				//定义子类构造方法，显式调用父类的构造方法，没用的父类构造参数给了个值“30”
,caliber(5.56)									//在这儿可以设置子类的成员属性的默认值。
{
	cout << "来了把Scar,单发伤害是" << dmg <<",";
	cout << "口径是" << caliber <<"mm"<< endl;
}
int main()
{
	ar Alice(61,20);
	scar Bob(42,30);
	Bob.v0 = 870;								//修改子类从父类继承的“子弹初速”属性
	cout << "Bob手里的枪子弹初速为" << Bob.v0 << "m/s" << endl;
	return 0;
}

//输出
来了支自动步枪,单发伤害为61
来了支自动步枪,单发伤害为42
来了把Scar,单发伤害是42,口径是5.56mm
Bob手里的枪子弹初速为870m/s
```