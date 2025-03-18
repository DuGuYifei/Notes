# vector

1. [常用函数](#常用函数)
2. [vector中存储正则表达式](#vector中存储正则表达式)
3. [vector分配内存和reserve分配内存](#vector分配内存和reserve分配内存)
4. [vector 用vector初始化](#vector-用vector初始化)
5. [vector 声明省略式](#vector-声明省略式)


## 常用函数
| code                                                                                 | Meaning                                                     |
| ------------------------------------------------------------------------------------ | ----------------------------------------------------------- |
| `vector.pop_back()`                                                                  | 去掉最后一个元素                                            |
| `vector.back()`                                                                      | 返回最后一个元素                                            |
| `new vector a {}`                                                                    | 可以用来初始化vector                                        |
| `vector a(length,value = 0)`                                                         | 可以初始化一个长length值value(省略默认0)的向量              |
| `vector<vector<int>> v(m,vector<int>(n))`                                            | 二维向量的声明，m个vector，每个包含n个0                     |
| `vector<vector<vector<double>>> dp(n,vector<vector<double>>(n,vector<double>(k+1)))` | dp[n][n][k+1]三维数组初始化0                                |
| `vec.resize(n)`                                                                      | 将vec这个向量重新分配大小n，初始值是0                       |
| `ans.insert(ans.end(),p2,b.end());`                                                  | 在ans最后加上从p2（b的一个迭代器）开始到end()结束的所有元素 |

## vector中存储正则表达式
[vector中存储正则表达式](regex正则表达式.md)

## vector分配内存和reserve分配内存
[reserve用法](https://blog.csdn.net/hl_zzl/article/details/84944494)

正常capacity：1，2，4，8，16

reserve 100 后: 100, 200

reserve后还可以push_back，就像正常情况下capacity乘以2了但是还是push_back

## vector 用vector初始化
```cpp
    vector<int>a({ 1,2,3,4,5 });
    vector<int>b(a.begin(), a.begin() + 2); // 1,2
```
**不包含 begin()+2**

[iota生成顺序递增序列](iota生成顺序递增序列.md)

## vector 声明省略式

```cpp
vector<vector<vector<int>>> d(n + 1, vector(6, vector<int>(16)));
vector d(n + 1, vector(6, vector<int>(16)));
```