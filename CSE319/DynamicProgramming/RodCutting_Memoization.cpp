#include <iostream>
#include <cstring>
using namespace std;

int memMaxRev(int p[], int r[], int n) {
    int maxRev;
    if (r[n] >= 0) return r[n];
    if (n == 0) {
        maxRev = 0;
    } else {
        maxRev = -999999;
        for (int i = 1; i <= n; i++) {
            int x = memMaxRev(p, r, n - i);
            if ((p[i] + x) > maxRev) {
                maxRev = p[i] + x;
            }
        }
    }
    r[n] = maxRev;
    return maxRev;
}

int maxRevenue(int p[], int n) {
    int r[n + 1];
    memset(r, -1, sizeof(r));
    return memMaxRev(p, r, n);
}

int main() {
    int p[] = {0, 1, 5, 8, 9};
    int n = 4;
    cout << "Max revenue is " << maxRevenue(p, n) << endl;
    return 0;
}