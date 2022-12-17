# explicit

explicit关键字只能用于修饰只有一个参数的类构造函数或者其他参数存在默认值, 它的作用是表明该构造函数是**显式的**, 而非隐式的, 

跟它相对应的另一个关键字是implicit, 意思是隐藏的,类构造函数默认情况下即声明为implicit(隐式).

比如:
```c++
#include <iostream>
#include <string>
 
using namespace std;
 
class Book
{
public:
	Book(){}
	Book(const string name, const int price = 100) : _name(name), _price(price){
		cout << "构造函数调用！" << endl;;
	};
 
	void IsSameBook(const Book & book)
	{
		if (_name == book._name)
			cout << "两本书重名！" << endl;
		else
			cout << "两本书不重名！" << endl;
	}
private:
	string _name;
	int _price;
};
 
void main()
{
	Book A("AA");	
	A.IsSameBook(string("AA"));	
	system("Pause");
}

输出：
构造函数调用！
构造函数调用！
两本书重名！
```

* 构造函数加上explicit关键字之后，使用`A.IsSameBook(string("AA"))`的写法，编译器会报错。explicit的作用就是防止其他类型对该类类型的隐式转换，但仍可以以显示转换的方式调用， 如` Book B=Book("AA")`的写法。

```c++
#include <iostream>
#include <string>
 
using namespace std;
 
class Book
{
public:
	Book(){}
	explicit Book(const string name, const int price = 100) : _name(name), _price(price){
		cout << "构造函数调用！" << endl;;
	};
 
	void IsSameBook(const Book & book)
	{
		if (_name == book._name)
			cout << "两本书重名！" << endl;
		else
			cout << "两本书不重名！" << endl;
	}
private:
	string _name;
	int _price;
};
 
void main()
{
	Book A("AA");	
	Book B = Book("AA");
	A.IsSameBook(B);	
	system("Pause");
}
```