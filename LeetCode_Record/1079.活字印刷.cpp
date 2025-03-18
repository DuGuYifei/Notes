#include <unordered_set>
#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1079 lang=cpp
 *
 * [1079] 活字印刷
 *
 * https://leetcode.cn/problems/letter-tile-possibilities/description/
 *
 * algorithms
 * Medium (73.84%)
 * Likes:    243
 * Dislikes: 0
 * Total Accepted:    30.6K
 * Total Submissions: 38.8K
 * Testcase Example:  '"AAB"'
 *
 * 你有一套活字字模 tiles，其中每个字模上都刻有一个字母 tiles[i]。返回你可以印出的非空字母序列的数目。
 * 
 * 注意：本题中，每个活字字模只能使用一次。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入："AAB"
 * 输出：8
 * 解释：可能的序列为 "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA"。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入："AAABBC"
 * 输出：188
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入："V"
 * 输出：1
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= tiles.length <= 7
 * tiles 由大写英文字母组成
 * 
 * 
 */

// @lc code=start
class Solution {
private:
    unordered_set<char> tileset;
public:
    int numTilePossibilities(string tiles) {
        int cnts[26] = {0};
        for(char c : tiles){
            cnts[c - 'A']++;
            tileset.insert(c);
        }
        return dfs(cnts, tiles.size()) - 1;
    }
    int dfs(int* cnts, int idx){
        if(idx == 0)
            return 1;
        int res = 1;//表示当前位置不放字母的情况
        for(char c : tileset){
            if(cnts[c - 'A'] > 0){
                cnts[c - 'A']--;
                res += dfs(cnts, idx - 1);
                cnts[c - 'A']++;
            }
        }
        return res;
    }
};
// @lc code=end

