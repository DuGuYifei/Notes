# toBinaryString

将整数转换为二进制字符串

```java
class Solution {
    public boolean queryString(String s, int n) {
        if(n > 1000) return false;
        for(int i = 1; i <= n; i++){
            String str = Integer.toBinaryString(i);
            if(!s.contains(str)) return false;
        }
        return true;
    }
}
```