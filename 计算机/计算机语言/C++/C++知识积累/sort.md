# sort
`sort`函数返回的是升序排列。

如果要降序，就要自己写`compare`函数

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