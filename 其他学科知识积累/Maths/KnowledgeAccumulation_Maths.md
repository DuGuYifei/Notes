# Maths 知识积累

## 2021-12-30

LeetCode 507.完美数

根据欧几里得-欧拉定理，每个偶完全数都可以写成：

$2^{p-1}(2^p-1)$

## 2022-2-9
欧几里得最大公约数
```cpp
int gcd(int a, int b){
    if (b == 0) return a;
    return gcd(b,a%b);
}
```
证明：
[公约数](https://blog.csdn.net/qq_25847123/article/details/95753295)
