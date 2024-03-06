# memset()数组初始化设值

```c++
int dp[MAXN][MAXN][MAXN*2]
memset(dp, -1, sizeof(dp)); //将dp中的所有值全部设置为-1
```
```cpp
void *memset(void *s, int ch, size_t n); 
```
函数解释：将s中当前位置后面的n个字节 （typedef unsigned int size_t ）用 ch 替换并返回 s 。