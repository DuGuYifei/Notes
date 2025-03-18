#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=850 lang=cpp
 *
 * [850] 矩形面积 II
 */

// @lc code=start
class Solution
{
private:
    const int MOD = 1e9 + 7;

public:
    int rectangleArea(vector<vector<int>> &rectangles)
    {
        int n = rectangles.size();
        vector<int> hbound;
        for (const auto &rect : rectangles)
        {
            // 下边界
            hbound.push_back(rect[1]);
            // 上边界
            hbound.push_back(rect[3]);
        }
        sort(hbound.begin(), hbound.end());
        hbound.erase(unique(hbound.begin(), hbound.end()), hbound.end());
        int m = hbound.size();
        // 「思路与算法部分」的 length 数组并不需要显式地存储下来
        // length[i] 可以通过 hbound[i+1] - hbound[i] 得到
        vector<int> seg(m - 1);

        int nn = 2 * n;
        vector<tuple<int, int, int>> sweep(nn);
        for (int i = 0; i < n; ++i)
        {
            // 左边界
            sweep[2 * i] = {rectangles[i][0], i, 1};
            // 右边界
            sweep[2 * i + 1] = {rectangles[i][2], i, -1};
        }
        sort(sweep.begin(), sweep.end());

        long long ans = 0;
        for (int i = 0; i < nn; i++)
        {
            int j = i;
            int t = get<0>(sweep[i]);
            while (j + 1 < nn && get<0>(sweep[j + 1]) == t)
            {
                j++;
            }
            if (j + 1 == nn)
                break;

            // 一次性地处理掉一批横坐标相同的左右边界
            for (int k = i; k <= j; k++)
            {
                auto &&[_, idx, diff] = sweep[k];
                // left 是每个重复的横坐标所在矩形的下边界，right 是上边界
                int left = rectangles[idx][1], right = rectangles[idx][3];
                //遍历纵坐标段
                for (int x = 0; x < m - 1; x++)
                {
                    // 如果left，right所在的矩形
                    // *******有一部分在这段范围内**********
                    if (left <= hbound[x] && hbound[x + 1] <= right)
                    {
                        seg[x] += diff; 
                        // *******下面通过seg[k] > 0 判断这块区域到下一个横坐标是否被矩形包裹着********
                        //因此可以理解为，遇到这个横坐标之前有多少个矩形开始了，
                        //如果这里是某个矩形的右边界，就-1，是左边界，就+1
                        //其实遇见+1下面就一定有矩形包裹着，因为-1最多被前面自己的+1抵扣掉，seg[k]不可能为负数
                    }
                }
            }

            long long cover = 0;// 这条竖线被矩形覆盖的到的总长度
            for (int k = 0; k < m - 1; k++)
            {
                if (seg[k] > 0)
                {
                    cover += hbound[k + 1] - hbound[k];
                }
            }

            ans += cover * (get<0>(sweep[j + 1]) - get<0>(sweep[j]));
            i = j;
        }
        return ans % MOD;
    }
};
// @lc code=end
