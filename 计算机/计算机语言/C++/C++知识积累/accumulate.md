# accumulate

```cpp
class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        if (start > destination) {
            swap(start, destination);
        }
        return min(accumulate(distance.begin() + start, distance.begin() + destination, 0),
                   accumulate(distance.begin(), distance.begin() + start, 0) +
                   accumulate(distance.begin() + destination, distance.end(), 0));
    }
};
```

[C++ 函数：accumulate（）_lzm_create的博客-CSDN博客_accumulate c++](https://blog.csdn.net/sinat_36338365/article/details/106615934)

该算法函数在numeric头文件中定义：#include<numeric>
目前知道的有几个功能：1.求和；2.求连乘; 3.string合并


```cpp
#include<iostream>
#include<numeric>//accumulate函数在这个库中定义
#include<string>//包含这个库，可以直接输出字符串
#include<vector>//vector是向量类型，可容纳许多类型的数据，因此也被称为容器
using namespace std;
int main() {
//功能一：求和
 int list[10] = { 1,2,3,4,5,6,7,8,9,10 };
 int sum= accumulate(list, list+10, 0) ;
 cout <<"和："<<sum<<endl;
 //功能二：求连乘积
 int  con_product  = accumulate(list, list + 3, 1, multiplies<int>());
 cout<<"连乘积："<<con_product<<endl;
 //功能三：string合并
 vector<string>a{"1","-2345","+6"};
 string a_sum=accumulate(a.begin(), a.end(),string("out: "));
cout<<"string合并后输出："<<a_sum<<endl;
 return 0;
}

```

## 求和时，
accumulate带有三个形参：累加的元素起始地址；累加的元素结束地址，累加的初值（通常为0）。例如：
`sum= accumulate(list, list+10, 0)` ;得出`sum=55`.
如果`sum= accumulate(list, list+3, 0)` ;得出`sum=6`.
如果`sum= accumulate(list, list+3, 100)` ;得出`sum=106`.

## 求连乘积时，
accumulate带有四个形参：连乘的元素起始地址；连乘的元素结束地址，连乘的初值（通常为1）。例如：
`con_product= accumulate(list, list+3, 1, multiplies<int>())` ;得出`sum=6`.
如果`con_product= accumulate(list, list+3, 10, multiplies<int>())` ;得出`sum=60`.

## 求string合并，
`string a_sum=accumulate(a.begin(), a.end(),string("out: "))`;得到out: `1-2345+6`