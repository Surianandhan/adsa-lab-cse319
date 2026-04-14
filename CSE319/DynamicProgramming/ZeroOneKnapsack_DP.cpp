#include <iostream>
using namespace std;

#define MAX_N 100
#define MAX_W 100

int knapsack(int wt[], int p[], int W, int n) {
    int m[MAX_N][MAX_W];
    
    for (int w = 0; w <= W; w++) m[0][w] = 0;
    for (int i = 0; i <= n; i++) m[i][0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i - 1] > w) {
                m[i][w] = m[i - 1][w];
            } else {
                m[i][w] = max(m[i - 1][w], p[i - 1] + m[i - 1][w - wt[i - 1]]);
            }
        }
    }
    return m[n][W];
}

int main() {
    int wt[] = {2, 3, 4, 5};
    int p[] = {3, 4, 5, 6};
    int n = 4;
    int W = 5;
    
    int maxProfit = knapsack(wt, p, W, n);
    cout << "Maximum profit obtained: " << maxProfit << endl;
    return 0;
}