# double
`1e-10` 10^(-10)

double 类型只能保证 15 位有效数字是精确的。为了避免计算带来的误差，我们将不等式  的右边加上 10^-10，从而防止不等式两边数值相等却被判定为大于的情况。

作者：LeetCode-Solution
链接：https://leetcode.cn/problems/subarray-product-less-than-k/solution/cheng-ji-xiao-yu-k-de-zi-shu-zu-by-leetc-92wl/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

```cpp
// logs[i+1]-logs[l] + 1e-10 < logk
// logs[l] > logs[i+1] - logk + 1e-10
```