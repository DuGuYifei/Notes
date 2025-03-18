class Solution {
    public int countAsterisks(String s) {
        int n = s.length();
        int ans = 0;
        boolean open = false;
        for(int i = 0; i < n; i++){
            if(s.charAt(i) == '|')
                open = !open;
            else if(open && s.charAt(i) == '*')
                ans++;
        }
        return ans;
    }
}