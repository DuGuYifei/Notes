#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution
{
public:
	vector<string> findLongestSubarray(vector<string> &array)
	{
		unordered_map<int, int> m;
		m[0] = -1;
		int longest = 0;
		int left = -1, right = -1;
		int diff = 0;
		int n = array.size();
		for (int i = 0; i < n; i++)
		{
			if (isdigit(array[i][0]))
				diff++;
			else
				diff--;
			if (m.count(diff))
			{
				int t = i - m[diff];
				if (t > longest)
				{
					longest = t;
					left = m[diff];
					right = i;
				}
			}
			else
				m[diff] = i;
		}
		return vector<string>(array.begin() + left + 1, array.begin() + right + 1);
	}
};