#include <string>
using namespace std;

class Solution {
public:
    int countAsterisks(string s) {
        bool start = true;
        int ans = 0;
        for(auto&i : s){
            if(i == '|')
                start = !start;
            else if(start && i == '*')
                ans++;
        }
        return ans;
    }
};