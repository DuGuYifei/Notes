#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1417 lang=cpp
 *
 * [1417] 重新格式化字符串
 */

// @lc code=start

//使用 malloc
// class Solution {
// public:
//     string reformat(string s) {
//         int nid = -1;
//         int sid = -2;
//         int n = s.size();
//         string ans = s + " ";
//         for (auto& c : s)
//         {
//             if (isdigit(c))
//             {
//                 nid += 2;
//                 if (nid > n)
//                     return "";
//                 ans[nid] = c;
//             }
//             else
//             {
//                 sid += 2;
//                 if (sid >= n)
//                     return "";
//                 ans[sid] = c;
//             }
//         }
//         if (nid == n && sid == n - 3)
//         {
//             ans[n - 1] = ans[0];
//             return ans.substr(1);
//         }
//         return ans.substr(0, n);
//     }
// };

class Solution {
public:
    string reformat(string s) {
        int nid = -1;
        int sid = -2;
        int n = s.size();
        string ans = s + " ";
        for (auto& c : s)
        {
            if (isdigit(c))
            {
                nid += 2;
                if (nid > n)
                    return "";
                ans[nid] = c;
            }
            else
            {
                sid += 2;
                if (sid >= n)
                    return "";
                ans[sid] = c;
            }
        }
        if (nid == n && sid == n - 3)
        {
            ans[n - 1] = ans[0];
            return ans.substr(1);
        }
        return ans.substr(0, n);
    }
};
// @lc code=end

