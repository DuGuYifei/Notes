import java.lang.String;
import java.security.KeyStore.Entry;
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int rearrangeCharacters(String s, String target) {
        HashMap<Integer, Integer> chr = new HashMap<>();
        HashMap<Integer, Integer> chrt = new HashMap<>();
        s.chars().forEach(v -> chr.put(v, chr.getOrDefault(v, 0) + 1));
        target.chars().forEach(v -> chrt.put(v, chrt.getOrDefault(v, 0) + 1));
        int ans = Integer.MAX_VALUE;
        for(Map.Entry<Integer, Integer> e : chrt.entrySet()){
            if(chr.getOrDefault(e.getKey(), 0) < chrt.get(e.getKey()))
                return 0;
            ans = Integer.min(ans, chr.get(e.getKey())/chrt.get(e.getKey()));
        }
        return ans;
    }
}