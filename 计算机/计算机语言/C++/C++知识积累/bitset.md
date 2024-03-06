# bitset
```cpp
class Solution {
public:
    bool queryString(string s, int n) {
        if(n >= 1024) return false;
        for(int i = (n >> 1) + 1; i <= n; i++){
            string temp = bitset<32>(i).to_string();
            if(s.find(temp.substr(temp.find_first_not_of('0'))) == string::npos) return false;
        }
        return true;
    }
};
```