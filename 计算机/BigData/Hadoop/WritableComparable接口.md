# WritableComparable接口


## private字段和write，readFields方法顺序
在实现 WritableComparable 接口的类中，字段可以是 public、protected 或 private 修饰的，这与普通的 Java 类的规则相同。

但是，需要注意的是，如果字段是 public 或 protected 修饰的，则在序列化和反序列化时，可能会受到访问权限的限制，从而导致序列化或反序列化失败。因此，为了避免这种情况，通常建议将字段设置为 private，并提供对应的 getter 和 setter 方法来读取和设置字段的值。

此外，在实现 WritableComparable 接口时，字段的顺序和类型必须与 write() 和 readFields() 方法中写入和读取的顺序和类型一致，否则会导致序列化和反序列化失败。

## 为什么要使用WritableComparable接口

在 MapReduce 中，输入数据和中间数据的类型必须是可序列化的（serializable）和可比较的（comparable），这样才能在分布式环境下进行传输和排序。在 Hadoop 中，Writable 接口就是为此而设计的，因为它是可序列化的和可比较的。

* 有些比如Long，本身就有Comparable，所以只需要Writable接口
* 没有的就都需要，使用WritableComparable接口

## WritableComparable接口的源码

```java
@InterfaceAudience.Public
@InterfaceStability.Stable
public interface WritableComparable<T> extends Writable, Comparable<T> {
}
```

## Writable实现
```java
public class Person implements Writable {
    private String name;
    private int age;
    
    public Person() {}
    
    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }
    
    public void readFields(DataInput in) throws IOException {
        this.name = in.readUTF();
        this.age = in.readInt();
    }
    
    public void write(DataOutput out) throws IOException {
        out.writeUTF(name);
        out.writeInt(age);
    }
    
    public String getName() {
        return name;
    }
    
    public int getAge() {
        return age;
    }
}
```

## Comparable实现
```java
public class Person implements Comparable<Person>{
    private int age;
    private String name;

    public Person(int age, String name) {
        this.age = age;
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public String getName() {
        return name;
    }

    @Override
    public int compareTo(Person other) {
        //按年龄升序排列
        return Integer.compare(this.age, other.age);
    }

    @Override
    public String toString() {
        return "Person{" +
                "age=" + age +
                ", name='" + name + '\'' +
                '}';
    }
}
```

## WritableComparable实现
hashCode不一定要，但是equals一定要，因为java规定，如果两个对象equals，那么他们的hashCode一定要相等

```java
package mapreduce;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import org.apache.hadoop.io.WritableComparable;

public class VisitorTuple implements WritableComparable<VisitorTuple> {

	private String firstName = "";
	private String midName = "";
	private String lastName = "";
	
	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		if(firstName != null) this.firstName = firstName;
		else this.firstName = "";
	}

	public String getMidName() {	
		return midName;
	}

	public void setMidName(String midName) {
		if(midName != null) this.midName = midName;
		else this.midName = "";			
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		if(lastName != null) this.lastName = lastName;
		else this.lastName = "";					
	}

	public void write(DataOutput out) throws IOException {
		out.writeUTF(firstName);
		out.writeUTF(midName);
		out.writeUTF(lastName);		
	}

	public void readFields(DataInput in) throws IOException {
		firstName = in.readUTF();
		midName = in.readUTF();
		lastName = in.readUTF();
	}

	@Override
	public int hashCode() {
        int result = 17;
        result = 31 * result + firstName.hashCode();
        result = 31 * result + lastName.hashCode();
        result = 31 * result + midName.hashCode();
        return result;		
	}

	@Override
	public boolean equals(Object o) {
        if (!(o instanceof VisitorTuple)) return false;        
        VisitorTuple visitor = (VisitorTuple) o;

        return visitor.firstName.equals(firstName) &&
        		visitor.midName.equals(midName) &&
        		visitor.lastName.equals(lastName);
	}

	@Override
	public String toString() {
		return firstName + " " + midName + " " + lastName;
	}

	public int compareTo(VisitorTuple v) {
		int last = lastName.compareTo(v.lastName);
		if(last!=0) return last;
		int first = firstName.compareTo(v.firstName);
		if(first!=0) return first;		
		return midName.compareTo(v.midName);
	}
	
}
```
