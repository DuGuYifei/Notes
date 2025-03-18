#include <string>
using namespace std;

class Solution {
public:
    bool CheckPermutation(string s1, string s2) {
        int n = s1.size();
        int hashTable[26] = {0};
        if(s2.size() != n)
            return false;
        for(auto& i: s1){
            hashTable[i - 'a'] ++;
        }
        for(auto& i : s2){
            hashTable[i - 'a']--;
            if(hashTable[i-'a']<0)
                return false;
        }
        return true;
    }
};