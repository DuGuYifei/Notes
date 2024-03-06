# Gray Code 格雷码
[力扣](https://leetcode-cn.com/problems/gray-code/)\
[百度百科](https://baike.baidu.com/item/%E6%A0%BC%E9%9B%B7%E7%A0%81)

**n位格雷码序列**是一个由`2n`个整数组成的序列，其中：
* 每个整数都在范围`[0, 2n - 1]`内（含`0`和`2n - 1`）
* 第一个整数是`0`
* 一个整数在序列中出现**不超过一次**
* 每对**相邻**整数的二进制表示**恰好一位不同**，且·
* **第一个**和**最后一个**整数的二进制表示恰好一位不同

```cpp
class Solution {
public:
//00 01  11 10
//000 001   011 010   110 111 101 100
    //n+1位格雷码的集合 = n位格雷码集合(顺序)加前缀0 + n位格雷码集合(逆序)加前缀1  百度百科
    vector<int> grayCode(int n) {
        vector<int>res(1<<n);
        // for(int i = 0 ; i<(1<<n);i++)
        // {
        //     res[i] = (i>>1)^i;
        // }
        // return res;
        res[0]=0;
        for(int i = 0; i<n ;i ++)
        {
            int mid = (1 << i);
            for(int j = 0;j<(1<<i);j++)
            {
                res[mid+j]=res[mid-j-1] ^ (1<<i);
            }
        } 
        return res;       
    }
    
};
```