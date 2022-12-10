# sort

1. [默认和自定义](#默认和自定义)
2. [sort 可以根据另一个数组排序](#sort-可以根据另一个数组排序)
3. [sort 自定义compare加速问题](#sort-自定义compare加速问题)
4. [多维](#多维)


## 默认和自定义
`sort`函数返回的是升序排列。

如果要降序，就要自己写`compare`函数

或者
```cpp
sort(a,a+len,greater<int>());//内置类型的由大到小排序
sort(subs.begin(), subs.end(), greater<string>{});
```

**Key**自己的函数要是static不然会报错，所以最好写成lambda表达式

sort vector 时候， 加上`&`会加速（加的多），加上const又加速一次（加的少）

`sort`一个`vector`:
```cpp
sort(nums.begin(), nums.end());
```

```cpp
static bool compare(int a,int b)   // 在class里不加static会报错
{
    return a>b; //降序排列，如果改为return a<b，则为升序
}
 
int main()
{
    int i;
    int a[20]={2,4,1,23,5,76,0,43,24,65};
     
    for(i=0;i<20;i++)
        cout<<a[i]<<endl;
    sort(a,a+20,compare);
     
    for(i=0;i<20;i++)
        cout<<a[i]<<endl;
     
    return 0;
}
```

`sort`一个数组

key:注意这个sort里是`+3`，因为sort要到最后一个的后面一个才行，比如vector的`end()`是最后一个元素的后面
```cpp
    pair<int, char> alphabet[3] = { {3,'a'},{5,'b'},{1,'c'} };
    sort(alphabet, alphabet + 3);
```

## sort 可以根据另一个数组排序

```cpp
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n = arr.size();
        vector<int> idx(n,0);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), 
            //[&arr]
            [r = arr.data()]
            (int a, int b)
            {return r[a] < r[b];});
            //{return arr[a] < arr[b];});
    }
```

## sort 自定义compare加速问题
慢1
```cpp
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(),pairs.end(), [&](vector<int>a, vector<int>b){
            return a[0]>b[0];
        });
        int ans = 0;
        int num = INT_MAX;
        for(auto& i : pairs)
        {
            if(i[1] < num)
            {
                ans++;
                num = i[0];
            }
        }
        return ans;
    }
};
```
慢2
```cpp
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(),pairs.end(), [&](const vector<int>a, const vector<int>b){
            return a[0]>b[0];
        });
        int ans = 0;
        int num = INT_MAX;
        for(auto& i : pairs)
        {
            if(i[1] < num)
            {
                ans++;
                num = i[0];
            }
        }
        return ans;
    }
};
```
快
```cpp
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(),pairs.end(), [](const vector<int>&a, const vector<int>&b){
            return a[0]>b[0];
        });
        int ans = 0;
        int num = INT_MAX;
        for(auto& i : pairs)
        {
            if(i[1] < num)
            {
                ans++;
                num = i[0];
            }
        }
        return ans;
    }
};
```

## 多维
多维默认先按第一个排序，相同就再按第二个。