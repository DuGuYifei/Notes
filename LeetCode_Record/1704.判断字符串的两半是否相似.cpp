/*
 * @lc app=leetcode.cn id=1704 lang=cpp
 *
 * [1704] 判断字符串的两半是否相似
 *
 * https://leetcode-cn.com/problems/determine-if-string-halves-are-alike/description/
 *
 * algorithms
 * Easy (77.57%)
 * Likes:    19
 * Dislikes: 0
 * Total Accepted:    19.2K
 * Total Submissions: 24.8K
 * Testcase Example:  '"book"'
 *
 * 给你一个偶数长度的字符串 s 。将其拆分成长度相同的两半，前一半为 a ，后一半为 b 。
 * 
 * 两个字符串 相似 的前提是它们都含有相同数目的元音（'a'，'e'，'i'，'o'，'u'，'A'，'E'，'I'，'O'，'U'）。注意，s
 * 可能同时含有大写和小写字母。
 * 
 * 如果 a 和 b 相似，返回 true ；否则，返回 false 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "book"
 * 输出：true
 * 解释：a = "bo" 且 b = "ok" 。a 中有 1 个元音，b 也有 1 个元音。所以，a 和 b 相似。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "textbook"
 * 输出：false
 * 解释：a = "text" 且 b = "book" 。a 中有 1 个元音，b 中有 2 个元音。因此，a 和 b 不相似。
 * 注意，元音 o 在 b 中出现两次，记为 2 个。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 <= s.length <= 1000
 * s.length 是偶数
 * s 由 大写和小写 字母组成
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    bool halvesAreAlike(string s) {
        int n = s.size();
        int m = n/2;
        int i = 0;
        int left = 0, right = 0;
        for(; i < m; i++)
        {
            if(s[i] >= 'a' && s[i] <= 'e' || s[i] >= 'A' && s[i] <= 'E')
                left++;
        }
        for(;i<n;i++)
        {
            if(s[i] >= 'a' && s[i] <= 'e' || s[i] >= 'A' && s[i] <= 'E')
                right++;
        }
        return left == right;
    }
};
// class Solution {
// public:
//     bool halvesAreAlike(string s) {
//         string a = s.substr(0, s.size() / 2);
//         string b = s.substr(s.size() / 2);
//         string h = "aeiouAEIOU";
//         int sum1 = 0, sum2 = 0;
//         for (auto& i : a) {
//             if (h.find_first_of(i) != string::npos) {
//                 sum1++;
//             }
//         }
//         for (auto& i: b) {
//             if (h.find_first_of(i) != string::npos) {
//                 sum2++;
//             }
//         }
//         return sum1 == sum2;
//     }
// };
// @lc code=end

