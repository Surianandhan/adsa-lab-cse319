#include <iostream>
using namespace std;

void MCO(int P[], int n) {
    int m[n][n];
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }
    
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = 9999;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + (P[i - 1] * P[k] * P[j]);
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        }
    }
    cout << m[1][n - 1] << endl;
}

int main() {
    int arr[] = {5, 3, 4, 2, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    MCO(arr, size);
    return 0;
}