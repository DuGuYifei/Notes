# Comparable泛型接口_compareTo

## 返回：
负整数、零或正整数，因为此对象小于、等于或大于指定对象。


## 增加CompareTo函数支持比较器

`PriorityQueue<Tuple<AID>>`:
```java
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode
@ToString
public class Tuple<X> implements Comparable<Tuple<X>>{
    private X x;
    private Integer y;
    private Integer z;

    @Override
    public int compareTo(Tuple<X> o) {
        return this.getY().equals(o.getY()) ? o.getZ() - this.getZ() : this.getY() - o.getY();
    }
}
```

