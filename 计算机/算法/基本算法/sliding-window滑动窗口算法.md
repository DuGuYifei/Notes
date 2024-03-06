# sliding-window滑动窗口算法
有两个指针，左指针和右指针

两种思维方式：

以leetcode.3为例，无重复字符的最长子串
* 用左指针大循环中右移（条件是只要重复还存在），右指针小循环扩大窗口
```c++
    unordered_set<char> window;
    int n = s.size();
    int rk = 0, ans = 0; //右指针
    for (int i = 0; i < n; i++) //左指针
    {
        if (i != 0)
        {
            window.erase(s[i - 1]);
        }
        while (rk < n && !window.count(s[rk]))
        {
            window.insert(s[rk]);
            rk++;
        }
        ans = max(ans, rk - i);
    }
    return ans;
```
* 用右指针大循环中右移扩大窗口（条件是只要重复还存在），左指针小循环右移（当还存在重复的）
```c++
    bool hash[128] = {false}; //一共就只有128位ascii码
    int right = 0, left = 0, n = s.size(), ans = 0;
    for (; s[right] != '\0'; right++)
    {
        if(!hash[s[right]])
        {
            hash[s[right]] = true;
        }
        else
        {
            ans = max(ans, right - left);
            while(s[left]!=s[right])
            {
                hash[s[left]] = false;
                left++;
            }
            left++;
        }
    }
    ans = max(ans, right - left);
    return ans;
```