import java.util.HashMap;

class Solution {
    public String decodeMessage(String key, String message) {
        HashMap<Character, Character> keymap = new HashMap<>();
        int cnt = 0;
        for(int i = 0; i < 2000; i++){
            if(key.charAt(i) != ' ' && !keymap.containsKey(key.charAt(i))){
                keymap.put(key.charAt(i), (char)(cnt++ + 'a'));
                if(cnt == 26)
                    break;
            }
        }
        keymap.put(' ', ' ');
        StringBuilder str = new StringBuilder();
        int n = message.length();
        for(int i = 0; i < n; i++){
            str.append(keymap.get(message.charAt(i)));
        }
        return str.toString();
    }
}