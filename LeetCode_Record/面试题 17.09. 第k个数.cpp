#include <vector>
using namespace std;
class Solution {
public:
    int getKthMagicNumber(int k) {
        vector<int> ls(k);
        ls[0] = 1;
        int a = 0, b = 0, c = 0;
        for(int i = 1; i < k; i++)
        {
            ls[i] = min({ls[a] * 3, ls[b] * 5, ls[c] * 7});
            if(ls[i] == ls[a] * 3)
                a++;
            if(ls[i] == ls[b] * 5)
                b++;
            if(ls[i] == ls[c] * 7)
                c++;
        }
        return ls[k - 1];
    }
};