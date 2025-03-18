#include <queue>
#include <set>
#include <functional>
using namespace std;
/*
 * @lc app=leetcode.cn id=855 lang=cpp
 *
 * [855] 考场就座
 *
 * https://leetcode-cn.com/problems/exam-room/description/
 *
 * algorithms
 * Medium (40.99%)
 * Likes:    148
 * Dislikes: 0
 * Total Accepted:    10.4K
 * Total Submissions: 24.4K
 * Testcase Example:  '["ExamRoom","seat","seat","seat","seat","leave","seat"]\n' +
  '[[10],[],[],[],[],[4],[]]'
 *
 * 在考场里，一排有 N 个座位，分别编号为 0, 1, 2, ..., N-1 。
 * 
 * 
 * 当学生进入考场后，他必须坐在能够使他与离他最近的人之间的距离达到最大化的座位上。如果有多个这样的座位，他会坐在编号最小的座位上。(另外，如果考场里没有人，那么学生就坐在
 * 0 号座位上。)
 * 
 * 返回 ExamRoom(int N) 类，它有两个公开的函数：其中，函数 ExamRoom.seat() 会返回一个 int
 * （整型数据），代表学生坐的位置；函数 ExamRoom.leave(int p) 代表坐在座位 p 上的学生现在离开了考场。每次调用
 * ExamRoom.leave(p) 时都保证有学生坐在座位 p 上。
 * 
 * 
 * 
 * 示例：
 * 
 * 输入：["ExamRoom","seat","seat","seat","seat","leave","seat"],
 * [[10],[],[],[],[],[4],[]]
 * 输出：[null,0,9,4,2,null,5]
 * 解释：
 * ExamRoom(10) -> null
 * seat() -> 0，没有人在考场里，那么学生坐在 0 号座位上。
 * seat() -> 9，学生最后坐在 9 号座位上。
 * seat() -> 4，学生最后坐在 4 号座位上。
 * seat() -> 2，学生最后坐在 2 号座位上。
 * leave(4) -> null
 * seat() -> 5，学生最后坐在 5 号座位上。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= N <= 10^9
 * 在所有的测试样例中 ExamRoom.seat() 和 ExamRoom.leave() 最多被调用 10^4 次。
 * 保证在调用 ExamRoom.leave(p) 时有学生正坐在座位 p 上。
 * 
 * 
 */

// @lc code=start

class ExamRoom {
private:
    int n = 0;
    set<int> seats;
    struct cmp{
        bool operator()(const pair<int, int>& a,const pair<int, int>& b){
            int d1 = (a.second - a.first)/2, d2 = (b.second - b.first)/2;
            return d1 != d2? d1 < d2 : a.first > b.first;
        }
    };
    priority_queue<pair<int, int>, vector<pair<int,int>>, cmp>qu;
public:
    ExamRoom(int n):n(n){
    }
    
    int seat() {
        if(seats.size() == 0){
            seats.emplace(0);
            return 0;
        }
        int left = *seats.begin();
        int right = n - 1 - *seats.rbegin();
        while(seats.size() >= 2){
            auto [a, b] = qu.top();
            if(seats.count(a) == 0 || seats.count(b) == 0 || *next(seats.find(a)) != b ){
                qu.pop();
            }else{
                int d = (b - a) / 2;
                if(d <= left || d < right) 
                    break;
                qu.pop();
                qu.emplace(a, a + d);
                qu.emplace(a + d, b);
                seats.emplace(a + d);
                return a + d;
            }
        }
        if(right > left){
            qu.emplace(*seats.rbegin(), n - 1);
            seats.emplace(n - 1);
            return n - 1;
        }else{
            qu.emplace(0, *seats.begin());
            seats.emplace(0);
            return 0;
        }
    }
    
    void leave(int p) {
        if(p != *seats.begin() && p != *seats.rbegin()){
            auto it = seats.find(p);
            qu.emplace(*prev(it), *next(it));
        }
        seats.erase(p);
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */
// @lc code=end

