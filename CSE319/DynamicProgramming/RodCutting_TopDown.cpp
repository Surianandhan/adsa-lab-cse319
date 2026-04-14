#include <iostream>
using namespace std;

int maxRevenue(int p[], int n) {
    if (n == 0) return 0;
    int maxRev = -999999;
    for (int i = 1; i <= n; i++) {
        int r = maxRevenue(p, n - i);
        if ((p[i] + r) > maxRev) {
            maxRev = p[i] + r;
        }
    }
    return maxRev;
}

int main() {
    int p[] = {0, 1, 5, 8, 9};
    int n = 4;
    int result = maxRevenue(p, n);
    cout << "Max revenue is " << result << endl;
    return 0;
}