class Solution {
public:
    int sumOfSquares(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for(int i=1; i<= nums.size(); i++){
            int ele = nums[i-1];
            if(n%i == 0){  //Special Number
                sum += (ele * ele);
            }
        }
        return sum;
    }
};