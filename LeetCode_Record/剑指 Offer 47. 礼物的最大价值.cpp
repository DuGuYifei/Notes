#include <vector>
using namespace std;

class Solution
{
private:
	vector<vector<int>> gridV;
	int n, m;
public:
	int maxValue(vector<vector<int>> &grid)
	{
		m = grid.size();
		n = grid[0].size();
		gridV = vector<vector<int>>(m, vector<int>(n));
		return dfs(grid, 0, 0);
	}

	int dfs(vector<vector<int>> &grid, int x, int y){
		if(gridV[x][y])
			return gridV[x][y];
		int botV = 0;
		int rightV = 0;
		if(x + 1 < m)
			botV = dfs(grid, x + 1, y);
		if(y + 1 < n)
			rightV = dfs(grid, x, y + 1);
		gridV[x][y] = max(botV, rightV) + grid[x][y];
		return gridV[x][y];
	}
};