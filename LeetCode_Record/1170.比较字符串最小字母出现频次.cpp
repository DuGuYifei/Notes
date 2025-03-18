#include <vector>
#include <string>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1170 lang=cpp
 *
 * [1170] 比较字符串最小字母出现频次
 *
 * https://leetcode.cn/problems/compare-strings-by-frequency-of-the-smallest-character/description/
 *
 * algorithms
 * Medium (61.75%)
 * Likes:    89
 * Dislikes: 0
 * Total Accepted:    26K
 * Total Submissions: 39.9K
 * Testcase Example:  '["cbd"]\n["zaaaz"]'
 *
 * 定义一个函数 f(s)，统计 s  中（按字典序比较）最小字母的出现频次 ，其中 s 是一个非空字符串。
 * 
 * 例如，若 s = "dcce"，那么 f(s) = 2，因为字典序最小字母是 "c"，它出现了 2 次。
 * 
 * 现在，给你两个字符串数组待查表 queries 和词汇表 words 。对于每次查询 queries[i] ，需统计 words 中满足
 * f(queries[i]) < f(W) 的 词的数目 ，W 表示词汇表 words 中的每个词。
 * 
 * 请你返回一个整数数组 answer 作为答案，其中每个 answer[i] 是第 i 次查询的结果。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：queries = ["cbd"], words = ["zaaaz"]
 * 输出：[1]
 * 解释：查询 f("cbd") = 1，而 f("zaaaz") = 3 所以 f("cbd") < f("zaaaz")。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
 * 输出：[1,2]
 * 解释：第一个查询 f("bbb") < f("aaaa")，第二个查询 f("aaa") 和 f("aaaa") 都 > f("cc")。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * 1 
 * queries[i][j]、words[i][j] 都由小写英文字母组成
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        int n = queries.size();
        int m = words.size();
        vector<int> wordsCount(m);
        m = 0;
        for(auto word : words){
            wordsCount[m++] = f(word);
        }
        sort(wordsCount.begin(), wordsCount.end());
        vector<int> res(n);
        for(int i = 0; i < n; i++){
            int count = f(queries[i]);
            res[i] = wordsCount.end() - upper_bound(wordsCount.begin(), wordsCount.end(), count);
        }
        return res;
    }

    int f(string s){
        int count[26] = {0};
        for(auto c : s){
            count[c - 'a']++;
        }
        for(int i = 0; i < 26; i++){
            if(count[i] != 0){
                return count[i];
            }
        }
        return 0;
    }
};
// @lc code=end

