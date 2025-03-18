#include <string>
using namespace std;

class Solution {
public:
    bool isFlipedString(string s1, string s2) {
        if(s1.size() == s2.size() && (s1 + s1).find(s2) != string::npos)
            return true;
        return false;
    }
};