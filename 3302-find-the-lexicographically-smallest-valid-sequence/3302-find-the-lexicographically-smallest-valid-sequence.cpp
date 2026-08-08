class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<int> suf(m, -1);
        int j = m - 1;
        for (int i = n - 1; i >= 0 && j >= 0; i--) {
            if (word1[i] == word2[j]) {
                suf[j] = i;
                j--;
            }
        }
        vector<int> ans;
        int pos = 0;
        bool usedMismatch = false;
        for (int i = 0; i < m; i++) {
            if (pos < n && word1[pos] == word2[i]) {
                ans.push_back(pos);
                pos++;
                continue;
            }
            if (!usedMismatch && pos < n) {
                if (i == m - 1 ||
                    (suf[i + 1] != -1 && suf[i + 1] > pos)) {

                    ans.push_back(pos);
                    pos++;
                    usedMismatch = true;
                    continue;
                }
            }
            while (pos < n && word1[pos] != word2[i]) {
                pos++;
            }

            if (pos < n) {
                ans.push_back(pos);
                pos++;
            } else {
                return {};
            }
        }
        return ans;
    }
};