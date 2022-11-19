# IoC_DI_DL

## IoC
IoC: Inversion of Control 中文通常翻译为“控制反转”。是Spring框架的核心。

控制反转实现方式一般有两种:
* DI: 依赖注入（Dependency Injection，简称DI）
* DL：依赖查找（Dependency Lookup）。

1. 最原始的依赖1.0方式：
创建一个“天猫”的商场类TMallMarket代码如下。该类提供了一个buy方法，可以从repertory中获取商品。
```java
import java.util.HashMap;
import java.util.Map;
 
public class TMallMarket {
	
	private static Map<String, Object> repertory = new HashMap<String, Object>();
	static{
		repertory.put("IPhone6s", "IPhone6s");
		repertory.put("Mi4", "Mi4");
		repertory.put("Milk", "milks");
	}
 
	public Object buy(String string) {
		
		Object object = repertory.get(string);
		
		return object;
	}

}
```

然后在创建一个人的类People代码如下。该类拥有一个TMallMarket 的成员变量。也有一个buy方法，可以通过TMallMarket 的buy方法来获取商品。这里需要注意的是，在People初始化的构造函数中创建了TMallMarket 的对象。
```java
public class People {
 
	private TMallMarket iMarket;
 
	public People() {
		iMarket = new TMallMarket();
	}
 
	public Object buy(String goods) {
 
		Object object = null;
		object = iMarket.buy(goods);
 
		return object;
	}
 
}
```
下面创建我们的测试类MainTest。通过构建People对象，调用buy方法就可以从TMallMarket 商场购买想要的商品了。但是这里我们提出一个问题，如果我现在这个想从京东上买东西,该怎么办呢？这样就会很麻烦了，添加一个京东的商场还不行，还得重新构造People类。这样的话就很麻烦了，下面我们进入接口实现方式的依赖2.0版本。
```java
public class MainTest {
	
	public static void main(String[] args) {
		
		/*最原始的方式*/
		People people = new People();
		Object object =  people.buy("Mi4");
		System.out.println(object);
		
	}
 
}
```
2. 用接口依赖的2.0方式：
```java
public interface IMarket {
 
	Object buy(String string);
 
}
------------------------------
import java.util.HashMap;
import java.util.Map;
 
public class TMallMarket implements IMarket{
	
	private static Map<String, Object> repertory = new HashMap<String, Object>();
	static{
		repertory.put("IPhone6s", "IPhone6s");
		repertory.put("Mi4", "Mi4");
		repertory.put("Milk", "milks");
	}
 
	public Object buy(String string) {
		
		Object object = repertory.get(string);
		
		return object;
	}
 
}
------------------------------
public class People {
 
	private IMarket iMarket;
 
	public People(IMarket iMarket) {
		this.iMarket = iMarket;
	}
 
	public Object buy(String goods) {
 
		Object object = null;
		object = iMarket.buy(goods);
 
		return object;
	}
 
}
-------------------------------
public class MainTest {
	
	public static void main(String[] args) {
		
		/*接口实现依赖方式*/
		IMarket iMarket = new TMallMarket();
		People people = new People(iMarket);
		Object object =  people.buy("Mi4");
		System.out.println(object);
		
	}
 
}
```

3. 进入依赖的3.0模式即IOC：
在IOC的案例中People、IMarket、TMallMarket 三个类没有改变和依赖2.0版本的一样。首先创建自己的**IOC容器**代码如下。在MyIOC中有一个people 的成员变量用来存放初始化容器时存放对象。startMyIOC方法相当于**启动一个IOC容器**，**根据转入的name参数来选择为 people 对象注入哪个市场**。getPeoPle获得我们想要好的 people 对象。
（★注意：方法中有需要传入一个name参数，这里应该是一个可以灵活配置的文件。根据你的配置来选择为People对象注入那个市场。这里为了演示的简单能够直观的展示IOC的特点，使用转入一个name来替代读入文件的方式）

```java
public class MyIOC {	
	public static People people = null;
	
	public void startMyIOC(String name){
		
		if ("TMallMarket".equals(name)) {
			people = new People(new TMallMarket());
		} else if ("JingDongMarket".equals(name)) {
			people = new People(new JingDongMarket());
		}
		
	}
	
	public Object getPeople() {
		return people;
	}
 
}
```

