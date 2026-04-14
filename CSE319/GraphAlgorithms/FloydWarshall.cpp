#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 20
#define INF 99999
#define NIL -1

void FloydWarshall(int Cost[MAX][MAX], int Dist[MAX][MAX], int Parent[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Dist[i][j] = Cost[i][j];
            if (Cost[i][j] == 0 || Cost[i][j] == INF) {
                Parent[i][j] = NIL;
            } else {
                Parent[i][j] = i;
            }
        }
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (Dist[i][k] + Dist[k][j] < Dist[i][j]) {
                    Dist[i][j] = Dist[i][k] + Dist[k][j];
                    Parent[i][j] = Parent[k][j];
                }
            }
        }
    }
}

int main() {
    int n = 5;
    int Cost[MAX][MAX] = {
        {0, 3, 8, INF, -4},
        {INF, 0, INF, 1, 7},
        {INF, 4, 0, INF, INF},
        {2, INF, -5, 0, INF},
        {INF, INF, INF, 6, 0}
    };
    
    int Dist[MAX][MAX], Parent[MAX][MAX];
    FloydWarshall(Cost, Dist, Parent, n);
    
    cout << "Distance Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (Dist[i][j] == INF) cout << "INF\t";
            else cout << Dist[i][j] << "\t";
        }
        cout << endl;
    }
    
    return 0;
}