import java.util.HashMap;
import java.util.Map;

class Solution {
    public String[] findLongestSubarray(String[] array) {
		Map<Integer, Integer> m = new HashMap<>();
		m.put(0, -1);
		int longest = 0;
		int left = -1;
		int diff = 0;
		int n = array.length;
		for (int i = 0; i < n; i++)
		{
			if (Character.isDigit(array[i].charAt(0)))
				diff++;
			else
				diff--;
			if (m.containsKey(diff))
			{
				int t = i - m.get(diff);
				if (t > longest)
				{
					longest = t;
					left = m.get(diff);
				}
			}
			else
				m.put(diff, i);
		}
		String[] ans = new String[longest];
		System.arraycopy(array, left + 1, ans, 0, longest);
		return ans;
    }
}