# @Singular

## 讲解
* 作用于集合字段，需要配合 @Builder 使用
* 使用 @Singular 注解一个集合字段（如果没有指定 value 属性值，那么集合字段名需要是复数形式），会生成两个添加元素方法
  * 一个向集合添加单个元素（方法名：集合字段名的单数形式 / value 属性值）
  * 一个将另一个集合的所有元素添加到集合中（方法名：集合字段名）
* 还生成了 clear 方法（方法名：clear + 集合字段名，驼峰命名）。 这些 singular 构建器相对而言是有些复杂的，主要是来保证以下特性：
  * 在调用 build 方法时，生成的集合是不可变的
  * 在调用 build 方法之后调用其中一个添加元素方法或 clear 方法不会修改任何已经生成的对象。如果对集合修改之后，再调用 build 方法，则会创建一个基于上一个对象创建的对象实体
  * 生成的集合将被压缩到最小的可行格式，同时保持高效
* @Singular 只能应用于 lombok 已知的集合类型。目前，支持的类型有：
  * Iterable、Collection、List (一般情况下，生成的不可修改的 ArrayList)
  * Set、SortedSet、NavigableSet (一般情况下，生成可变大小不可修改的 HashSet 或者 TreeSet)
  * Map、SortedMap、NavigableMap (一般情况下，生成可变大小不可修改的 HashMap 或者 TreeMap)
* 在调用 build 方法来创建实例对象时， 并没有直接使用 Collections.unmodifiableList(Collection c) 此方法来创建实例，而是分为三种情况
  * 第一种，当集合中没有元素时，创建一个空集合
  * 第二种，当集合中存在一个元素时，创建一个不可变的单元素集合
  * 第三种，根据当前集合的元素数量创建对应合适大小的集合

## 案例

### 实际代码
```Java
@Builder
public class User {
    private String username;
    private String password;
    @Singular
    private List<String> sixties;
	
	public static void main(String[] args) {
	    User.builder().sixty("").build()
	}
}
```

### 编译后
````Java
public class User {
    private String username;
    private String password;
    private List<String> sixties;
    
    User(String username, String password, List<String> sixties) {
        this.username = username;
        this.password = password;
        this.sixties= sixties;
    }
	
    public static User.UserBuilder builder() {
    	return new User.UserBuilder();
    }
	
    public static class UserBuilder {
        private String username;
        private String password;
        private ArrayList<String> sixties;
        
        UserBuilder() {}
        
        public User.UserBuilder username(String username) {
        	this.username = username;
        	return this;
        }
        
        public User.UserBuilder password(String password) {
        	this.password = password;
        	return this;
        }
		
        public User.UserBuilder sixty(String sixty) {
            if (this.sixties == null) {
                this.sixties = new ArrayList();
            }
            this.sixties.add(sixty);
            return this;
        }
		
        public User.UserBuilder sixties(Collection<? extends String> sixties) {
            if (this.sixties == null) {
                this.sixties = new ArrayList();
            }
            this.sixties.addAll(sixties);
            return this;
        }
		
        public User.UserBuilder clearSixties() {
            if (this.sixties != null) {
                this.sixties .clear();
            }
            return this;
        }
		
        public User build() {
            List sixties;
            switch(this.sixties == null ? 0 : this.sixties.size()) {
	            case 0:
	                sixties = Collections.emptyList();
	                break;
	            case 1:
	                sixties = Collections.singletonList(this.sixties.get(0));
	                break;
	            default:
	                sixties = Collections.unmodifiableList(new ArrayList(this.sixties));
            }
            return new User(this.username, this.password, sixties);
        }
        
		public String toString() {
            return "User.UserBuilder(username=" + this.username + ", password=" + this.password + ", sixties" + this.sixties + ")";
        }
    }
}

```