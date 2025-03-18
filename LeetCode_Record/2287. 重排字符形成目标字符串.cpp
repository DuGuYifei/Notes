#include <string>
using namespace std;

class Solution {
public:
    int rearrangeCharacters(string s, string target) {
        int chr[26] = {0};
        int chrt[26] = {0};
        for(char& i : s){
            chr[i - 'a']++;
        }
        for(char& i : target){
            chrt[i - 'a']++;
        }
        int ans = INT_MAX;
        for(int i = 0; i < 26; i++){
            if(chrt[i]){
                if(chr[i] < chrt[i])
                    return 0;
                ans = min(ans, chr[i] / chrt[i]);
            }
        }
        return ans;
    }
};