# stable_sort和sort
[stable_sort()与sort()的用法区别_yunshouhu的博客-CSDN博客_stable_sort](https://blog.csdn.net/earbao/article/details/54911878)

带有stable的函数可保证相等元素的原本相对次序在排序后保持不变。

[力扣 937](https://leetcode-cn.com/problems/reorder-data-in-log-files/)

```cpp
class Solution {
public:
    static bool cmp(const string& a, const string& b)
    {
        int posa = a.find_first_of(' ');
        int posb = b.find_first_of(' ');
        bool ad = isdigit(a[posa+1]);
        bool bd = isdigit(b[posb+1]);
        if(ad && bd)
        {
            return false;
        }
        if(!ad && !bd)
        {
            string sa = a.substr(posa+1);
            string sb = b.substr(posb+1);
            if(sa!=sb)
            {
                return sa < sb;
            }
            return a<b;
        }
        return ad? false:true;
    }
    vector<string> reorderLogFiles(vector<string>& logs) {
        stable_sort(logs.begin(),logs.end(),cmp);
        return logs;
    }
};
```