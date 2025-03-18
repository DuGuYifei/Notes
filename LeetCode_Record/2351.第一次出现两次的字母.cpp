#include <string>
using namespace std;

class Solution {
public:
    char repeatedCharacter(string s) {
        bool letter[26] = {false};
        for(auto& i : s){
            int c = i - 'a';
            if(letter[c])
                return i;
            letter[c] = true;
        }
        return 'a';
    }
};