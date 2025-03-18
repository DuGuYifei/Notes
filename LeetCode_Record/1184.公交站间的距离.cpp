/*
 * @lc app=leetcode.cn id=1184 lang=cpp
 *
 * [1184] 公交站间的距离
 */

// @lc code=start

// 方法一------------------------------------------------
// class Solution {
// public:
//     int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
//         int d1 = 0, d2 = 0;
//         int n = distance.size();
//         for(int i = start; i != destination; i++)
//         {
//             if(i == n) 
//             {
//                 i = -1;
//                 continue;
//             }
//             d1 += distance[i];
//         }
//         if(destination == 0)
//             destination = n - 1;
//         destination--;
//         for(int i = start - 1; i != destination; i--)
//         {
//             if(i == -1)
//             {
//                 i = n - 1;
//             }
//             d2 += distance[i];
//         }
//         return min(d1,d2);
//     }
// };

//方法二------------------------------------------------
class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        if (start > destination) {
            swap(start, destination);
        }
        return min(accumulate(distance.begin() + start, distance.begin() + destination, 0),
                   accumulate(distance.begin(), distance.begin() + start, 0) +
                   accumulate(distance.begin() + destination, distance.end(), 0));
    }
};
// @lc code=end

