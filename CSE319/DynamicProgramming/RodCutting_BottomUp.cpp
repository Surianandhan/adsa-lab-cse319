#include <iostream>
using namespace std;

int maxRevenue(int p[], int n) {
    int r[n + 1];
    for (int j = 0; j <= n; j++) {
        if (j == 0) {
            r[j] = 0;
        } else {
            int mr = -9999;
            for (int i = 1; i <= j; i++) {
                if ((p[i] + r[j - i]) > mr) {
                    mr = p[i] + r[j - i];
                }
            }
            r[j] = mr;
        }
    }
    return r[n];
}

int main() {
    int p[] = {0, 1, 5, 8, 9};
    int n;
    cout << "Enter Number: ";
    cin >> n;
    cout << "Maximum Revenue: " << maxRevenue(p, n) << endl;
    return 0;
}