#include <unordered_set>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1832 lang=cpp
 *
 * [1832] 判断句子是否为全字母句
 *
 * https://leetcode-cn.com/problems/check-if-the-sentence-is-pangram/description/
 *
 * algorithms
 * Easy (82.20%)
 * Likes:    36
 * Dislikes: 0
 * Total Accepted:    24.3K
 * Total Submissions: 29.5K
 * Testcase Example:  '"thequickbrownfoxjumpsoverthelazydog"'
 *
 * 全字母句 指包含英语字母表中每个字母至少一次的句子。
 * 
 * 给你一个仅由小写英文字母组成的字符串 sentence ，请你判断 sentence 是否为 全字母句 。
 * 
 * 如果是，返回 true ；否则，返回 false 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：sentence = "thequickbrownfoxjumpsoverthelazydog"
 * 输出：true
 * 解释：sentence 包含英语字母表中每个字母至少一次。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：sentence = "leetcode"
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * sentence 由小写英语字母组成
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    bool checkIfPangram(string sentence) {
        // unordered_set<char> chrs;
        // for(auto& i : sentence){
        //     chrs.insert(i);
        // }
        // return chrs.size() == 26;
        int state = 0;
        for(char& i:sentence){
            state |= 1 << (i - 'a');
        }
        return state == (1 << 26) - 1;
    }
};
// @lc code=end

