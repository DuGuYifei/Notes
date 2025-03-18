#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=913 lang=cpp
 *
 * [913] 猫和老鼠
 */

// @lc code=start

class Solution
{
public:
    vector<vector<int>> graph;
    int state[51][51][51 * 2];
    int catMouseGame(vector<vector<int>> &graph)
    {
        this->graph = graph;
        memset(state, -1, sizeof(state));
        return JudgeResult(graph, 2, 1, 0);
    }

    int JudgeResult(vector<vector<int>> &graph, int cat, int mouse, int turn)
    {
        turn++;

        //key: 因为如果>2n 两人都有重复的位置，那么最佳答案又会一样不停重复
        if (turn > graph.size() * 2)
            return 0;

        if (mouse == 0)
            return 1;
        else if (cat == mouse)
            return 2;
        else
        {
            /******超级重点，记忆搜索，
            之所以停不下来就是因为这里没有想到过他会一直不停的向下探索，
            探索重复的点，
            虽然回合数不同但是次数实在是太多*/
            if (state[mouse][cat][turn] == -1)
                state[mouse][cat][turn] = GoNext(graph, cat, mouse, turn);

            else
                return state[mouse][cat][turn];
        }
        return state[mouse][cat][turn];
    }

    //key: 最佳状态可以理解为想办法让对方赢不了
    int GoNext(vector<vector<int>> &graph, int cat, int mouse, int turn)
    {
        //判断 当前回合的玩家 的位置
        int current = turn % 2 == 0 ? cat : mouse;

        int counterWin = turn % 2 == 0 ? 1 : 2;

        int realWin = counterWin;

        //**key: 通过遍历不让对方赢的可能 判断什么是最优解
        for (int i : graph[current])
        {
            if (turn % 2 == 0 && i == 0)
                continue;

            int nextResult = turn % 2 == 0 ? JudgeResult(graph, i, mouse, turn) : JudgeResult(graph, cat, i, turn);

            if (nextResult != counterWin)
            {
                realWin = nextResult;
                if (nextResult != 0)
                {
                    break;
                }
            }
        }

        return realWin;
    }
};
// @lc code=end
