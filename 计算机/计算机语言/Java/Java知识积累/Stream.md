# Stream

## map和flatMap
[map和flatMap](flatMap和map.md)

## Stream.distinct()
去重

## Stream.collect()
`.collect(Collectors.toList())` 将stream整合为list
```java
List<Integer> numbers = Arrays.asList(3, 2, 2, 3, 7, 3, 5);

// 获取对应的平方数

List<Integer> squaresList = numbers.stream().map( i -> i*i).distinct().collect(Collectors.toList());
```

