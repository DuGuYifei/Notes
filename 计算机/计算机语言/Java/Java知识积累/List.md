# List

## Remove
1. `Remove(int i);` 根据下标删除
2. `Remove(对象 i);` 比如 Integer i 就是一个int对象。


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

## List 和 ArrayList
[List和ArrayList](List和ArrayList.md)

## list.subList(from, to)
报错：(fromIndex < 0 || toIndex > size || fromIndex > toIndex)

## list.contains(x)
`String str1 = new String("sd");`

创建了两个内容相同的String对象：str1和str2，将str1存入了集合list中。

**这两个对象不是同一个对象，所以“str1==str2”输出的结果是false。但是通过“list.contains(str2)”判断集合中是否包含str2时，返回的却是true。**

