# Set_HashSet_TreeSet


## 比较
* Set: 是接口存取无序，元素唯一
* HashSet: Set接口实现的类，存取无序，元素唯一，底层是 HashMap
* LinkedHashSet：直接父类是 HashSet,不排序但存取有序，存储的元素不能重复。
* TreeSet：元素唯一，更重要的一个是给元素进行排序，底层是 TreeMap（红黑树）

## Set
### first, last
```java
int left = seats.first();
int right = n - 1 - seats.last();
```

### higher lower
`seats.higher(top[0]) == top[1]`
`int prev =seats.lower(p), next = seats.higher(p)`