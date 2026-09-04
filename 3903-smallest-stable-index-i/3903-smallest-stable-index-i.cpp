class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        for(int i = 0; i< nums.size() ; i++){
            int max = *max_element(nums.begin() , nums.begin() + (i+1));
            int min = *min_element(nums.begin() + i , nums.end());

            int instability_score = max - min ; 
            if(instability_score <= k){
                return i;
            }
        }
        return -1;
    }
};