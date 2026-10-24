class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        auto convertToDays = [&](string date) {
            int month = stoi(date.substr(0, 2));
            int day = stoi(date.substr(3, 2));
            int total = day;
            for (int i = 0; i < month - 1; i++) {
                total += daysInMonth[i];
            }
            return total;
        };
        int aliceStart = convertToDays(arriveAlice);
        int aliceEnd = convertToDays(leaveAlice);
        int bobStart = convertToDays(arriveBob);
        int bobEnd = convertToDays(leaveBob);
        int start = max(aliceStart, bobStart);
        int end = min(aliceEnd, bobEnd);
        if (start > end) {
            return 0;
        }
        return end - start + 1;
    }
};