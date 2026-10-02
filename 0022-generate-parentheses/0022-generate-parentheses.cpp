class Solution {
public:
    vector<string> ans;
    void backtrack(string curr, int open, int close, int n) {
        if (curr.length() == 2 * n) {
            ans.push_back(curr);
            return;
        }
        if (open < n) {
            curr.push_back('(');
            backtrack(curr, open + 1, close, n);
            curr.pop_back();
        }
        if (close < open) {
            curr.push_back(')');
            backtrack(curr, open, close + 1, n);
            curr.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        backtrack("", 0, 0, n);
        return ans;
    }
};