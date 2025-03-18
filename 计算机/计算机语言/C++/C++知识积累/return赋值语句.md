# return赋值语句


```c++
vector<int> a = { 1,2,3 };

int ss(int x) {
    return a[x] = 1;
}

int main()
{
    
    cout << ss(2) << " " << a[2];
}
```
输出：
1 1