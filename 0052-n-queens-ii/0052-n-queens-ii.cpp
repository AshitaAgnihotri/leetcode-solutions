class Solution {
public:
    bool isSafe(vector<string>& board, int row, int col) {
        int n = board.size();
        for (int j = 0; j < col; j++) {
            if (board[row][j] == 'Q') {
                return false;
            }
        }
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }
    void nQueens(vector<string>& board, int row, int& count) {
        int n = board.size();
        if (row == n) {
            count++;
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isSafe(board, row, col)){ 
                board[row][col] = 'Q';
                nQueens(board, row + 1, count);
                board[row][col] = '.';
            }
        }
    }
    int totalNQueens(int n) {
        int count = 0;
        vector<string> board(n, string(n, '.'));
        nQueens(board, 0, count);
        return count;
    }
};