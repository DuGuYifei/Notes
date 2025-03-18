# 文件流stream


## istream
istream可以让别的流放进去

```cpp
extern void expense_tracker(int argc, const char** argv, std::istream& input);

int main(int argc, char* argv[])
{
    expense_tracker(argc, const_cast<const char**>(argv), std::cin);
}
```

## ifstream

ifstream是从文件中读取数据的输入流。它是istream的派生类，因此它继承了istream的所有功能。ifstream类的构造函数和析构函数如下：

```cpp
#include <fstream>

std::ifstream ifs("file.txt");
if (!ifs.is_open()) {
    return;
}
```

## ofstream

ofstream是向文件中写入数据的输出流。它是ostream的派生类，因此它继承了ostream的所有功能。ofstream类的构造函数和析构函数如下：

```cpp
#include <fstream>

std::ofstream ofs("file.txt");

ofs << "Hello, World!" << std::endl;
```

### 参数

可以通过 按位或运算符 (|) 组合多个模式参数，例如：

* 默认模式：std::ios::out（等同于不指定模式）。
* 追加写入：std::ios::out | std::ios::app。
* 二进制写入：std::ios::out | std::ios::binary。
* 追加二进制写入：std::ios::out | std::ios::app | std::ios::binary。

## fixed 和 setprecision

```cpp
std::ofstream file(filename, std::ios::app);
file.precision(2);
file << std::fixed;

// 两位小数
std::cout.precision(2);
std::cout << std::fixed;
```