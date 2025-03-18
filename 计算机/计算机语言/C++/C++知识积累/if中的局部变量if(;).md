# if中的局部变量if(int a = 1;a==0)
[LeetCode 2029 石子游戏-ix]

```cpp
class Solution
{
public:
    bool stoneGameIX(vector<int> &stones)
    {
        int zero = 0, one = 0, two = 0, n = stones.size();
        if (n == 0)
            return false;
        for (int i = 0; i < n; i++)
        {
            if (int res = stones[i] % 3;!res)
                zero++;
            else if (res == 1)
                one++;
            else
                two++;
        }
        if (!(zero % 2))
        {
            return one && two;
        }
        return one-two > 2 || two - one >2 ;
    }
};
```