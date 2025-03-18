# heap堆

## heap
头文件#include <algorithm>,STL在<algorithm.h>中实现了对存储在数组或vector中的元素进行堆操作的函数，包括make_heap, pop_heap, push_heap, sort_heap。
【两层：上层heap，底层vector(或数组)】，即用数组或vector数据容器来实现堆。
默认情况下是max-heap，该大顶堆实际上是以一个vector表现的完全二叉树。

## heap操作的四个函数：
* make_heap( )：建立堆（要么大顶堆，要么小顶堆）
* push_heap( ): 在堆中添加元素
* pop_heap( ): 在堆中删除元素
* sort_heap( ): 堆排序

相关参数：
_First, _Last：可以随机访问的迭代器/ 指针
_Comp: 比较函数（仿函数）,其规则——如果函数的第一个参数小于第二个参数应返回true，否则返回false。默认less

使用建议：
**大顶堆**，就每一个函数都加上第三个参数`less<int>()`，假如元素是int类型的；
**小顶堆**，就每一个函数都加上第三个参数`greater<int>()`，假如元素是int类型的，一直加上，一直一致。

## 建立堆
```cpp
make_heap(_First, _Last, _Comp)
```

默认是建立大最大堆的。

## 在堆中添加元素
```cpp
push_heap(_First, _Last，_Comp)
```

要先在底层容器（数组或vector）里加入数据，再调用push_heap()。
实现细节：（1）添加元素到vector的尾部；（2）重新调整堆。
该算法必须是在满足堆序的条件下，添加元素。
如，插入15到当前的大根堆里，vector容器名字为max_heap：

```cpp
max_heap.push_back(15);
push_heap(max_heap.begin(), max_heap.end());
```

## 在堆中删除元素
```cpp
pop_heap(_First, _Last，_Comp)
```

实现细节：（1）删除堆顶元素；（2）用尾部元素替代max_heap[0]；（3）重新调整堆。
(pop_heap操作实际上是我们把堆顶元素取出来，放到了数组或vector容器的末尾，用原来的末尾元素去替代，然后end迭代器减1，执行siftdown()下溯函数来重新调整堆）
注意算法执行完毕后，最大的元素并没有被取走，而是放于底层容器的末尾。如果要取走，则可以使用底部容器（vector）提供的pop_back()函数。
pop_heap()操作后，再调用max_heap.pop_back()，从底层容器中删掉原堆顶元素。

```cpp
pop_heap(max_heap.begin(), max_heap.end());//取出了堆顶元素（也叫删除堆顶元素），放到了底层容器的末尾，原来末尾的元素替代堆顶，end迭代器减1，重新siftdown了堆
max_heap.pop_back();//从底层容器（数组或vector）中删除了元素
```

## 堆排序
```cpp
sort_heap(_First, _Last，_Comp)
```

**既然每次pop_heap可以获得堆顶的元素（假如是大顶堆，每次都获得最大的元素，取出放到了底层容器的末尾），那么我们持续对整个heap做pop_heap操作，每次讲操作的范围向前缩减一个元素（就是每次end迭代器减1）。最终我们可以获得一个递增的序列。**
注意：这个排序是在一个堆上进行的。

关于堆排序，可以看看这个博客<<白话经典算法系列之七 堆排序>> https://blog.csdn.net/morewindows/article/details/6709644

## 实现
### 小顶堆，堆排序为降序
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printHeap(vector<int> &v){
    for(vector<int>::iterator it= v.begin();it!=v.end();++it){
        cout<< *it <<" ";
    }
    cout<<"\n"<<endl;
}

int main()
{
    vector<int> min={10,30,22,6,15,9};

    //建立小顶堆
    make_heap(min.begin(), min.end(), greater<int>());
    printHeap(min);//6 10 9 30 15 22

    //插入元素
    min.push_back(20);
    push_heap(min.begin(),min.end(), greater<int>());//该算法前提：必须在堆的条件下
    printHeap(min); //6 10 9 30 15 22 20   仍为小顶堆

    //删除堆顶元素
    pop_heap(min.begin(),min.end(), greater<int>());
    printHeap(min);//9 10 20 30 15 22 6  不为小顶堆 这个pop_heap操作后，实际上是把堆顶元素放到了末尾
    min.pop_back();//这才彻底在底层vector数据容器中删除
    printHeap(min);//9 10 20 30 15 22  仍为小顶堆

    //堆排序  保持greater，小顶堆，得到的是降序
    sort_heap(min.begin(),min.end(), greater<int>());//试了用less，结果杂乱无章
    printHeap(min);//30 22 20 15 10 9 注意结果是降序的哦!!!其实是调用了很多次pop_heap(...,greater..)，每一次都把小顶堆堆顶的元素往末尾放，没放一次end迭代器减1

    return 0;
}
```

### 大顶堆，堆排序为升序
把上面code里所有的第三个参数改为less<int>()。


## 原理
一个数组存数字，比如大顶堆。

### push
先在数组尾部加一个位置，然后每次跟父节点比较，大了就shiftup，跟爹交换。

### pop
先把头跟尾交换，尾巴扔掉，头开始向下滑，每次跟较大的儿子交换位置。