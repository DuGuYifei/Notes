# minmax_element

```cpp
#include <algorithm>

// 这个不一定行：auto [mini, maxi] = minmax_element(nums.begin(), nums.end());
auto minmax = minmax_element(nums.begin(), nums.end());
int diff = *minmax.second - *minmax.first;
```