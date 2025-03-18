class Solution {
    private boolean sign, upper, lower, digit;

    public boolean strongPasswordCheckerII(String password) {
        int n = password.length();
        if(n < 8)
            return false;
        Character prev = password.charAt(0);
        charIs(prev);
        for(int i = 1; i < n; i++){
            Character now = password.charAt(i);
            if(now == prev)
                return false;
            prev = now;
            charIs(now);
        }
        if(sign && upper && lower && digit)
            return true;
        return false;
    }

    public void charIs(Character c){
        if(Character.isUpperCase(c))
            upper = true;
        else if(Character.isLowerCase(c))
            lower = true;
        else if(Character.isDigit(c))
            digit = true;
        else 
            sign = true;
    }
}