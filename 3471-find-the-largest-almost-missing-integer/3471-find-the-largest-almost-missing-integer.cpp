class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,int> cnt;
        for(int i=0;i<=n-k;i++){
            unordered_set<int> seen;
            for(int j=i;j<i+k;j++){
                if(!seen.count(nums[j])){
                    cnt[nums[j]]++;
                    seen.insert(nums[j]);
                }
            }
        }
        int ans=-1;
        for(auto &[x,f]:cnt){
            if(f==1)
                ans=max(ans,x);
        }
        return ans;
    }
};