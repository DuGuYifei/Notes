# HashMap_HashTable_Dictionary

## Dictionary
过时了，仍然保留只是为了向后兼容。

## HashMap
## Integer int
只能用Integer不能用int，初步估计只能用object

### put, replace
使用replace来更新比put更安全

### putIfAbsent
```java
for(int[]i:logs){
    hmap.putIfAbsent(i[0], new HashSet<>());
    hmap.get(i[0]).add(i[1]);
}
```

## 遍历
```java
// Variable used in lambda expression should be final or effectively final
AtomicInteger totalGold = new AtomicInteger();
goldMap.forEach((k, v) -> totalGold.addAndGet(v.getGold()));

hm.forEach((k,v)->{
    if((v & (v - 1)) > 0)
        ans.add(k);
});

hm.entrySet().forEach(v -> ans.add(v.getKey() + v.getValue()));

for (Map.Entry<Object,Object> entry: map.entrySet()) {
    System.out.println("key:" + entry.getKey() + ",vaule:" + entry.getValue());
}

Iterator<Map.Entry<Object, Object>> iterator = map.entrySet().iterator();
while (iterator.hasNext()) {
    Map.Entry<Object, Object> entry = iterator.next();
    System.out.println("key:" + entry.getKey() + ",vaule:" +entry.getValue());
}
```