#include <vector>
#include <iostream>
using namespace std;

#define MAXM 100
#define MAXN 50

bool isSafe(int board[][MAXN], int n, int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i][col]) return false;
    
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;
    
    for (int i = row, j = col; i >= 0 && j < n; i--, j++)
        if (board[i][j]) return false;
    
    return true;
}

bool PlaceQueen(int board[MAXM][MAXN], int n, int r, int Solutions[MAXM][MAXN], int &m) {
    if (r == n) {
        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 1)
                    Solutions[m][k++] = j + 1;
            }
        }
        m++;
        return true;
    }
    
    bool res = false;
    for (int c = 0; c < n; c++) {
        if (isSafe(board, n, r, c)) {
            board[r][c] = 1;
            res = PlaceQueen(board, n, r + 1, Solutions, m) || res;
            board[r][c] = 0;
        }
    }
    return res;
}

int main() {
    int n;
    cout << "Enter number of Queens: ";
    cin >> n;
    
    int board[MAXM][MAXN] = {0};
    int Solutions[MAXM][MAXN] = {0};
    int m = 0;
    
    PlaceQueen(board, n, 0, Solutions, m);
    
    cout << "Number of Solutions Found: " << m << endl;
    for (int i = 0; i < m; i++) {
        cout << i + 1 << ". [";
        for (int j = 0; j < n; j++) {
            cout << Solutions[i][j];
            if (j < n - 1) cout << " ";
        }
        cout << "]" << endl;
    }
    return 0;
}