# 随机数_mt19937_random_device_uniform_real_distribution

mt19937
纳尼？这是what？
这个东西确实鲜为人知，mt19937是C++11新加入的特性，虽然长得一脸蒙逼样，不影响其卓越的性能。
## 简介
mt是指maxint（整型int最大值的缩写）

19937是指2^19937-1

mt19937是c++11新特性，它是一种随机数算法，用法与rand()函数类似，但是mt19937具有速度快，周期长的特点（所谓周期长应该是指19937所代表的意思吧）

rand()在windows下生成的数据范围为0-32726

此时的mt19937所生成的数据范围大概为(-maxint,+maxint)（maxint整型int最大值的缩写）


## 代码
要取得 [a,b) 的随机整数，使用 (rand() % (b-a))+ a;
要取得 [a,b] 的随机整数，使用 (rand() % (b-a+1))+ a;
要取得 (a,b] 的随机整数，使用 (rand() % (b-a))+ a + 1;
要取得 0～1 之间的浮点数，可以使用rand()/double(RAND_MAX)。
————————————————
版权声明：本文为CSDN博主「TABE_」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/TABE_/article/details/123465659

```cpp
srand((int)time(0));
(int)(10.0 * rand()/(RAND_MAX+1.0));
```

```cpp
#include<random>
#include<ctime>

typedef std::mt19937  Random_mt19937;
Random_mt19937  rnd(time(0));

int main()
{
    printf("%11d\n",rnd());
    return 0;
}
```

```cpp
    int randomLevel() {
        int lv = 1;
        /* 随机生成 lv */
        while (dis(gen) < P_FACTOR && lv < MAX_LEVEL) {
            lv++;
        }
        return lv;
    }
```