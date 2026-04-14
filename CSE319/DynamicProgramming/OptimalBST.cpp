#include <iostream>
using namespace std;

const int MAX_KEYS = 10;

void OptimalBST(int keys[], double P[], double Q[], int n) {
    double C[MAX_KEYS][MAX_KEYS] = {0};
    int R[MAX_KEYS][MAX_KEYS] = {0};
    double W[MAX_KEYS][MAX_KEYS] = {0};
    
    // Initialize weights
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (i == j) {
                W[i][j] = Q[i];
            } else {
                W[i][j] = W[i][j - 1] + P[j] + Q[j];
            }
        }
    }
    
    // Compute optimal costs
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (i == j) {
                C[i][j] = 0;
                R[i][j] = 0;
            } else {
                double minCost = 1e9;
                int root = -1;
                for (int k = i; k <= j; k++) {
                    double cost = C[i][k - 1] + C[k + 1][j] + W[i][j];
                    if (cost < minCost) {
                        minCost = cost;
                        root = k;
                    }
                }
                C[i][j] = minCost;
                R[i][j] = root;
            }
        }
    }
    
    cout << "Optimal cost: " << C[0][n] << endl;
}

int main() {
    int keys[] = {10, 20, 30, 40};
    double P[] = {0, 0.35, 0.8, 1.75, 2.95};
    double Q[] = {0.35, 0.8, 1.75, 2.95, 0};
    int n = 4;
    OptimalBST(keys, P, Q, n);
    return 0;
}