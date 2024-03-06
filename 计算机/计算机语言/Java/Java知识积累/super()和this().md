# super()和this()

java的super()和this()都必须在构造函数的第一行，所以不能同时出现。

## super7=
```java
public class Test {
	public static void main(String[] args) {
		new Child();
	}
}

class Parent {
	public Parent() {
		System.out.println("Parent");
	}
}

class Child extends Parent {
	public Child() {
		super(); // 调用父类构造函数
		System.out.println("Child");
	}
}
```

输出：

```
Parent
Child
```

## this()

```java
public class Test {
	public static void main(String[] args) {
		new Child();
	}
}

class Parent {
	public Parent() {
		System.out.println("Parent");
	}
}

class Child extends Parent {
	public Child() {
		this("ChildXXD"); // 调用本类构造函数
		System.out.println("Child");
	}
	
	public Child(String s) {
		System.out.println(s);
	}
}
```

输出：

```
ChildXXD
Child
```