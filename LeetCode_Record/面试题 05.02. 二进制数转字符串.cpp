#include <string>
using namespace std;

class Solution {
public:
    string printBin(double num) {
        string ans = "0.";
        int cnt = 0;
        while(cnt < 6)
        {
            cnt++;
            num *= 2;
            int digit = num;
            ans.push_back('0' + digit);
            num -= digit;
            if(num == 0)
                return ans;
        }
        return "ERROR";
    }
};