# pair<int,int>

如果没用就`#include <utility>`

## auto[a,b]对pair函数返回值

Structured binding declaration (since C++17)
所以vs studio里面要在工程文件右键属性，c/c++里修改版本

```c++
auto [left1, right1] = TwoSides(s, i, i);
auto [left2, right2] = TwoSides(s, i, i + 1);

pair<int, int> TwoSides(string s, int left, int right){};
```

如上例，left1,right1 经VS Studio监视变量，类型是`int&&`。

## 声明
```cpp
    pair<int,int> board[26] =
    {
        {0,0},{0,1},{0,2},{0,3},{0,4},
        {1,0},{1,1},{1,2},{1,3},{1,4},
        {2,0},{2,1},{2,2},{2,3},{2,4},
        {3,0},{3,1},{3,2},{3,3},{3,4},
        {4,0},{4,1},{4,2},{4,3},{4,4},
        {5,0}
    };

    pair<int, int> adjs[4] = {make_pair(current_node.first-1, current_node.second), ...};
```