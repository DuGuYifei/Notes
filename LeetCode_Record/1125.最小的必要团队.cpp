#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=1125 lang=cpp
 *
 * [1125] 最小的必要团队
 *
 * https://leetcode.cn/problems/smallest-sufficient-team/description/
 *
 * algorithms
 * Hard (50.56%)
 * Likes:    166
 * Dislikes: 0
 * Total Accepted:    14K
 * Total Submissions: 22.9K
 * Testcase Example:  '["java","nodejs","reactjs"]\n[["java"],["nodejs"],["nodejs","reactjs"]]'
 *
 * 作为项目经理，你规划了一份需求的技能清单 req_skills，并打算从备选人员名单 people 中选出些人组成一个「必要团队」（ 编号为 i
 * 的备选人员 people[i] 含有一份该备选人员掌握的技能列表）。
 * 
 * 所谓「必要团队」，就是在这个团队中，对于所需求的技能列表 req_skills
 * 中列出的每项技能，团队中至少有一名成员已经掌握。可以用每个人的编号来表示团队中的成员：
 * 
 * 
 * 例如，团队 team = [0, 1, 3] 表示掌握技能分别为 people[0]，people[1]，和 people[3] 的备选人员。
 * 
 * 
 * 请你返回 任一 规模最小的必要团队，团队成员用人员编号表示。你可以按 任意顺序 返回答案，题目数据保证答案存在。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：req_skills = ["java","nodejs","reactjs"], people =
 * [["java"],["nodejs"],["nodejs","reactjs"]]
 * 输出：[0,2]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：req_skills = ["algorithms","math","java","reactjs","csharp","aws"],
 * people =
 * [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
 * 输出：[1,2]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * req_skills[i] 由小写英文字母组成
 * req_skills 中的所有字符串 互不相同
 * 1 
 * 0 
 * 1 
 * people[i][j] 由小写英文字母组成
 * people[i] 中的所有字符串 互不相同
 * people[i] 中的每个技能是 req_skills 中的技能
 * 题目数据保证「必要团队」一定存在
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        unordered_map<string, int> skillmap;
        for(const string& skill : req_skills){
            skillmap[skill] = skillmap.size();
        }
        int n = people.size();
        int m = req_skills.size();
        int dplen = 1 << m;
        vector<int> dp(dplen, n);
        dp[0] = 0;
        vector<int> prev_skillcombo(dplen);
        vector<int> next_person(dplen);
        for(int i = 0; i < n; i++){
            int mask = 0;
            for(const string& skill : people[i]){
                mask |= (1 << skillmap[skill]);
            }
            for(int j = 0; j < dplen; j++){
                int next = j | mask;
                if(next >= dplen) continue;
                if(dp[next] > dp[j] + 1){
                    dp[next] = dp[j] + 1;
                    prev_skillcombo[next] = j;
                    next_person[next] = i;
                }
            }
        }
        vector<int> ans;
        int i = dplen - 1;
        while(i){
            ans.push_back(next_person[i]);
            i = prev_skillcombo[i];
        }
        return ans;
    }
};
// @lc code=end

