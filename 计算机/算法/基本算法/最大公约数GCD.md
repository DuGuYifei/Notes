# 最大公约数 GCD
欧几里得最大公约数
```cpp
int gcd(int a, int b){
    if (b == 0) return a;
    return gcd(b,a%b);
}
```