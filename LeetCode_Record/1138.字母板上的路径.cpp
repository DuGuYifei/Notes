#include <string>
#include <utility>
using namespace std;
/*
 * @lc app=leetcode.cn id=1138 lang=cpp
 *
 * [1138] 字母板上的路径
 *
 * https://leetcode-cn.com/problems/alphabet-board-path/description/
 *
 * algorithms
 * Medium (43.67%)
 * Likes:    111
 * Dislikes: 0
 * Total Accepted:    24.1K
 * Total Submissions: 46.7K
 * Testcase Example:  '"leet"'
 *
 * 我们从一块字母板上的位置 (0, 0) 出发，该坐标对应的字符为 board[0][0]。
 * 
 * 在本题里，字母板为board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"]，如下所示。
 * 
 * 
 * 
 * 我们可以按下面的指令规则行动：
 * 
 * 
 * 如果方格存在，'U' 意味着将我们的位置上移一行；
 * 如果方格存在，'D' 意味着将我们的位置下移一行；
 * 如果方格存在，'L' 意味着将我们的位置左移一列；
 * 如果方格存在，'R' 意味着将我们的位置右移一列；
 * '!' 会把在我们当前位置 (r, c) 的字符 board[r][c] 添加到答案中。
 * 
 * 
 * （注意，字母板上只存在有字母的位置。）
 * 
 * 返回指令序列，用最小的行动次数让答案和目标 target 相同。你可以返回任何达成目标的路径。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：target = "leet"
 * 输出："DDR!UURRR!!DDD!"
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：target = "code"
 * 输出："RR!DDRR!UUL!R!"
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= target.length <= 100
 * target 仅含有小写英文字母。
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    const pair<int,int> board[26] =
    {
        {0,0},{0,1},{0,2},{0,3},{0,4},
        {1,0},{1,1},{1,2},{1,3},{1,4},
        {2,0},{2,1},{2,2},{2,3},{2,4},
        {3,0},{3,1},{3,2},{3,3},{3,4},
        {4,0},{4,1},{4,2},{4,3},{4,4},
        {5,0}
    };
    string alphabetBoardPath(string target  ) {
        string ans = "";
        int x = 0, y = 0;
        for(char& i : target)
        {
            int nx = board[i - 'a'].first;
            int ny = board[i - 'a'].second;

            if(nx < x)
                ans.append(x - nx, 'U');

            if(ny < y)
                ans.append(y - ny, 'L');

            if(nx > x)
                ans.append(nx - x, 'D');

            if(ny > y)
                ans.append(ny - y, 'R');


            ans.append(1, '!');

            x = nx;
            y = ny;
        } 

        return ans;
    }
};
// @lc code=end

