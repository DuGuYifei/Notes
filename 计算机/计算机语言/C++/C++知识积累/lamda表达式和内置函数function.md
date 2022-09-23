# lambda表达式和内置函数function
这种方法不如分开写函数快

`[]()->int{}`

-   `[]`里放捕获列表 (例2)，可以省略 [传值的两种用法速度](#[]两种用法速度)

    -   []表示不捕获任何变量
    -   [var]表示值传递方式捕获变量var
    -   [=]表示值传递方式捕获所有父作用域的变量（包括this） (例4)
    -   [&]表示引用传递方式捕捉所有父作用域的变量（包括this）(例4，5)
    -   [&var]表示引用传递捕捉变量var
    -   [this]表示值传递方式捕捉当前的this指针
    -   [=, &] 拷贝与引用混合
        -   [=, &a, &b]表示以引用传递的方式捕捉变量a和b，以值传递方式捕捉其它所有变量。
    - [&, a, this]表示以值传递的方式捕捉变量a和this，引用传递方式捕捉其它所有变量。
    ```cpp
     static constexpr auto tri_hash = [fn = hash<int>()](const tuple<int, int, int>& o) -> size_t {
        auto&& [x, y, z] = o;
        return (fn(x) << 24) ^ (fn(y) << 8) ^ fn(z);
    };
    ```

-   `()`里放的是参数 (用的是[]里传入的参数)

-   `->int`表明返回值是int，可省略，即使有返回值也可以省略(对速度影响不大，尽量省略)

-   `{}`里放的是函数体

有时候要给它一个`function`不然没有办法递归(recursion)自身，会报错：“auto说明符的变量不能出现在自身”
- `function<void(int a)>`
- `#include <functional>`
```cpp
function<void(int, int, int)> dfs = [&](int x, int y, int gold) {
    gold += grid[x][y];
    ans = max(ans, gold);

    int rec = grid[x][y];
    grid[x][y] = 0;

    for (int d = 0; d < 4; ++d) {
        int nx = x + dirs[d][0];
        int ny = y + dirs[d][1];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] > 0) {
            dfs(nx, ny, gold);
        }
    }

    grid[x][y] = rec;
};
```

例1：[c++基础(lambda)](https://www.jianshu.com/p/6482fbd3abdf)

但是这篇文章对`[=][&]`d的解释不好,

```cpp
#include <iostream>
#include <vector>
#include <algorithm>


void ForEach(const std::vector<int> &values, void (*func)(int))
{
    for (int value : values)
        func(value);
}

int main(int argc, char const *argv[])
{
    std::vector<int> values = {1, 2, 3, 2, 1};
    ForEach(values, [](int value) { std::cout << "value: " << value << std::endl; });
    std::cin.get();
}
```

例2：[在C++中Lambda表达式](https://docs.microsoft.com/zh-cn/previous-versions/dd293608\(v=vs.110\)?redirectedfrom=MSDN)

```cpp
// even_lambda.cpp
// compile with: cl /EHsc /nologo /W4 /MTd
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() 
{
   // Create a vector object that contains 10 elements.
   vector<int> v;
   for (int i = 0; i < 10; ++i) {
      v.push_back(i);
   }

   // Count the number of even numbers in the vector by 
   // using the for_each function and a lambda.
   int evenCount = 0;
   for_each(v.begin(), v.end(), [&evenCount] (int n) {
      cout << n;

      if (n % 2 == 0) {
         cout << " is even " << endl;
         ++evenCount;
      } else {
         cout << " is odd " << endl;
      }
   });

   // Print the count of even numbers to the console.
   cout << "There are " << evenCount 
        << " even numbers in the vector." << endl;
}

/*输出：
0 is even
1 is odd
2 is even
3 is odd
4 is even
5 is odd
6 is even
7 is odd
8 is even
9 is odd
There are 5 even numbers in the vector.
*/
```

例3：

```cpp
int main() { 
	int boys = 4, girls = 3; 
	auto totalChild = [=]()->int { return girls + boys; };
	auto totalChild2 = [=]() { return girls + boys; };
	cout << totalChild() << endl << totalChild2();
	return totalChild(); 
}

//输出 7 7
```

例4：

```cpp
int x = 1;
auto valueLambda = [=]() { cout << x << endl; };
auto refLambda = [&]() { cout << x << endl; };
x = 13;
valueLambda();
refLambda();

//输出： 1 13
```

例5
```cpp
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<int> idx(n);
        iota(idx.begin(),idx.end(),0);
        sort(idx.begin(), idx.end(), [&](const int& a, const int& b)->bool{
            return wage[a]/quality[a] <= wage[b]/quality[b];
        });
    ...
    }
如果去掉船只符号 & 则会报错
```

## []两种用法速度

```cpp
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n = arr.size();
        vector<int> idx(n,0);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), 
            //[&arr]
            [r = arr.data()]
            (int a, int b)
            {return r[a] < r[b];});
            //{return arr[a] < arr[b];});
    }
```

1. `[r = arr.data()]` 快
2. `[&arr]` 慢