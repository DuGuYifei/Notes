#include <vector>
#include <queue>
using namespace std;

constexpr int directions[8][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},	{0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
};
class Solution {
private:
	vector<vector<bool>> visited;
public:
    vector<int> pondSizes(vector<vector<int>>& land) {
		int m = land.size();
		int n = land[0].size();
		visited = vector<vector<bool>>(m, vector<bool>(n, false));
		priority_queue<int, vector<int>, greater<int>> pq;
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				int cnt = dfs(i, j, land);
				if(cnt != 0)
					pq.push(cnt);
			}
		};
		vector<int> res;
		while(!pq.empty()){
			res.push_back(pq.top());
			pq.pop();
		}
		return res;
    }
	
	int dfs(int i, int j, vector<vector<int>>& land){
		if(i < 0 || i >= land.size() || j < 0 || j >= land[0].size() || visited[i][j] || land[i][j] != 0)
			return 0;
		visited[i][j] = true;
		int count = 1;
		for(int k = 0; k < 8; k++){
			count += dfs(i + directions[k][0], j + directions[k][1], land);
		}
		return count;
	}
};