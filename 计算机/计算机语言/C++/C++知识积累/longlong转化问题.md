# long long转化问题

[static_cast](static_cast和dynamic_cast.md)

```cpp
            ans += static_cast<long long>(i - maxLeft[i]) * (maxRight[i] - i) * nums[i] + static_cast<long long>(minLeft[i] - i) * (minRight[i] - i) * nums[i];
```

`1LL` 表示long long的1