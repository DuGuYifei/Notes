# transform 和 for_each
[C++ hash(STL hash)及其函数模板用法详解](http://c.biancheng.net/view/523.html)
[C++ transform](https://www.baidu.com/link?url=RhlqbdKts9ZhAwkz8BgidzcTYX3tNfnbydYqX4L9Cw6VLGwxRY57WA5PDVM3mxwBf59N2sWb6M4nvwVdsipb6a&wd=&eqid=8c79f515002c401a000000066202a75b)

```cpp
std::hash<int> hash_int;// Function object to hash int
std::vector<int> {-5, -2, 2, 5, 10};
std::transform(std::begin(n), std::end(n),std::ostream_iterator<size_t> (std:: cout," "),hash_int);
```

注意第三个参数是一直是开始位置，但是并不会让string反过来
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
char op(char ch)
{

   if(ch>='A'&&ch<='Z')
        return ch+32;
    else
        return ch;
}
int main()
{
    string first,second;
    cin>>first;
    second.resize(first.size());
    transform(first.begin(),first.end(),second.begin(),op);
    cout<<second<<endl;
    return 0;
}
```

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
void print(int &elem){cout<<elem<<" ";}
int op(int a,int b){return a*b;}
int main()
{
    vector <int> A,B,SUM;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int t;
        cin>>t;
        A.push_back(t);
    }
    for(int i=0;i<n;i++)
    {
        int t;
        cin>>t;
        B.push_back(t);
    }
    SUM.resize(n);
    transform(A.begin(),A.end(),B.begin(),SUM.begin(),op);
    for_each(SUM.begin(),SUM.end(),print);
    return 0;
}
```