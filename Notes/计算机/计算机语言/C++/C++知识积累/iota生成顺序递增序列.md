# iota生成顺序递增序列

```c++
#include <numeric>

vector<int> a(3);
std::iota(a.begin(),a.end(),0); // 生成从0开始的单调递增1向量

```


```cpp
std::iota(v.begin(),v.end(),-2.5);  //从-2.5开始每次加1
std::iota(v.begin(),v.end(),"iota");//iota,ota,ta,a(数量根据v的长度，超过4也只会到a结束，然后输出空格)
```