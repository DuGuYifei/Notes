#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
/*
 * @lc app=leetcode.cn id=1001 lang=cpp
 *
 * [1001] 网格照明
 */

// @lc code=start
class Solution
{
public:
    vector<int> gridIllumination(int n, vector<vector<int>> &lamps, vector<vector<int>> &queries)
    {
        vector<int> ans;
        unordered_map<int, int> row, col, diag, antidiag;
        pair<int, int> dirs[9] = {{0, 0}, {1, 0}, {1, 1}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
        auto hash_p = [](const pair<int, int> &p)
        {
           return hash<int>()(p.first) ^ hash<int>()(p.second);
        };
        unordered_set<pair<int, int>, decltype(hash_p)> lamp(0, hash_p);
        for (auto &i : lamps)
        {
            if (lamp.find({i[0], i[1]}) == lamp.end())
            {
                lamp.insert({i[0], i[1]});
                row[i[0]]++;
                col[i[1]]++;
                diag[i[1] - i[0]]++;
                antidiag[i[1] + i[0]]++;
            }
        }
        for (auto &i : queries)
        {
            int x = i[0], y = i[1];
            if (row[i[0]] > 0 || col[i[1]] > 0 || diag[i[1] - i[0]] > 0 || antidiag[i[1] + i[0]] > 0)
            {
                ans.push_back(1);
                for (auto &j : dirs)
                {
                    int nx = i[0] + j.first;
                    int ny = i[1] + j.second;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n)
                    {
                        auto p = lamp.find({nx, ny});
                        if (p != lamp.end())
                        {
                            lamp.erase(p);
                            row[nx]--;
                            col[ny]--;
                            diag[ny - nx]--;
                            antidiag[ny + nx]--;
                        }
                    }
                }
            }
            else
                ans.push_back(0);
        }
        return ans;
    }
};
// @lc code=end
