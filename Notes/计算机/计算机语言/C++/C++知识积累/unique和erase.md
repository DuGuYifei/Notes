# unique和erase

1. 只清理相连，所以无序要先排序
2. 伪去重，将重复元素扔到后面

```c++
#include <iostream>
#include <algorithm>
int main(void){
    int a[8] = {2, 2, 2, 4, 4, 6, 7, 8};
    int c;
    std::sort(a, a + 8);  //对于无序的数组需要先排序
    c = (std::unique(a, a + 8) - a );
    std::cout<< "c = " << c << std::endl;//去重函数返回地址为：去重后最后一个不重复元素地址
    //打印去重后的数组成员
    for (int i = 0; i < c; i++)
        std::cout<< "a = [" << i << "] = " << a[i] << std::endl;
    return 0;
}
```
返回值c等于5，而a数组的前5项为2、4、6、7、8。

对于容器也是一样

下案例：**unique + erase**
```c++
std::vector<int> ModuleArr;
//排序
std::sort(ModuleArr.begin(), ModuleArr.end());
//去重
ModuleArr.erase(unique(ModuleArr.begin(), ModuleArr.end()), ModuleArr.end());
```