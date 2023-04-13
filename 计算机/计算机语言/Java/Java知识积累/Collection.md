# Collection

## col.toArray()
转为数组

## Collections.binarySearch

[binarySearch](binarySearch.md)

## Collections.nCopies

```java
List<String> list = new ArrayList(Collections.nCopies(10, "hello"));
```

不会额外占用空间，它的返回值直接就是List，只不过是一个不可变的List，它的大小是10，而且它的每个元素都是"hello"。如果你试图修改这个List，那么会抛出UnsupportedOperationException异常。