class Solution {
	private int[][] gridV;
	private int n, m;

	public int maxValue(int[][] grid)
	{
		m = grid.length;
		n = grid[0].length;
		gridV = new int[m][n];
		return dfs(grid, 0, 0);
	}

	int dfs(int[][] grid, int x, int y){
		if(gridV[x][y] > 0)
			return gridV[x][y];
		int botV = 0;
		int rightV = 0;
		if(x + 1 < m)
			botV = dfs(grid, x + 1, y);
		if(y + 1 < n)
			rightV = dfs(grid, x, y + 1);
		gridV[x][y] = Math.max(botV, rightV) + grid[x][y];
		return gridV[x][y];
	}
}