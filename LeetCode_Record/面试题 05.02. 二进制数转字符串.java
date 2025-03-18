class Solution {
    public String printBin(double num) {
        StringBuilder ans = new StringBuilder("0.");
        int cnt = 0;
        while(cnt < 6)
        {
            cnt++;
            num *= 2;
            int digit = (int)num;
            ans.append(digit);
            num -= digit;
            if(num == 0)
                return ans.toString();
        }
        return "ERROR";
    }
}