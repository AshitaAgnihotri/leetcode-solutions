class Solution {
public:
    string smallestNumber(string num, long long t) {
        long long temp = t;
        for (int p : {2, 3, 5, 7}) {
            while (temp % p == 0) temp /= p;
        }
        if (temp > 1) return "-1";
        int n = num.length();
        auto get_primes = [](long long v) {
            vector<int> cnt(10, 0);
            for (int p : {2, 3, 5, 7}) {
                while (v % p == 0) { cnt[p]++; v /= p; }
            }
            return cnt;
        };
        vector<int> req = get_primes(t);
        int first_zero = n;
        for (int i = 0; i < n; i++) {
            if (num[i] == '0') { first_zero = i; break; }
        }
        auto min_digits_needed = [](vector<int> c) {
            int digits = 0;
            int n9 = c[3] / 2; c[3] %= 2; digits += n9;
            int n8 = c[2] / 3; c[2] %= 3; digits += n8;
            if (c[2] > 0 && c[3] > 0) { digits++; c[2]--; c[3]--; }
            int n4 = c[2] / 2; c[2] %= 2; digits += n4;
            digits += c[2] + c[3] + c[5] + c[7];
            return digits;
        };
        vector<vector<int>> pref(n + 1, vector<int>(10, 0));
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i];
            if (num[i] != '0') {
                int v = num[i] - '0';
                for (int p : {2, 3, 5, 7}) {
                    int tmp = v;
                    while (tmp % p == 0) { pref[i + 1][p]++; tmp /= p; }
                }
            }
        }
        if (first_zero == n) {
            bool ok = true;
            for (int p : {2, 3, 5, 7}) {
                if (pref[n][p] < req[p]) ok = false;
            }
            if (ok) return num;
        }
        for (int i = min(n - 1, first_zero); i >= 0; i--) {
            int start_digit = num[i] - '0' + 1;
            for (int d = start_digit; d <= 9; d++) {
                vector<int> cur_req = req;
                for (int p : {2, 3, 5, 7}) cur_req[p] = max(0, cur_req[p] - pref[i][p]);
                int tmp = d;
                for (int p : {2, 3, 5, 7}) {
                    while (tmp % p == 0) { cur_req[p] = max(0, cur_req[p] - 1); tmp /= p; }
                }
                int rem_len = n - 1 - i;
                if (min_digits_needed(cur_req) <= rem_len) {
                    string ans = num.substr(0, i);
                    ans += to_string(d);
                    string suf = "";
                    while (cur_req[7]--) suf += '7';
                    while (cur_req[5]--) suf += '5';
                    while (cur_req[3] >= 2) { suf += '9'; cur_req[3] -= 2; }
                    while (cur_req[2] >= 3) { suf += '8'; cur_req[2] -= 3; }
                    if (cur_req[2] > 0 && cur_req[3] > 0) { suf += '6'; cur_req[2]--; cur_req[3]--; }
                    while (cur_req[2] >= 2) { suf += '4'; cur_req[2] -= 2; }
                    if (cur_req[3] > 0) suf += '3';
                    if (cur_req[2] > 0) suf += '2';
                    while (suf.length() < rem_len) suf += '1';
                    sort(suf.begin(), suf.end());
                    return ans + suf;
                }
            }
        }
        string ans = "";
        while (req[7]--) ans += '7';
        while (req[5]--) ans += '5';
        while (req[3] >= 2) { ans += '9'; req[3] -= 2; }
        while (req[2] >= 3) { ans += '8'; req[2] -= 3; }
        if (req[2] > 0 && req[3] > 0) { ans += '6'; req[2]--; req[3]--; }
        while (req[2] >= 2) { ans += '4'; req[2] -= 2; }
        if (req[3] > 0) ans += '3';
        if (req[2] > 0) ans += '2';
        while (ans.length() <= n) ans += '1';
        sort(ans.begin(), ans.end());
        return ans;
    }
};