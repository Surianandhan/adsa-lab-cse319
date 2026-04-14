#include <iostream>
using namespace std;

#define MAX 20

enum MyColor { W, B };

struct Edge {
    int u, v;
    int Cost;
    MyColor Color;
};

struct Vertex {
    int value;
    int Set;
};

class Graph {
    Edge* E;
    Vertex* V;
    int nV, nE;
    
public:
    Graph(int, int, int[MAX][MAX]);
    void Kruskals();
    void SortEdges();
    void ShowSpanningTree();
};

void Graph::SortEdges() {
    for (int i = 0; i < nE; i++) {
        for (int j = i + 1; j < nE; j++) {
            if (E[j].Cost < E[i].Cost) {
                swap(E[i], E[j]);
            }
        }
    }
}

Graph::Graph(int e, int v, int w[MAX][MAX]) {
    nE = e;
    nV = v;
    E = new Edge[e];
    V = new Vertex[v];
    
    int idx = 0;
    for (int i = 0; i < v; i++) {
        for (int j = i + 1; j < v; j++) {
            if (w[i][j] != 0) {
                E[idx].u = i;
                E[idx].v = j;
                E[idx].Cost = w[i][j];
                E[idx].Color = W;
                idx++;
            }
        }
    }
    
    for (int i = 0; i < v; i++) {
        V[i].value = i;
        V[i].Set = i;
    }
}

void Graph::Kruskals() {
    SortEdges();
    int totalCost = 0;
    
    for (int i = 0; i < nE; i++) {
        int setU = V[E[i].u].Set;
        int setV = V[E[i].v].Set;
        
        if (setU != setV) {
            E[i].Color = B;
            totalCost += E[i].Cost;
            for (int j = 0; j < nV; j++) {
                if (V[j].Set == setV) {
                    V[j].Set = setU;
                }
            }
        }
    }
    
    cout << "Minimum Spanning Tree Edges:\n";
    for (int i = 0; i < nE; i++) {
        if (E[i].Color == B) {
            cout << E[i].u << "--" << E[i].v << " : " << E[i].Cost << endl;
        }
    }
    cout << "Total Cost: " << totalCost << endl;
}

int main() {
    int nV = 9;
    int nE = 14;
    
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
    
    Graph g(nE, nV, Cost);
    g.Kruskals();
    
    return 0;
}