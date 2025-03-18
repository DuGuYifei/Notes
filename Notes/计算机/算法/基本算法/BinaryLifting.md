# BinaryLifting

## 原理

1. `dp[i][j]` 表示从 i 节点开始，跳 2^j 步后到达的节点。
2. `dp[i][j - 1] = dp[dp[i][j - 1]][j - 1]`，即从 i 节点开始，跳 2^(j - 1) 步后到达的节点，再跳 2^(j - 1) 步后到达的节点，即为从 i 节点开始，跳 2^j 步后到达的节点。
3. 查询时，很难懂，其实就是把 k 转换为二进制，然后从低位到高位，如果该位为 1，则跳 2^j 步，直到 k 为 0。

## 代码
[力扣](https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/)

```cpp
class TreeAncestor {

private:
	vector<vector<int>> dp;
	int maxPow;

public:
	TreeAncestor(int n, vector<int>& parent){
		maxPow = log2(n) + 1;
		dp.resize(n, vector<int>(maxPow, -1));
		for(int i = 0; i < n; i++){
			// 距离为 1 的节点
			dp[i][0] = parent[i];
		}
		for(int j = 1; j < maxPow; j++){
			for(int i = 0; i < n; i++){
				if(dp[i][j - 1] != -1){
					dp[i][j] = dp[dp[i][j - 1]][j - 1];
				}
			}
		}
	}

	int getKthAncestor(int node, int k){
        for(int j = 0; j < Log; j++){
            if((k >> j) & 1){
                node = ancestors[node][j];
                if(node == -1){
                    break;
                }
            }
        }
        return node;
	}
}
