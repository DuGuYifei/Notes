# Maths 知识积累

1. [欧几里得-欧拉定理 偶数](#欧几里得-欧拉定理-偶数)
2. [欧几里得最大公约数](#欧几里得最大公约数)
3. [二项式定理 和 组合C的N项和](#二项式定理-和-组合c的n项和)


## 欧几里得-欧拉定理 偶数

LeetCode 507.完美数

根据欧几里得-欧拉定理，每个偶完全数都可以写成：

$2^{p-1}(2^p-1)$

## 欧几里得最大公约数
欧几里得最大公约数
```cpp
int gcd(int a, int b){
    if (b == 0) return a;
    return gcd(b,a%b);
}
```

```java
    public int gcd(int num1, int num2) {
        while (num2 != 0) {
            int temp = num1;
            num1 = num2;
            num2 = temp % num2;
        }
        return num1;
    }
```

证明：
[公约数](https://blog.csdn.net/qq_25847123/article/details/95753295)

## 二项式定理 和 组合C的N项和
二项式定理：
$(a+b)^n = C_n^0a^{n} + C_n^1a^{n-1}b + ... + C_n^ka^{n-k}b^k +...+ C_n^nb^n$

组合N项和
$C_n^0 + C_n^1 + ... + C_n^n = (1+1)^n = 2^n$
$C_n^0=1$

