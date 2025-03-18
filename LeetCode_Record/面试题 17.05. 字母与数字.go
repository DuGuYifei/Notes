package leetcode

func findLongestSubarray(array []string) []string {
	m := make(map[int]int)
	m[0] = -1
	longest := 0
	left := -1
	diff := 0
	n := len(array)
	for i := 0; i < n; i++ {
		if array[i][0] < 58 {
			diff++
		} else {
			diff--
		}
		if l, ok := m[diff]; ok {
			t := i - l
			if t > longest {
				longest = t
				left = l
			}
		} else {
			m[diff] = i
		}
	}
	if longest == 0 {
		return []string{}
	}
	return array[left+1 : left+longest+1]
}
