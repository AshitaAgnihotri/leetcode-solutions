class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        // {weight, index}
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> available;
        // {finishTime, weight, index}
        priority_queue<tuple<long long,int,int>,
                       vector<tuple<long long,int,int>>,
                       greater<tuple<long long,int,int>>> busy;
        int n = servers.size();
        for(int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }
        vector<int> ans(tasks.size());
        long long time = 0;
        for(int i = 0; i < tasks.size(); i++) {
            // Never move time backwards
            time = max(time, (long long)i);
            // Release all completed servers
            while(!busy.empty() && get<0>(busy.top()) <= time) {
                auto [finish, weight, index] = busy.top();
                busy.pop();
                available.push({weight, index});
            }
            // If all servers are busy, wait
            if(available.empty()) {
                time = get<0>(busy.top());
                while(!busy.empty() && get<0>(busy.top()) <= time) {
                    auto [finish, weight, index] = busy.top();
                    busy.pop();
                    available.push({weight, index});
                }
            }
            // Select the server with minimum weight, then index
            auto [weight, index] = available.top();
            available.pop();
            ans[i] = index;
            busy.push({time + tasks[i], weight, index});
        }
        return ans;
    }
};
