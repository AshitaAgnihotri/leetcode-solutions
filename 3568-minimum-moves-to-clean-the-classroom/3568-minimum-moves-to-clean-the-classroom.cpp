class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        vector<vector<int>> litter(m, vector<int>(n, -1));
        int sx = 0, sy = 0;
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                else if (classroom[i][j] == 'L') {
                    litter[i][j] = cnt++;
                }
            }
        }
        if (cnt == 0)
            return 0;
        int totalMasks = 1 << cnt;
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
            n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(totalMasks, false)
                )
            )
        );
        int startMask = totalMasks - 1;
        queue<tuple<int, int, int, int>> q;
        q.push({sx, sy, energy, startMask});
        visited[sx][sy][energy][startMask] = true;
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        int moves = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto [x, y, curEnergy, mask] = q.front();
                q.pop();
                if (mask == 0)
                    return moves;
                if (curEnergy == 0)
                    continue;
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                        continue;
                    if (classroom[nx][ny] == 'X')
                        continue;
                    int newEnergy;
                    int newMask = mask;
                    newEnergy = curEnergy - 1;
                    if (classroom[nx][ny] == 'R') {
                        newEnergy = energy;
                    }
                    if (classroom[nx][ny] == 'L') {
                        int id = litter[nx][ny];
                        newMask &= ~(1 << id);
                    }
                    if (!visited[nx][ny][newEnergy][newMask]) {
                        visited[nx][ny][newEnergy][newMask] = true;
                        q.push({
                            nx,
                            ny,
                            newEnergy,
                            newMask
                        });
                    }
                }
            }
            moves++;
        }
        return -1;
    }
};