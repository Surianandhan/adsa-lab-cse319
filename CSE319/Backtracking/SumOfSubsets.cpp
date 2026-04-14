#include <bits/stdc++.h>
#define MAXN 10
#define MAXM 1024
using namespace std;

struct Subset {
    int X[MAXN];
    int n;
    Subset(int size) {
        n = size;
        for (int i = 0; i < n; i++) X[i] = 0;
    }
    Subset() {}
};

void PrintSubset(Subset ssAll[], int solutionSize, int set[], int n) {
    cout << "\nNumber of Solutions: " << solutionSize;
    cout << "\nSolutions: ";
    for (int i = 0; i < solutionSize; i++) {
        cout << "\n\t[";
        for (int j = 0; j < n; j++) {
            if (ssAll[i].X[j]) cout << set[j] << " ";
        }
        cout << "]";
    }
}

void SubSetSum(int i, int n, int set[], int balanceSum, Subset ss, Subset ssAll[], int &solutionSize) {
    if (balanceSum < 0) return;
    if (balanceSum == 0) {
        ssAll[solutionSize++] = ss;
        return;
    }
    if (i == n) return;
    
    ss.X[i] = 1;
    SubSetSum(i + 1, n, set, balanceSum - set[i], ss, ssAll, solutionSize);
    
    ss.X[i] = 0;
    SubSetSum(i + 1, n, set, balanceSum, ss, ssAll, solutionSize);
}

int main() {
    int set1[] = {10, 7, 5, 18, 12, 20, 15};
    int sum = 35;
    int n = 7;
    Subset ss(n);
    Subset ssAll[MAXM];
    int solutionSize = 0;
    
    SubSetSum(0, n, set1, sum, ss, ssAll, solutionSize);
    cout << "Test Case 1:";
    PrintSubset(ssAll, solutionSize, set1, n);
    
    return 0;
}