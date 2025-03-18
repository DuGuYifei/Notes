class Solution {
    public int minMaxGame(int[] nums) {
        int n = nums.length;
        while(n > 1){
            for(int i = 0; i < n/2; i++){
                if(i % 2 == 1){
                    nums[i] = Math.max(nums[i * 2], nums[i * 2 + 1]);
                }else{
                    nums[i] = Math.min(nums[i * 2], nums[i * 2 + 1]);
                }
            }
            n /= 2;
        }
        return nums[0];
    }
}