import java.util.PriorityQueue;
import java.util.TreeSet;

/*
 * @lc app=leetcode.cn id=855 lang=java
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
    private int n;
    TreeSet<Integer> seats = new TreeSet<>();
    PriorityQueue<int[]>pq = new PriorityQueue<>((a,b) -> {
        int d1 = (a[1] - a[0])/2, d2 = (b[1] - b[0])/2;
        return d1 != d2? d2 - d1 : a[0] - b[0];
    });

    public ExamRoom(int n) {
        this.n = n;
    }
    
    public int seat() {
        if(seats.isEmpty()){
            seats.add(0);
            return 0;
        }
        int left = seats.first();
        int right = n - 1 - seats.last();
        while(seats.size() > 1){
            int[] top = pq.peek();
            if(seats.contains(top[0]) && seats.contains(top[1]) && seats.higher(top[0]) == top[1]){
                int d = (top[1] - top[0])/2;
                if(d <= left || d < right)
                    break;
                pq.poll();
                int seat = top[0] + d;
                pq.add(new int[]{top[0], seat});
                pq.add(new int[]{seat, top[1]});
                seats.add(seat);
                return seat;
            }
            pq.poll();
        }
        if(left < right){
            pq.add(new int[]{seats.last(), n - 1});
            seats.add(n - 1);
            return n - 1;
        }
        pq.add(new int[]{0, seats.first()});
        seats.add(0);
        return 0;
    }
    
    public void leave(int p) {
        if(p != seats.first() && p != seats.last()){
            pq.add(new int[]{seats.lower(p), seats.higher(p)});
        }
        seats.remove(p);
    }
}

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom obj = new ExamRoom(n);
 * int param_1 = obj.seat();
 * obj.leave(p);
 */
// @lc code=end

