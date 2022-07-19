# hash<T>和自构建hash函数给hashset
```cpp
auto hash_p = [](const pair<int, int> &p) -> size_t {
  static hash<long long> hash_ll;
  return hash_ll(p.first + (static_cast<long long>(p.second) << 32));
};
unordered_set<pair<int, int>, decltype(hash_p)> points(0, hash_p);
```

第三个参数是一个指定输出地址的迭代器，这里是一个 `ostream` 迭代器
- int
  ```cpp
  std::hash<int> hash_int;// Function object to hash int
  std::vector<int>n {-5, -2, 2, 5, 10};
  std::transform(std::begin(n), std::end(n),std::ostream_iterator<size_t> (std:: cout," "),hash_int);
  ```
- double
  ```cpp
  std::hash<double> hash_double;
  std::vector<double> x {3.14,-2.71828, 99.0, 1.61803399,6.62606957E-34};
  std::transform(std::begin(x), std::end(x),std::ostream_iterator<size_t>(std::cout," "),hash_double);
  ```
- pointer
  ```cpp
  std::hash<Box*> hash_box; // Box class as in Chapter 2
  Box box{1, 2, 3};
  std:: cout << "Hash value = " << hash_box (&box)<<std::endl;    // Hash value = 2916986638
  ```
