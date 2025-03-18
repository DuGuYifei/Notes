# string最后一位的一些思考和push_back
```cpp
string s = "aa";
cout << s[2]; //可以
//cout << s[3]; //报错

s.push_back('s'); 
cout << s; //aas

会自动解决\0的问题

```