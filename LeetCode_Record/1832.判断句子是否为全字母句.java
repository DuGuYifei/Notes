import java.util.Arrays;
import java.util.Collection;
import java.util.HashSet;

/*
 * @lc app=leetcode.cn id=1832 lang=java
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
    public boolean checkIfPangram(String sentence) {
        // HashSet<Character> chrs = new HashSet<>();
        // int n = sentence.length();
        // for(int i = 0; i < n; i++){
        //     chrs.add(sentence.charAt(i));
        // }
        // return chrs.size() == 26;
        int state = 0;
        int n = sentence.length();
        for(int i = 0; i < n; i++){
            state |= 1 << (sentence.charAt(i) - 'a');
        }
        return state == (1 << 26) - 1;
    }
}
// @lc code=end

