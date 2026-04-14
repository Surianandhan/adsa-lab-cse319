#include <iostream>
#include <vector>
using namespace std;

#define MAX 20
#define INF 99999

enum MyColor { W, G, B };

struct Vertex {
    vector<int> AdjList;
    int Value;
    MyColor Color;
    int Dist;
    int Parent;
};

int PathBFS(int b[MAX][MAX], int n, int s, int t, int Path[]) {
    Vertex* V = new Vertex[n];
    
    for (int i = 0; i < n; i++) {
        V[i].Value = i;
        V[i].Color = W;
        V[i].Dist = 9999;
        V[i].Parent = -1;
        V[i].AdjList.clear();
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (b[i][j] != 0) {
                V[i].AdjList.push_back(j);
            }
        }
    }
    
    V[s].Color = G;
    V[s].Dist = 0;
    V[s].Parent = -1;
    
    vector<int> Q;
    Q.push_back(s);
    
    while (Q.size() > 0) {
        int c = Q[0];
        Q.erase(Q.begin());
        for (int u : V[c].AdjList) {
            if (V[u].Color == W) {
                V[u].Color = G;
                V[u].Dist = V[c].Dist + 1;
                V[u].Parent = c;
                Q.push_back(u);
            }
        }
        V[c].Color = B;
    }
    
    int cnt = 0;
    Path[cnt++] = t;
    while (V[t].Parent != -1) {
        Path[cnt++] = V[t].Parent;
        t = V[t].Parent;
    }
    
    for (int i = 0, j = cnt - 1; i < j; i++, j--) {
        int temp = Path[i];
        Path[i] = Path[j];
        Path[j] = temp;
    }
    
    delete[] V;
    return cnt;
}

int MaxFlow(int b[MAX][MAX], int n, int s, int t) {
    int Path[MAX], cnt;
    int maxFlow = 0, minCap;
    
    while ((cnt = PathBFS(b, n, s, t, Path)) > 1) {
        minCap = INF;
        for (int i = 0; i < cnt - 1; i++) {
            int u = Path[i];
            int v = Path[i + 1];
            if (b[u][v] < minCap) minCap = b[u][v];
        }
        
        maxFlow += minCap;
        
        for (int i = 0; i < cnt - 1; i++) {
            int u = Path[i];
            int v = Path[i + 1];
            b[u][v] = b[u][v] - minCap;
            b[v][u] = b[v][u] + minCap;
        }
    }
    return maxFlow;
}

int main() {
    int n = 10;
    int b[MAX][MAX] = {
        {0, 12, 0, 0, 0, 20, 0, 3, 0, 0},
        {0, 0, 5, 0, 0, 0, 0, 0, 6, 0},
        {0, 0, 0, 13, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 12, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 10, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 0, 0, 5, 0},
        {0, 0, 0, 0, 0, 4, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 10, 0, 0, 0, 0, 0, 0}
    };
    
    cout << "\nMaximum Flow From 0 to 3: " << MaxFlow(b, n, 0, 3) << endl;
    return 0;
}