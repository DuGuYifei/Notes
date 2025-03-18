# 自定义iterator

原文来自下面链接处。

[浅谈如何实现自定义的 iterator](https://hedzr.com/c++/algorithm/writing-your-own-stl-iterator/)

## 实现你自己的迭代器


### 使用 std::iterator

在 C++17 之前，实现自定义的迭代器被推荐采用从 std::iterator 派生的方式。



#### std::iterator 的基本定义

Std::iterator 具有这样的定义：

```cpp
template<
    class Category,
    class T,
    class Distance = std::ptrdiff_t,
    class Pointer = T*,
    class Reference = T&
> struct iterator;
```

其中，T 是你的容器类类型，无需多提。而 Category 是必须首先指定的所谓的 `迭代器标签`，参考 [这里](https://en.cppreference.com/w/cpp/iterator/iterator_tags) 。Category 主要可以是：

1. input_iterator_tag：输入迭代器
2. output_iterator_tag：输出迭代器
3. forward_iterator_tag：前向迭代器
4. bidirectional_iterator_tag：双向迭代器
5. random_access_iterator_tag：随机访问迭代器
6. contiguous_iterator_tag：连续迭代器

这些标签看起来似乎相当莫名其妙，仿佛我知道它们的用意，但实际上却又难以明白，难以挑选。



#### 迭代器标签

下面粗略地对它们及其关联实体进行特性上的介绍，以帮助你理解。

这些 tags 实际上绑定关联着一些同名实体类如 input_iterator 等等，通过模板特化技术分别实现专有的 distance() 和 advance() ，以达到特定的迭代优化效果。



##### `input_iterator_tag` 

`input_iterator_tag` 可以包装函数的输出——以用作它人的输入流。所以它是仅可递增的（只能 +1），你不能对它 +n，只能通过循环 n 次递增来模拟相应的效果。input_iterator 无法递减（-1），因为输入流没有这样的特性。它的迭代器值（`*it`）是只读的，你不能对其置值。

但 output_iterator_tag，forward_iterator_tag 的迭代器值是可读写的。可读写的迭代器值是指：

```cpp
std::list<int> l{1,2,3};
auto it = l.begin();
++it;
(*it) = 5; // <- set value back into the container pointed by iterator
```

`input_iterator` 将容器呈现为一个输入流，你可以通过 input_iterator 接收输入数据流。



##### `output_iterator_tag`

`output_iterator_tag` 很少被用户直接使用，它通常和 back_insert_iterator/ front_insert_iterator/ insert_iterator 以及 ostream_iterator 等配合使用。

`output_iterator` 没有 ++/-- 能力。你可以向 `output_iterator` 指向的容器中写入/置入新值，仅此而已。

如果你有输出流样式的呈现需求，可以选择它。



##### `forward_iterator_tag` 

`forward_iterator_tag` 表示前向迭代器，所以只能增量，不能回退，它继承 `input_iterator_tag` 的一切基本能力，但又有所增强，例如允许设置值。

从能力上说，`input_iterator` 支持读取/设置值，也支持递增行走，不支持递减行走（需要模拟，低效），+n 需要用循环模拟故而低效，但如果你的容器只有这样的外露的需求，那么 `forward_iterator_tag` 就是最佳选择。

从理论上来说，支持 `forward_iterator_tag`  的迭代器必须至少实现 begin/end。



##### `bidirectional_iterator_tag` 

`bidirectional_iterator_tag` 的关联实体 `bidirectional_iterator` 是双向可行走的，既可以 `it++`  也可以 `it--`，例如 std::list。如同 `forward_iterator_tag` 一样，`bidirectional_iterator_tag` 不能直接 +n （和 -n），所以 +n 需要一个特化的 advance 函数来循环 n 次，每次 +1（即通过循环 n 次递增或递减来模拟）。

从理论上来说，支持 `bidirectional_iterator_tag`  的迭代器必须同时实现 begin/end 以及 rbegin/rend。



##### `random_access_iterator_tag` 

`random_access_iterator_tag` 表示的随机访问迭代器，`random_access_iterator` 支持读取/设置值，支持递增递减，支持 +n/-n。

由于 `random_access_iterator` 支持高效的 +n/-n，这也意味着它允许高效的直接定位，这种迭代器的所属容器，通常也顺便支持 `operator []` 下标存取，如同 std::vector 那样。



##### `contiguous_iterator_tag`

`contiguous_iterator_tag` 在 C++17 中开始引入，但是编译器们的支持力度有问题，所以目前我们不能对其进行详细介绍，对于实作来说不必考虑它的存在。



#### 自定义迭代器的实现

一个定制迭代器需要选择一个迭代器标签，也就是选择迭代器的支持能力集合。下面是一个示例：

```cpp
namespace customized_iterators {
  template<long FROM, long TO>
  class Range {
    public:
    // member typedefs provided through inheriting from std::iterator
    class iterator : public std::iterator<std::forward_iterator_tag, // iterator_category
    long,                      // value_type
    long,                      // difference_type
    const long *,              // pointer
    const long &               // reference
      > {
      long num = FROM;

      public:
      iterator(long _num = 0)
        : num(_num) {}
      iterator &operator++() {
        num = TO >= FROM ? num + 1 : num - 1;
        return *this;
      }
      iterator operator++(int) {
        iterator ret_val = *this;
        ++(*this);
        return ret_val;
      }
      bool operator==(iterator other) const { return num == other.num; }
      bool operator!=(iterator other) const { return !(*this == other); }
      long operator*() { return num; }
    };
    iterator begin() { return FROM; }
    iterator end() { return TO >= FROM ? TO + 1 : TO - 1; }
  };

  void test_range() {
    Range<5, 13> r;
    for (auto v : r) std::cout << v << ',';
    std::cout << '\n';
  }

}
```

> 这个示例的原型来自于 cppreference 上 [std::iterator](https://en.cppreference.com/w/cpp/iterator/iterator) 及其原作者，略有修改。



#### 自增自减运算符重载

专门独立一个小节，因为发现垃圾教程太多了。

自增自减的运算符重载分为前缀后缀两种形式，前缀方式**返回引用**，后缀方式**返回新副本**：

```cpp
struct X {
  // 前缀自增
  X& operator++() {
    // 实际上的自增在此进行
    return *this; // 以引用返回新值
  }

  // 后缀自增
  X operator++(int) {
    X old = *this; // 复制旧值
    operator++();  // 前缀自增
    return old;    // 返回旧值
  }

  // 前缀自减
  X& operator--() {
    // 实际上的自减在此进行
    return *this; // 以引用返回新值
  }

  // 后缀自减
  X operator--(int) {
    X old = *this; // 复制旧值
    operator--();  // 前缀自减
    return old;    // 返回旧值
  }
};
```

或者去查看 cppreference 的 [文档](https://zh.cppreference.com/w/cpp/language/operators) 以及 [文档](https://zh.cppreference.com/w/cpp/language/operator_incdec)，别去看那些教程了，找不出两个正确的。

正确的编码是实现一个前缀重载，然后基于它实现后缀重载：

```cpp
struct incr {
  int val{};
  incr &operator++() {
    val++;
    return *this;
  }
  incr operator++(int d) {
    incr ret_val = *this;
    ++(*this);
    return ret_val;
  }
};
```

如果有必要，你可能需要实现 `operator=` 或者 `X(X const& o)` 拷贝构造函数。但对于`简单平凡 struct` 来说可以省略（如果你不能确定自动内存拷贝是否被提供，考虑查看汇编代码，或者干脆显式实现 `operator=` 或者 `X(X const& o)` 拷贝构造函数）





### C++17 起

但从 C++17 起 std::iterator 被弃用了。

> 如果你真的很关心流言飞语，可以去 [这里](https://stackoverflow.com/questions/37031805/preparation-for-stditerator-being-deprecated/38103394) 看看有关的讨论。

在多数情况下，你仍然可以使用 std::iterator 来简化代码编写，但这一特性以及早期的迭代器标签、类别等等概念已经过时。



#### 完全手写迭代器

所以在从 C++17 开始的新时代，自定义迭代器原则上暂时只有手写。

```cpp
namespace customized_iterators {
  namespace manually {
    template<long FROM, long TO>
    class Range {
      public:
      class iterator {
        long num = FROM;

        public:
        iterator(long _num = 0)
          : num(_num) {}
        iterator &operator++() {
          num = TO >= FROM ? num + 1 : num - 1;
          return *this;
        }
        iterator operator++(int) {
          iterator ret_val = *this;
          ++(*this);
          return ret_val;
        }
        bool operator==(iterator other) const { return num == other.num; }
        bool operator!=(iterator other) const { return !(*this == other); }
        long operator*() { return num; }
        // iterator traits
        using difference_type = long;
        using value_type = long;
        using pointer = const long *;
        using reference = const long &;
        using iterator_category = std::forward_iterator_tag;
      };
      iterator begin() { return FROM; }
      iterator end() { return TO >= FROM ? TO + 1 : TO - 1; }
    };
  } // namespace manually

  void test_range() {
    manually::Range<5, 13> r;
    for (auto v : r) std::cout << v << ',';
    std::cout << '\n';
  }

}
```

示例中的 iterator traits 部分不是必需的，你完全可以不必支持它们。



#### 需要照顾到的事情

完全手写迭代器的注意事项包括：

1. begin() 和 end()
2. 迭代器嵌入类（不必被限定为嵌入），至少实现：
   1. 递增运算符重载，以便行走
   2. 递减运算符重载，如果是双向行走（bidirectional_iterator_tag）或随机行走（random_access_iterator_tag）
   3. `operator*`  运算法重载，以便迭代器求值
   4. `operator!=` 运算符重载，以便计算迭代范围；必要时也可以显式重载 `operator==`（默认时编译器自动从 `!=` 运算符上生成一个配套替代品）

如果你编码对迭代范围进行了支持，那么就可以使用 for 范围循环：

```cpp
your_collection coll;
for(auto &v: coll) {
  std::cout << v << '\n';
}
```

关于 for 范围循环的展开式，可以查看 [这里](https://en.cppreference.com/w/cpp/language/range-for)。



### C++20 之后

在 C++20 之后，迭代器发生了巨大的变化。但由于它的工程实作还早的很，所以本文中暂且不予讨论。





### 其它相关



#### 除了 iterator 还有 const_iterator

为了代码规范和安全性，getter 通常一次提供两个，可写的和不可写的：

```cpp
struct incr {
  int &val(){ return _val; }
  int const &val() const { return _val; }
  private:
  int _val{};
}
```

同样的道理，迭代器的 begin() 和 end() 也至少要提供 const 和 非 const 的两种版本。一般来说你可以通过独立实现来帮助提供多套版本：

```cpp
struct XXX {
  
  // ... struct leveled_iter_data {
  //    static leveled_iter_data begin(NodePtr root_) {...}
  //.   static leveled_iter_data end(NodePtr root_) {...}
  // }
  
  using iterator = leveled_iter_data;
  using const_iterator = const iterator;
  iterator begin() { return iterator::begin(this); }
  const_iterator begin() const { return const_iterator::begin(this); }
  iterator end() { return iterator::end(this); }
  const_iterator end() const { return const_iterator::end(this); }

}
```

这是不费脑子的一种方式，读写安全性被约束在 XXX 之内：owner 当然能够明白哪些应该可被暴露，哪些需要暂时约束暴露出来的能力。

除了 iterator 和 const_iterator 之外，rbegin/rend, cbegin/cend 等也可以考虑被实现。



#### 注意事项：迭代器的使用

迭代器的使用一定要注意**随用随取**的准则。

```cpp
void test_iter_invalidate() {
  std::vector<int> vi{3, 7};
  auto it = vi.begin();
  it = vi.insert(it, 11);
  vi.insert(it, 5000, 23);
  vi.insert(it, 1, 31);				// crach here!
  std::cout << (*it) << '\n';
  return;
}
```

在多数 OS 环境中，`vi.insert(it, 5000, 23);` 语句有极大概率导致 vector 不得不重新分配内部的数组空间，因此该语句执行之后，it 所持有的内部指针就已经无意义了（it 仍指向旧的缓冲区的某个位置），所以下一行语句继续使用 it 将会导致错误的指向与写入。由于过时的缓冲区有很大的可能已经被调度处于缺页状态，所以这个错误往往会导致 SIGSEGV 致命异常。如果产生了 SIGSEGV 信号，你可能是很幸运的，反而若是过时的缓冲区尚且有效，那么这一语句能够被执行且不报任何错误，那才是要命。



#### 迭代器的搜索并删除

stdlib 的容器采用一种叫做 [erase and remove](https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom) 的惯用法来事实上删除一个元素。以 std::list 为例，remove_if() 能够从 list 中找到符合条件的元素，并将他们聚集（收集）起来移动到 list 的末尾，然后返回这组元素中的第一个元素的位置 iter，然而这些元素并未被从 list 中删除，如果你需要去掉他们的话，你需要以 list.erase(iter, list.end()) 来明确地移除它们。

所以删除元素是这样的：

```cpp
bool IsOdd(int i) { return i & 1; }

std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
v.erase(std::remove_if(v.begin(), v.end(), IsOdd), v.end());

std::list<int> l = { 1,100,2,3,10,1,11,-1,12 };
l.erase(l.remove_if(IsOdd), l.end());
```

由于 std::vector 不能像 std::list 那样聚集元素到链表末尾，所以它没有 remove_if() 成员函数，故而在它上面做 search & erase 需要 **std::remove_if** 的参与。而 std::list 可以直接使用成员函数 remove_if 来完成，代码也显得稍微简洁一些。

自 C++20 起，erase and remove_if 可以被简化为 std::erase_if() 或 erase_if() 成员函数，例如  [std::erase, std::erase_if (std::vector)](https://en.cppreference.com/w/cpp/container/vector/erase2) 。







## 后记

这次的 About customizing your own STL-like iterator 贡献了一些个人理解和最佳实践的准则，但是还有点点意犹未尽。

下回考虑是不是介绍一个 tree_t 及其迭代器实现，或许能够更有参考价值。

![image-20211028185204870](https://raw.githubusercontent.com/hzimg/blog-pics/master/uPic/image-20211028185204870.png)

### Refs

- [基于范围的 for 循环 (C++11 起) - cppreference.com](https://zh.cppreference.com/w/cpp/language/range-for) 

- [std::iterator - cppreference.com](https://en.cppreference.com/w/cpp/iterator/iterator) 

- [std::input_iterator_tag, std::output_iterator_tag, std::forward_iterator_tag, std::bidirectional_iterator_tag, std::random_access_iterator_tag, std::contiguous_iterator_tag - cppreference.com](https://en.cppreference.com/w/cpp/iterator/iterator_tags) 

- [Increment/decrement operators - cppreference.com](https://en.cppreference.com/w/cpp/language/operator_incdec) 

- [operator overloading - cppreference.com](https://en.cppreference.com/w/cpp/language/operators) 

- [Traversing Trees with Iterators](https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html) 

- [c++ - How to implement an STL-style iterator and avoid common pitfalls? - Stack Overflow](https://stackoverflow.com/questions/8054273/how-to-implement-an-stl-style-iterator-and-avoid-common-pitfalls)

- [c++ - Writing your own STL Container - Stack Overflow](https://stackoverflow.com/questions/7758580/writing-your-own-stl-container/7759622#7759622) 

- [STL & Generic Programming: Writing Your Own Iterators - Dr Dobb's](https://www.drdobbs.com/stl-generic-programming-writing-your-ow/184401417) 

   [c++ - How to correctly implement custom iterators and const_iterators? - Stack Overflow](https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators) 
