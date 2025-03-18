#include <string>
using namespace std;

class Solution {
public:
    bool strongPasswordCheckerII(string password) {
        if(password.size() < 8)
            return false;
        bool upper = false;
        bool lower = false;
        bool digit = false;
        bool sign = false;
        char prev = ' ';
        for(auto& i:password){
            if(i == prev)
                return false;
            prev = i;
            if(isdigit(i))
                digit = true;
            else if(isupper(i))
                upper = true;
            else if(islower(i))
                lower = true;
            else
                sign = true;
        }
        if(upper && lower && digit && sign)
            return true;
        return false;
    }
};