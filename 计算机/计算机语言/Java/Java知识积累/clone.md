# clone

`clone()`方法是`Object`类中的一个方法，它的作用是创建并返回此对象的一个副本。`clone()` 深拷贝

但也不是默认深拷贝，如果里面有Object，还是会浅拷贝。

并且clone()在Object源码里是`protected`, `native`。protected意味着只有同一个包的子类可以调用[protected子类访问](protected%E5%AD%90%E7%B1%BB%E8%AE%BF%E9%97%AE.md)，native意味着是本地方法，也就是说它的实现是在本地的，而不是在java代码中的。

所以要重写一次这样允许子类调用。

如果没有` implements Cloneable `，会抛出`CloneNotSupportedException`。

下面案例就说明了前拷贝问题，Test类确实被改地址了，但是类里面的Object修改后两个实例都会修改:
```
输出：
Test@726f3b58
Test@368102c8
a
b
b
```

```java
public class MyClass {
    public static void main(String args[]) {
        Test a = new Test();
        
        try{
            Test b = (Test) a.clone();
            System.out.println(a);
            System.out.println(b);
            System.out.println(a.a.a);
            b.a.a = "b";
            System.out.println(a.a.a);
            System.out.println(b.a.a);
        } catch(Exception e){
            System.out.println(e);
        }
    }
}

public class Test implements Cloneable{
    public Child a = new Child();
    @Override
	protected Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
}

public class Child {
    String a = "a";
}
```

为了实现深拷贝，需要在clone()里面重写，否则哪怕你把Child类也加一个clone()，Clonable也没用。
无效：
```java
public class Child implements Cloneable{
    String a = "a";
    @Override
	protected Object clone() throws CloneNotSupportedException {
	    Child nc = new Child();
		return nc;
		// return super.clone(); 也无效
	}
}
```
比如：
```java
  @Override
  public Object clone() {
    Website clonedWebsite = null;
    try {
      clonedWebsite = (Website) super.clone();
    } catch (CloneNotSupportedException e) {
      e.printStackTrace();
    }
    clonedWebsite.setId(
        new UUID(
            this.getId().getMostSignificantBits(),
            this.getId().getLeastSignificantBits()));
    clonedWebsite.setUser(
        this.getUser());
    clonedWebsite.setCreatedAt(new Date(this.getCreatedAt().getTime()));
    clonedWebsite.setUpdatedAt(new Date(this.getUpdatedAt().getTime()));
    clonedWebsite.setDisplayName(new String(this.getDisplayName()));
    clonedWebsite.setRedirectUrl(new String(this.getRedirectUrl()));
    clonedWebsite.setPrivateKey(new String(this.getPrivateKey()));
    clonedWebsite.setIsActive(new Boolean(this.getIsActive()));
    return clonedWebsite;
  }
```