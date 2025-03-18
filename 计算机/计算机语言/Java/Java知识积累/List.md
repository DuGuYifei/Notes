# List


1. [两种List](#两种list)
   1. [awt.List](#awtlist)
2. [初始化](#初始化)
3. [List 和 ArrayList](#list-和-arraylist)
4. [遍历](#遍历)
5. [list.subList(from, to)](#listsublistfrom-to)
6. [list.contains(x)](#listcontainsx)
7. [Remove](#remove)
8. [list.removeAll(collection\<?\> c) 和 clear()](#listremoveallcollection-c-和-clear)
9. [list.toArray()](#listtoarray)


## 两种List
```java
import java.util.List;
import java.awt.List;
```

### awt.List
`getRows` 获取行数，即长度


## 初始化
[java-List集合初始化的几种方式与一些常用操作-持续更新_瑶山的博客-CSDN博客_初始化list](https://blog.csdn.net/qq_44695727/article/details/106517147)

* 常见

```java
List<String> languages = new ArrayList<>();
languages.add("Java");
languages.add("List");
languages.add("ArrayList");

static List<String> list = new ArrayList<String>() {
    { // 这个大括号 就是 构造代码块 会在构造函数前 调用
        this.add("11"); //this 可以省略
        add("21");
        add("31");
        add(str);
    }
};
```

* 下面呢的方法创建的是**不可变**
```java
List<String> list = Arrays.asList("Java", "Jdk", "Jre");
List<String> list2 = Collections.nCopies(3, "apple");
```

* 想要**可变**，封装一下
```java
List<String> list = new ArrayList<>(Arrays.asList("1", "2", "3"));
List<String> dogs = new ArrayList<>(Collections.nCopies(3, "dog"));
```

## List 和 ArrayList
[List和ArrayList的对比](List和ArrayList的对比.md)

上面的有泛型，下面的没有


## 遍历
1. 利用 for 遍历
```java
for(inti=0;i<list.size();i++){
    System.out.print(list.get(i)+", ");
}
```

2. 利用 foreach 循环
```java
for(inti:list){
    System.out.print(i+", ");
}
```

3. 使用 -> 的 lambda 表达式遍历数组
```java
list.forEach(i->System.out.print(i+", "))
```

4. 使用 :: 的 lambda 表达式遍历数组
```java
list.forEach(System.out::println);
```

## list.subList(from, to)
报错：(fromIndex < 0 || toIndex > size || fromIndex > toIndex)

## list.contains(x)
`String str1 = new String("sd");`

创建了两个内容相同的String对象：str1和str2，将str1存入了集合list中。

**这两个对象不是同一个对象，所以“str1==str2”输出的结果是false。但是通过“list.contains(str2)”判断集合中是否包含str2时，返回的却是true。**

## Remove
1. `Remove(int i);` 根据下标删除
2. `Remove(对象 i);` 比如 Integer i 就是一个int对象。

## list.removeAll(collection<?> c) 和 clear()
* clear是删除Collection对象中的所有元素，即清空Collection对象。
* removeAll是删除所有c里的对象。

## list.toArray()
* `toArray()` 返回一个Object数组
* `toArray(T[] a)` 返回一个T类型的数组
```java
res.toArray(new Integer[res.size()])l; // 只能Integer，不能int，且不能隐式转换int[]

return res.stream().mapToInt(Integer::valueOf).toArray();
```