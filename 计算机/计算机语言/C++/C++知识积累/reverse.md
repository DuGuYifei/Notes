# reverse

反转一个容器的元素

```cpp
#include <algorithm>

template <typename T>
void reverse(T &container)
{
	std::reverse(container.begin(), container.end());
}
```

string也行



