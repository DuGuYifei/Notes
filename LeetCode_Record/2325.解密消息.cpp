#include <unordered_map>
using namespace std;

class Solution {
public:
    string decodeMessage(string key, string message) {
        int cnt = 0;
        unordered_map<char, char> keymap;
        for (char& c : key) {
            if (c != ' ' && !keymap[c]) {
                keymap[c] = cnt++ + 'a';
                if (cnt == 26)
                    break;
            }
        }
        for (char& c : message) {
            if (c != ' ')
                c = keymap[c];
        }
        return message;
    }
};