接下来在我们的测试类中看一看是如何使用我们自己定义的IOC。很明显，这种方式和我们演示spring的helloworld的时候是很相似的。看起来更加清楚，先初始化容器，在通过容器获取你需要的对象，然后使用对象。

在这个案例中，我们将People与IMarket匹配的事情，也就是相互依赖的关系完全的交给了MyIOC来处理。这就是IOC控制反转的核心，将相互的依赖（控制）进行了反转。初次看起来好像和依赖2.0的接口没有谁什么区别，是因为我们这里案例比较简单实现的也不完善。当我开始深入接触spring之后就会感受到IOC的强大。

```java
public class MainTest {
	
	public static void main(String[] args) {
		
		/*IOC实现的依赖关系*/
		//初始化IOC容器。
		MyIOC myIOC = new MyIOC();
		myIOC.startMyIOC("TMallMarket");
		//通过IOC容器获取对象和使用对象。
		People people = (People) myIOC.getPeople();
		System.out.println(people.buy("Mi4"));
	}
 
}
```

### DI
#### 真实使用
[@Autowired](@Autowired.md)

#### 真实使用讲解：
1. 构造注入
```java
public class UserService {
 private UserRepository repository;
 public UserService(UserRepository repository) {
 this.repository = repository;
 }
}
----------------------------------------
UserRepository repository = //create notifier
UserService service = new UserService(repository);
```
使用构造函数注入：
* 可以在一步中创建
* 构造和注入不可变对象（没有 setter 和 final 字段）。

2. setter注入
```java
public class UserService {
 private UserRepository repository;
 public void setRepository(UserRepository repository) {
 this.repository = repository;
 }
}
-----------------------------
UserService service = new UserService();
UserRepository repository = //create notifier
service.setRepository(repository);
```
使用 setters 注入：
* 存在默认构造函数，
* 注入后可以替换依赖项，
* 需要 setters（没有带有 final 字段的不可变对象）

3. field注入
```java
public class UserService {
 private UserRepository repository;
}
-----------------------------
UserService service = new UserService();
Field field = service.getClass().getDeclaredField("repository");
field.setAccessible(true);
UserRepository repository = //create notifier
field.set(service, repository);
```
字段注入：
* 不需要额外的方法，
* 需要反射机制

#### 讲解：

1. 构造方法注入
   ```java
   	public void startMyIOC(String name){
		
		if ("TMallMarket".equals(name)) {
			people = new People(new TMallMarket());
		} else if ("JingDongMarket".equals(name)) {
			people = new People(new JingDongMarket());
		}
		
	}
    ```
2. stter和getter方法注入
    ```java
 
    public class People {
    
    	private IMarket iMarket;
    
    	public People() {
    		// TODO Auto-generated constructor stub
    	}
    
    	public People(IMarket iMarket) {
    		this.iMarket = iMarket;
    	}
    
    	public IMarket getiMarket() {
    		return iMarket;
    	}
    
    	public void setiMarket(IMarket iMarket) {
    		this.iMarket = iMarket;
    	}
    
    	public Object buy(String goods) {
        
    		Object object = null;
    		object = iMarket.buy(goods);
    
    		return object;
    	}
    
    }
    ```
    MyIOC新加的方法如下所示。创建people 对象后通过setiMarket方法注入相应的依赖。这里只是简单的介绍了以下两种注入的方式，还有一种接口注入由于其侵入性较强已不怎么使用。

    关于构造注入的优点，在于创建对象的同时，所有的依赖都会同时创建完成可以马上使用。但是当依赖较多时构造方法的参数列表可能较长，而且构造方法不能被继承无法设置默认值。

    对于stter和getter注入，其依赖的对象可以延后注入，在创建完对象后不能立即使用。但是stter和getter方法可以被继承，其依赖对象注入的时机也可以灵活选择。综合来说这种方式在一般情况下是最可取的。在spring可以更加清晰的了解这些注入方式的作用和效果这里就不再多讲了。
    ```java
    	public void startMyIOCByStter(String name){
		
		if ("TMallMarket".equals(name)) {
			people = new People();
			people.setiMarket(new TMallMarket());
		} else if ("JingDongMarket".equals(name)) {
			people = new People();
			people.setiMarket(new JingDongMarket());
		}
		
	}
    ```
3. field注入