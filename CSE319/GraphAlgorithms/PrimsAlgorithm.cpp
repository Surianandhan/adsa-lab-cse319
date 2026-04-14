#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define MAX 20

enum MyColor { W, B };

struct Vertex {
    vector<int> AdjList;
    int Value;
    MyColor Color;
    int Parent;
    int Key;
};

class Graph {
    Vertex* V;
    int size;
    
public:
    Graph(int);
    void AddEdge(int, int, int[MAX][MAX]);
    void Prims(int[MAX][MAX], int);
    bool ExtractMin(int&);
    void ShowSpanningTree();
};

Graph::Graph(int n) {
    size = n;
    V = new Vertex[n];
    for (int i = 0; i < n; i++) {
        V[i].Value = i;
        V[i].Color = W;
        V[i].Parent = -1;
        V[i].Key = 9999;
    }
}

void Graph::Prims(int Cost[MAX][MAX], int s) {
    V[s].Key = 0;
    int u;
    while (ExtractMin(u)) {
        V[u].Color = B;
        for (int v = 0; v < size; v++) {
            if (Cost[u][v] != 0 && V[v].Color == W && Cost[u][v] < V[v].Key) {
                V[v].Key = Cost[u][v];
                V[v].Parent = u;
            }
        }
    }
}

bool Graph::ExtractMin(int &u) {
    int minKey = 9999;
    u = -1;
    for (int i = 0; i < size; i++) {
        if (V[i].Color == W && V[i].Key < minKey) {
            minKey = V[i].Key;
            u = i;
        }
    }
    return u != -1;
}

void Graph::ShowSpanningTree() {
    int totalCost = 0;
    cout << "Minimum Spanning Tree Edges:\n";
    for (int i = 0; i < size; i++) {
        if (V[i].Parent != -1) {
            cout << V[i].Parent << "--" << i << " : " << V[i].Key << endl;
            totalCost += V[i].Key;
        }
    }
    cout << "Total Cost: " << totalCost << endl;
}

int main() {
    int n = 9;
    int Cost[MAX][MAX] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    
    Graph g(n);
    g.Prims(Cost, 0);
    g.ShowSpanningTree();
    
    return 0;
}