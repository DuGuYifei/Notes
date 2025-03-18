#include <string>
using namespace std;

class Solution {
public:
    string greatestLetter(string s) {
        int letters[58] = {0};
        for(char& c : s){
            letters[c - 'A']++;
        }
        
        for(int i = 25; i >= 0; i--){
            if(letters[i] > 0 && letters[i + 32] > 0){
                return string(1, i + 'A');
            }
        }
        return "";
    }
};