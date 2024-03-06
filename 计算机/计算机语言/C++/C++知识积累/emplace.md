# emplace


## 效率
**正确说法：**`emplace比其他方法快，因为
* 其他：
  * 构造一个临时对象
  * 调用移动构造函数把临时对象的副本拷贝到容器末尾增加的元素中
  * 调用析构释放临时对象
* emplace：
  * 调用构造函数

**错误说法：**在vector中`emplace_back`没有`push_back`快

## 用法
但是emplace可以直接传入构造用的参数，比如pair，可以直接传两个值进去自动生成pair。

最近在刷题的时候看别人优雅的代码，发现一个叫做“emplace”的新朋友，检索了网上的相关资料后知道，这是C++11中加入的新特性，`emplace_back`能通过参数构造对象，不需要拷贝或者移动内存，相比`push_back`能更好地避免内存的拷贝与移动，使容器插入元素的性能得到进一步提升。

由此，在大多数情况下应该优先使用`emplace_back`来代替`push_back`。所有的标准库容器（array除外，因为它的长度不可改变，不能插入元素）都增加了类似的方法：`emplace`、`emplace_hint`、`emplace_front`、`emplace_after`、`emplace_back`等.


[C++11中emplace的使用\_MaloFleur-CSDN博客\_emplace](https://blog.csdn.net/u013700358/article/details/52623985)

支持传入参数直接构造，详情见
[push和emplace区别](push和emplace区别.md)

## emplace_hint
`emplace_hint(const_iterator hint, Args&&...args)`
hint是位置，比如`.begin()`

## emplace 和 emplace_back 在vector中
```cpp

// vector::emplace,emplace_back
#include <iostream>
#include <vector>
using namespace std;
 
class text{
private:
    string str;
public:
    text(string s):str(s){}
    void show()const{
        cout<<str<<endl;
    }
 
};
 
//emplace的用法 iterator emplace (const_iterator position, Args&&... args);
//在position位置插入一个元素，非常得注意，这个position是一个迭代器，并不是整型int
//在position位置插入一个元素后，原position后的元素都要一次后移一个位置
//返回指向新插入元素的迭代器
int main ()
{
    vector<int> res = {10,20,30};
 
    //int(错误，不能用int) it = res.emplace ( res.begin()+1, 100 );
    //emplace返回指向新插入元素的迭代器
    auto it = res.emplace ( res.begin()+1, 100 );
    res.emplace ( it, 200 );
    res.emplace ( res.end(), 300 );
 
    cout << "myvector contains:";
    //或者用for (auto& x: res)
    //或者用for (auto x: res)
    for (int x: res)
        cout << ' ' << x;
    cout << '\n';
 
//-------------------------------------------------------------
//-------------------------------------------------------------
    //emplace_back的用法
    //emplace_back和push_back的功能一样，但用emplace_back更好
    vector<text> vi;
    vi.emplace_back("Leo");
    vi.front().show();
    vi.emplace_back("Love");
 
    //这条push_back代码会报错没想到吧，为什么报错呢？
    //不用深究，是它背后的机制造成的
    //vi.push_back("Love");
    vi.back().show();
 
    return 0;
}
```