# hash<T>和自构建hash函数给hashset

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

## hash for unordered_set
```cpp
auto hash_p = [](const pair<int, int> &p) -> size_t {
  static hash<long long> hash_ll;
  return hash_ll(p.first + (static_cast<long long>(p.second) << 32));
};
unordered_set<pair<int, int>, decltype(hash_p)> points(0, hash_p);
```

## hash for unordered_map
```cpp
static constexpr auto tri_hash = [fn = hash<int>()](const tuple<int, int, int>& o) -> size_t {
        auto&& [x, y, z] = o;
        return (fn(x) << 24) ^ (fn(y) << 8) ^ fn(z);
    };  

unordered_map<tuple<int, int, int>, pair<TreeNode*, int>, decltype(tri_hash)> seen{0, tri_hash};
```

## 更优雅的自定义方式

hashset同理

```cpp
struct VectorHash {
    std::size_t operator()(const std::vector<int>& vec) const {
        std::size_t seed = vec.size();
        for (const auto& num : vec) {
            seed ^= std::hash<int>{}(num) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        
        unordered_map<vector<int>, int, VectorHash> vmap;
        int m = matrix.size();
        int n = matrix[0].size();
        int ans = 0;
        for(int i = 0; i < m; i++){
            vector<int> zeroTemp;
            vector<int> oneTemp;
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == 0){
                    zeroTemp.push_back(j);
                }else{
                    oneTemp.push_back(j);
                }
            }
            vmap[zeroTemp]++;
            vmap[oneTemp]++;
            ans = max(ans, vmap[zeroTemp]);
            ans = max(ans, vmap[oneTemp]);
        }
        return ans;
    }
};
```