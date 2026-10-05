class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);
        for (char ch : s) {
            if (ch == '(') {
                st.push(0);
            }
            else {
                int inside = st.top();
                st.pop();
                int score = max(2 * inside, 1);
                st.top() += score;
            }
        }
        return st.top();
    }
};