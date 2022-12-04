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