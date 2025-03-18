/*
 * @lc app=leetcode.cn id=672 lang=cpp
 *
 * [672] 灯泡开关 Ⅱ
 */

// @lc code=start
class Solution {
public:
/*
int main()
{
    unordered_set<string> res;
    for(int i = 0; i < 2;i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0;k < 2; k++)
                for (int l = 0; l < 2; l++)
                {
                    bool b12 = (i + j)%2; // 6k 6k+2
                    bool b13 = (i + k)%2; // 6k+3 6k+5
                    bool b124 =(i + j + l)%2;  // 6k+1
                    bool b134 = (i + k + l)%2; // 6k+4
                    
                    string t = to_string(b12) + to_string(b13) + to_string(b124) + to_string(b134);
                    res.insert(t);
                }
    for (auto& i : res)
        cout << i <<endl;
    return 0;
}

输出：8种
1010
0101
0000
1100
1001
0011
0110
1111
*/
    int flipLights(int n, int presses) {
        if(n == 0 || presses == 0) return 1;
        if(n == 1) return 2; 
        if(n == 2) return presses == 1? 3:4;
        if(presses == 1) return 4;
        return presses == 2? 7:8;
    }
};
// @lc code=end

