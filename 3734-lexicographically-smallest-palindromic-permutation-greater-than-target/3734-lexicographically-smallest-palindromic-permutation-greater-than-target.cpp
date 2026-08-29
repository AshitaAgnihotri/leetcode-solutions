class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        vector<int> freq(26);
        for(char ch : s) freq[ch - 'a']++;
        int odd = 0, mid = -1;
        for(int i = 0; i < 26; i++) {
            if(freq[i] & 1) {
                odd++;
                mid = i;
            }
        }
        if(odd > 1) return "";
        for(int &cnt : freq) cnt /= 2;
        string ans = s;
        int half = ans.size() / 2;
        auto make = [&]() {
            if(mid != -1) ans[half] = 'a' + mid;
            int len = ans.size();
            for(int i = 0; i < half; i++)
                ans[len - 1 - i] = ans[i];
        };
        int pos = 0;
        while(pos < half) {
            int ch = target[pos] - 'a';
            if(freq[ch] == 0) break;
            ans[pos] = target[pos];
            freq[ch]--;
            pos++;
        }
        if(pos == half) {
            make();
            if(ans > target) return ans;
        }
        while(true) {
            if(pos < half) {
                int minChar = target[pos] - 'a' + 1;
                for(int ch = minChar; ch < 26; ch++) {
                    if(freq[ch] != 0) {
                        ans[pos] = 'a' + ch;
                        freq[ch]--;
                        int dst = pos + 1;
                        for(int c = 0; c < 26; c++) {
                            for(int off = 0; off < freq[c]; off++)
                                ans[dst + off] = 'a' + c;
                            dst += freq[c];
                        }
                        make();
                        return ans;
                    }
                }
            }
            if(pos == 0) return "";
            pos--;
            freq[target[pos] - 'a']++;
        }
    }
};