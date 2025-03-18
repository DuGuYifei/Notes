# unordered_set转vector

```cpp
	unordered_set<int> a;
	a.insert(1);
	a.insert(2);
	a.insert(3);
	vector<int> b ={ a.begin(), a.end() };
	vector<int> b ({ a.begin(), a.end() });
	vector<int> b { a.begin(), a.end() };
	return 0;

//例2
unordered_set<TreeNode*> ans;
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) 
{
    dfs(root);
    return {ans.begin(), ans.end()};
}
```
