class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        int start = 0, end = n-1;
        int currSum = 0;

        while(start < end){
            currSum = nums[start] + nums[end];
            if(currSum == target){
                return {start+1 , end+1};
            }else if(currSum > target){
                end-- ;
            }else{
                start++ ;
            }
        }
        return {};
    }
};