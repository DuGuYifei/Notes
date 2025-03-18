#include <vector>
#include <unordered_set>
using namespace std;
/*
 * @lc app=leetcode.cn id=1036 lang=cpp
 *
 * [1036] 逃离大迷宫
 */

// @lc code=start
class Solution
{
public:
    int area;
    bool findTarget = false;
    struct pair_hash
    {
        inline size_t operator()(const std::pair<int, int> &v) const
        {
            return v.first * 31 + v.second;
        };
    };

    unordered_set<pair<int, int>, pair_hash> haveGone;
    unordered_set<pair<int, int>, pair_hash> block;

    bool isEscapePossible(vector<vector<int>> &blocked, vector<int> &source, vector<int> &target)
    {
        area = blocked.size() * (blocked.size() - 1) / 2;

        for (auto i : blocked)
        {
            block.emplace(i[0], i[1]);
        }
        haveGone.emplace(source[0], source[1]);

        if (!getNeighbour(source[0], source[1], target[0], target[1]))
            return false;
        if (findTarget)
            return true;
        haveGone = {{target[0], target[1]}};
        return getNeighbour(target[0], target[1], source[0], source[1]);
    }

    bool getNeighbour(int sourceX, int sourceY, int targetX, int targetY)
    {
        bool havePath = false;
        if (sourceX + 1 < 1000000 && !haveGone.count({sourceX + 1, sourceY}) && !block.count({sourceX + 1, sourceY}))
        {
            if (sourceX + 1 == targetX && sourceY == targetY)
            {
                findTarget = true;
                return true;
            }
            haveGone.emplace(sourceX + 1, sourceY);

            if (haveGone.size() > area)
                return true;
            if (getNeighbour(sourceX + 1, sourceY, targetX, targetY))
            {
                if (findTarget)
                    return true;
                havePath = true;
            }
        }
        if (sourceY + 1 < 1000000 && !haveGone.count({sourceX, sourceY + 1}) && !block.count({sourceX, sourceY + 1}))
        {
            if (sourceX == targetX && sourceY + 1 == targetY)
            {
                findTarget = true;
                return true;
            }
            haveGone.emplace(sourceX, sourceY + 1);
            if (haveGone.size() > area)
                return true;
            if (getNeighbour(sourceX, sourceY + 1, targetX, targetY))
            {
                if (findTarget)
                    return true;
                havePath = true;
            }
        }
        if (sourceX - 1 >= 0 && !haveGone.count({sourceX - 1, sourceY}) && !block.count({sourceX - 1, sourceY}))
        {
            if (sourceX - 1 == targetX && sourceY == targetY)
            {
                findTarget = true;
                return true;
            }
            haveGone.emplace(sourceX - 1, sourceY);
            if (haveGone.size() > area)
                return true;
            if (getNeighbour(sourceX - 1, sourceY, targetX, targetY))
            {
                if (findTarget)
                    return true;
                havePath = true;
            }
        }
        if (sourceY - 1 >= 0 && !haveGone.count({sourceX, sourceY - 1}) && !block.count({sourceX, sourceY - 1}))
        {
            if (sourceX == targetX && sourceY - 1 == targetY)
            {
                findTarget = true;
                return true;
            }
            haveGone.emplace(sourceX, sourceY - 1);
            if (haveGone.size() > area )
                return true;
            if (getNeighbour(sourceX, sourceY - 1, targetX, targetY))
            {
                if (findTarget)
                    return true;
                havePath = true;
            }
        }
        return havePath;
    }
};
// @lc code=end
