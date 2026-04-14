#include <iostream>
#include <vector>
using namespace std;

#define MAX 20

struct Vertex {
    vector<int> AdjList;
    int Value;
    int Parent;
    int Distance;
};

class Graph {
    Vertex* V;
    int size;
    void Relax(int, int, int[MAX][MAX]);
    
public:
    Graph(int);
    void AddEdge(int, int);
    bool BellmanFord(int[MAX][MAX], int);
    void ShowGraph();
};

Graph::Graph(int n) {
    size = n;
    V = new Vertex[n];
    for (int i = 0; i < n; i++) {
        V[i].Value = i;
        V[i].Parent = -1;
        V[i].Distance = 9999;
    }
}

void Graph::Relax(int u, int v, int w[MAX][MAX]) {
    if (V[v].Distance > V[u].Distance + w[u][v]) {
        V[v].Distance = V[u].Distance + w[u][v];
        V[v].Parent = u;
    }
}

bool Graph::BellmanFord(int w[MAX][MAX], int s) {
    V[s].Distance = 0;
    
    for (int i = 1; i <= size - 1; i++) {
        for (int u = 0; u < size; u++) {
            for (int v = 0; v < size; v++) {
                if (w[u][v] != 0) {
                    Relax(u, v, w);
                }
            }
        }
    }
    
    for (int u = 0; u < size; u++) {
        for (int v = 0; v < size; v++) {
            if (w[u][v] != 0 && V[v].Distance > V[u].Distance + w[u][v]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n = 5;
    int Cost[MAX][MAX] = {
        {0, 6, 0, 0, 7},
        {0, 0, 5, -4, 8},
        {0, -2, 0, 0, 0},
        {2, 0, 7, 0, 0},
        {0, 0, -3, 9, 0}
    };
    
    Graph g(n);
    int source = 0;
    
    if (g.BellmanFord(Cost, source)) {
        cout << "Shortest distances from source " << source << ":\n";
        for (int i = 0; i < n; i++) {
            cout << "Vertex " << i << ": " << g.V[i].Distance << endl;
        }
    } else {
        cout << "Graph contains negative weight cycle" << endl;
    }
    
    return 0;
}