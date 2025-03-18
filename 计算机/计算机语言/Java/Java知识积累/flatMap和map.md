# flatMap和map

将map结果重新转换回stream
```java
List e = Arrays.stream(words).map(word->word.split("")).flatMap(Arrays::stream).distinct().collect(toList());
```
