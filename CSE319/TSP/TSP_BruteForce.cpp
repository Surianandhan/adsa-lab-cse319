#include <iostream>
using namespace std;

#define MAXN 9
#define MAXM 100
#define MAXPER 40320
#define INF 9999

void GeneratePermutations(int a[], int s, int e, int p[][MAXN], int &pcnt, int vSize) {
    if (s == e) {
        for (int i = 0; i < vSize; i++) {
            p[pcnt][i] = a[i];
        }
        pcnt++;
    } else {
        for (int i = s; i <= e; i++) {
            swap(a[s], a[i]);
            GeneratePermutations(a, s + 1, e, p, pcnt, vSize);
            swap(a[s], a[i]);
        }
    }
}

bool NextPermutation(int Vertex[], int vSize, int P[][MAXN], int &pcnt) {
    if (pcnt == 0) return false;
    for (int i = 0; i < vSize; i++) {
        Vertex[i] = P[pcnt - 1][i];
    }
    pcnt--;
    return true;
}

int TSP(int Cost[][MAXN], int n, int s, int mintour[]) {
    int mincost = INF;
    int Vertex[MAXN];
    int P[MAXPER][MAXN];
    
    for (int i = 1, j = 0; i <= n; i++) {
        if (i != s) Vertex[j++] = i;
    }
    
    int vSize = n - 1;
    int pcnt = 0;
    GeneratePermutations(Vertex, 0, vSize - 1, P, pcnt, vSize);
    
    int tour[MAXN + 1], c;
    while (NextPermutation(Vertex, vSize, P, pcnt)) {
        c = 0;
        int curPathWeight = 0;
        int k = s;
        tour[c++] = s;
        for (int i = 0; i < vSize; i++) {
            tour[c++] = Vertex[i];
        }
        tour[c] = s;
        
        for (int i = 0; i < c; i++) {
            curPathWeight += Cost[tour[i]][tour[i + 1]];
        }
        
        if (curPathWeight < mincost) {
            mincost = curPathWeight;
            for (int i = 0; i <= n; i++) mintour[i] = tour[i];
        }
    }
    return mincost;
}