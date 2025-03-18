#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
		int n = reward1.size();
		vector<int> diff(n);
		int ans = 0;
		int cnt = 0;
		for(int i = 0; i < n; i++) {
			if(reward1[i] >= reward2[i]){
				ans += reward1[i];
				cnt++;
			}else{
				ans += reward2[i];
			}
			diff[i] = reward1[i] - reward2[i];
		}
		sort(diff.begin(), diff.end());
		int leftZero = lower_bound(diff.begin(), diff.end(), 0) - diff.begin();
		if(cnt < k) {
			int tmp = k - cnt;
			for(int i = 1; i <= tmp; i++) {
				ans += diff[leftZero - i];
			}
		}
		else if (cnt > k) {
			int tmp = cnt - k;
			for(int i = 0; i < tmp; i++) {
				ans -= diff[leftZero + i];
			}
		}
		return ans;
    }
};