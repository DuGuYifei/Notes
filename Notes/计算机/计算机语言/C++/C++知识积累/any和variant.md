# any和variant

## any

`std::any`是C++17引入的一个新特性，它是一个类型安全的容器，可以存储任何类型的对象。`std::any`是一个类模板，它的实例可以存储任何类型的对象，只要该类型是复制可构造的。

```cpp
#include <any>
#include <iostream>

int main() {
    std::any var = 10;  // 存储 int 类型
    var = std::string("Hello");  // 可以存储不同类型

    try {
        std::cout << std::any_cast<std::string>(var) << std::endl;  // 使用 any_cast 提取值
    } catch (const std::bad_any_cast& e) {
        std::cout << "Bad cast: " << e.what() << std::endl;
    }
}
```

## variant

`std::variant`是C++17引入的另一个新特性，它是一个类型安全的联合，可以存储多个类型中的一个。`std::variant`是一个类模板，它的实例可以存储多个类型中的一个，只要这些类型是复制可构造的。

```cpp
#include <variant>
#include <iostream>

int main() {
    std::variant<int, double> var = 10;  // 存储 int 类型（不一定只有两种类型）
    var = 3.14;  // 可以存储不同类型

    try {
        std::cout << std::get<double>(var) << std::endl;  // 使用 get 提取值
    } catch (const std::bad_variant_access& e) {
        std::cout << "Bad access: " << e.what() << std::endl;
    }
}
```