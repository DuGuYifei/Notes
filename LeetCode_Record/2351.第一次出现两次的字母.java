class Solution {
    public char repeatedCharacter(String s) {
        boolean letters[] = new boolean[26];
        for(int i = 0; i < 26; i++){
            int c = s.charAt(i) - 'a';
            if(letters[c])
                return s.charAt(i);
            letters[c] = true;
        }
        return 'a';
    }
}