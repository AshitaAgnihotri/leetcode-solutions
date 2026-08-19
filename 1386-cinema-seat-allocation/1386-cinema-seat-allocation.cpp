class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int,int> mp;
        for(auto &r: reservedSeats) {
            int row = r[0];
            int seat = r[1];
            if(seat >= 2 && seat <= 9)
                mp[row] |= (1 << seat);
        }
        int ans = (n - mp.size()) * 2;
        for(auto &[row, mask] : mp) {
            bool left = true, middle = true, right = true;
            for(int s = 2; s <= 5; s++)
                if(mask & (1 << s)) left = false;
            for(int s = 4; s <= 7; s++)
                if(mask & (1 << s)) middle = false;
            for(int s = 6; s <= 9; s++)
                if(mask & (1 << s)) right = false;
            if(left && right)
                ans += 2;
            else if(left || middle || right)
                ans += 1;
        }
        return ans;
    }
};