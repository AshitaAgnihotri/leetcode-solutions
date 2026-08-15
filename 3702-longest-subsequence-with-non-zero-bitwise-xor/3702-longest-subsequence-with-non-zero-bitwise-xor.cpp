class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int x=0, n = nums.size();
        bool nonZero = false;
        for(int a :nums){
            x^=a;
            if(a != 0){
                nonZero = true;
            }
        }
        if(x!=0){
            return n;
        }
        if(nonZero){
            return n-1;
        }
        return 0;
    }
};