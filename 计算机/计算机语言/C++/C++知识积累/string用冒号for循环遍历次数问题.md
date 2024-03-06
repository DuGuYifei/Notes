# string用冒号for循环遍历次数问题
```cpp
    string x = "1234";
    int ans = 4;
    for (auto& i : x)
    {
        ans--;
    }
    cout << ans;
```

输出 0

所以不遍历`\0`