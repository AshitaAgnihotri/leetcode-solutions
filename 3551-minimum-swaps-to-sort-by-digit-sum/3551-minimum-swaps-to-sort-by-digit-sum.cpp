class Solution {
public:
    int digitSum(int num) {
        int sum = 0;

        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }

        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        vector<int> sortedNums = nums;

        sort(sortedNums.begin(), sortedNums.end(),
             [&](int a, int b) {
                 if (digitSum(a) == digitSum(b)) {
                     return a < b;
                 }
                 return digitSum(a) < digitSum(b);
             });

        unordered_map<int, int> position;

        for (int i = 0; i < n; i++) {
            position[sortedNums[i]] = i;
        }

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                continue;
            }

            int j = i;
            int cycleSize = 0;

            while (!visited[j]) {
                visited[j] = true;
                cycleSize++;

                j = position[nums[j]];
            }

            if (cycleSize > 1) {
                swaps += cycleSize - 1;
            }
        }

        return swaps;
    }
};
