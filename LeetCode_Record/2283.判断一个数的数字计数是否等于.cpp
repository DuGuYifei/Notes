#include <string>
using namespace std;
class Solution {
public:
    bool digitCount(string num) {
        int cnt[10] = {0};
        
        for(char& i : num){
            cnt[i - '0']++;
        }
        int n = num.size();
        for(int i = 0; i < n; i++){
            if(cnt[i] != num[i] - '0')
                return false;
        }
        return true;
    }
};