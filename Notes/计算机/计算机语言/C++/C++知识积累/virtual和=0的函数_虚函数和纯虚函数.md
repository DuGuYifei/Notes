# virtual和=0的函数

* 定义一个函数为虚函数，不代表函数为不被实现的函数。
* 定义他为虚函数是为了允许用基类的指针来调用子类的这个函数。
* 定义一个函数为纯虚函数，才代表函数没有被实现。
* 定义纯虚函数是为了实现一个接口，起到一个规范的作用，规范继承这个类的程序员必须实现这个函数。

`virtual void funtion1()=0;` 纯虚函数**一定没有定义**，纯虚函数用来规范派生类的行为，即接口。包含纯虚函数的类是抽象类，抽象类不能定义实例，但可以声明指向实现该抽象类的具体类的指针或引用。

`virtual ReturnType FunctionName(Parameter);` 虚函数必须实现，如果不实现，编译器将报错


[继承重写函数调用问题](继承重写函数调用问题.md)

```cpp
#pragma once

using namespace std;

//父类
class Parent{
public:
	void parent_method() {
		cout << " Parent parent_method " << endl;
	}

	//虚函数
	virtual void virtual_method() {
		cout << " Parent virtual_method " << endl;
	}

	//纯虚函数 , 类似于 Java 的抽象方法 , 
	//父类中声明后 , 该方法必须实现 , 否则编译时报错
	virtual void pure_virtual_method() = 0;
};

//父类
class Parent1 {
public:
	void parent_method() {
		cout << " Parent1 parent_method " << endl;
	}

	void parent_method1() {
		cout << " Parent1 parent_method1 " << endl;
	}
};

//子类
//继承父类 Parent
//继承作用域 : 默认私有继承 private 
class Child : public Parent, public Parent1 {
public:
	void parent_method() {
		//子类中调用父类的方法 , 该操作相当于 Java 中的 super 方法 
		Parent::parent_method();
		Parent1::parent_method();

		cout << " Child parent_method " << endl;
	}

	//重写父类的虚函数
	void virtual_method() {
		cout << " Child virtual_method " << endl;
	}

	//实现纯虚函数方法 , 该方法必须实现 , 否则会报错
	void pure_virtual_method() {
		cout << " Child pure_virtual_method " << endl;
	}
};
```