class Solution {
public:
    unordered_set<string> result;
    void dfs(string &s, int index,
             int leftRemove,
             int rightRemove,
             int balance,
             string current) {
        // Invalid balance
        if (balance < 0) {
            return;
        }
        // Reached the end
        if (index == s.size()) {
            if (leftRemove == 0 &&
                rightRemove == 0 &&
                balance == 0) {
                result.insert(current);
            }
            return;
        }
        char ch = s[index];
        // Case 1: '('
        if (ch == '(') {
            // Option 1: Remove it
            if (leftRemove > 0) {
                dfs(s, index + 1,
                    leftRemove - 1,
                    rightRemove,
                    balance,
                    current);
            }
            // Option 2: Keep it
            dfs(s, index + 1,
                leftRemove,
                rightRemove,
                balance + 1,
                current + ch);
        }
        // Case 2: ')'
        else if (ch == ')') {
            // Option 1: Remove it
            if (rightRemove > 0) {
                dfs(s, index + 1,
                    leftRemove,
                    rightRemove - 1,
                    balance,
                    current);
            }
            // Option 2: Keep it
            if (balance > 0) {
                dfs(s, index + 1,
                    leftRemove,
                    rightRemove,
                    balance - 1,
                    current + ch);
            }
        }
        // Case 3: normal character
        else {
            dfs(s, index + 1,
                leftRemove,
                rightRemove,
                balance,
                current + ch);
        }
    }
    vector<string> removeInvalidParentheses(string s) {
        int leftRemove = 0;
        int rightRemove = 0;
        // Find minimum number of removals needed
        for (char ch : s) {
            if (ch == '(') {
                leftRemove++;
            }
            else if (ch == ')') {
                if (leftRemove > 0) {
                    leftRemove--;
                }
                else {
                    rightRemove++;
                }
            }
        }
        string current = "";
        dfs(s, 0,
            leftRemove,
            rightRemove,
            0,
            current);
        return vector<string>(result.begin(), result.end());
    }
};