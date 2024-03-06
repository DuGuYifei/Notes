# stringstream

[c++ stringstream ss()_wesigj的博客-CSDN博客_istringstream ss(str);](https://blog.csdn.net/wesigj/article/details/108959219)

定义了三个类：istringstream、ostringstream 和 stringstream

```cpp
stringstream ss;
ss << str;

stringstream ss(str);
```

Example1:
```cpp
// swapping ostringstream objects
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

int main () {

  std::stringstream ss;

  ss << 100 << ' ' << 200;

  int foo,bar;
  ss >> foo >> bar;

  std::cout << "foo: " << foo << '\n';
  std::cout << "bar: " << bar << '\n';

  return 0;
}
 Edit & Run
```

Example2:
```cpp
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
	string str = "hello world";
	cout << str << endl;
	
	stringstream ss(str); //将str复制到ss
	string abc;
	while(ss >> abc) //相当于输入一个个的单词
	{
		cout << abc <<endl;
	}

	return 0;
}
```

Example2:
```cpp
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
	int num = 1000;
	string str;
	stringstream ss; //将str复制到ss
	ss << num;
	ss >> str;
	ss.clear();//使用stringstream来做转换时，最好使用完，进行ss.clear()操作
	cout << str << endl;
	cout << str.c_str() << endl;
	return 0;
}
```