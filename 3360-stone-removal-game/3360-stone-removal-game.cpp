class Solution {
public:
    bool canAliceWin(int n) {
        int remove = 10;

        while (n >= remove) {
            n -= remove;
            remove--;
        }

        return remove % 2 == 1;
    }
};