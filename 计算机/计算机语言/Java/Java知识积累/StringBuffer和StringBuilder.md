# StringBuffer和StringBuilder

* String 是不可变的，而 StringBuffer 和 StringBuilder 是可变类。
* 字符串连接运算符 (+) 在内部使用 StringBuilder 类。
* 线程
  * StringBuffer 是线程安全和同步的（[线程锁](线程锁.md)），而 StringBuilder 不是。 
    * 快 - StringBuilder
    * 慢 - StringBuffer
  * 单线程 - StringBuilder
  * 多线程 - StringBuffer。


## StringBuilder
```java
StringBuilder ans = new StringBuilder();
ans.append(word2.substring(id2));
ans.append(word1.charAt(id1));
return ans.toString();
```

### 清空
`sb.setLength(0)`

### reverse反转
`sb.reverse()`