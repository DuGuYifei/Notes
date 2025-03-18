class Solution {
    public String greatestLetter(String s) {
        int[] letters = new int[58];
        int n = s.length();
        for(int i = 0; i < n; i++){
            letters[s.charAt(i) - 'A']++;
        }
        
        for(int i = 25; i >= 0; i--){
            if(letters[i] > 0 && letters[i + 32] > 0){
                return String.valueOf((char)(i + 'A'));
            }
        }
        return "";
    }
}