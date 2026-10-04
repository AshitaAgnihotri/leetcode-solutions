class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;
        int high = 0;
        for (char ch : s) {
            if (ch == '(') {
                low++;
                high++;
            }
            else if (ch == ')') {
                low--;
                high--;
            }
            else {  // '*'
                low--;
                high++;
            }
            // Minimum cannot be negative
            low = max(0, low);
            // Even maximum is negative -> impossible
            if (high < 0) {
                return false;
            }
        }
        return low == 0;
    }
};