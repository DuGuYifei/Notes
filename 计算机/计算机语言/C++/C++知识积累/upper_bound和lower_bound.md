# upper_bound和lower_bound

* 二分查找
* 返回地址，所以用`*`提取内容
* 返回迭代器，可以直接 - begin() 得到int pos 索引值
* 找不到返回 end()
* `#include <algorithm>`

lower_bound( )和upper_bound( )都是利用二分查找的方法在一个排好序的数组中进行查找的。

在从小到大的排序数组中，

**lower_bound**( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个**大于或等于**num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

**upper_bound**( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个**大于**num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

在从大到小的排序数组中，重载lower_bound()和upper_bound()

lower_bound( begin,end,num,greater<type>() ):从数组的begin位置到end-1位置二分查找第一个小于或等于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

upper_bound( begin,end,num,greater<type>() ):从数组的begin位置到end-1位置二分查找第一个小于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。
————————————————
版权声明：本文为CSDN博主「brandong」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_40160605/article/details/80150252

## 自定义比较
出自 [leetcode 1235](../../../LeetCode/1235.规划兼职工作.cpp)
```cpp
        for(int i = 1; i <= n; i++)
        {
            int k = upper_bound(jobs.begin(), jobs.begin() + i - 1, jobs[i-1][0], [&](int st, const vector<int>& job){
                return st < job[1]; // 找到第一个比它大的值的索引，则前一个刚好是最后一个小于等于 jobs[i-1][0]的值
            }) - jobs.begin();
            dp[i] = max(dp[i - 1], dp[k] + jobs[i - 1][2]); // 直接用k是因为dp有个默认dp[0] = 0，相当于比jobs多出一个索引
        }
```