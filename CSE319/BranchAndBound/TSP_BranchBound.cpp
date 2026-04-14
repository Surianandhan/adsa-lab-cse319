#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define MAX 10
#define INF 9999

int final_path[MAX];
bool visited[MAX];
int final_cost = INF;

int reduceMatrix(int cost[MAX][MAX], int n, vector<bool>& rowRed, vector<bool>& colRed) {
    int reductionCost = 0;
    
    // Row reduction
    for (int i = 0; i < n; i++) {
        int minVal = INF;
        for (int j = 0; j < n; j++) {
            if (cost[i][j] < minVal && cost[i][j] != -1) {
                minVal = cost[i][j];
            }
        }
        if (minVal != INF && minVal != 0) {
            reductionCost += minVal;
            for (int j = 0; j < n; j++) {
                if (cost[i][j] != -1) {
                    cost[i][j] -= minVal;
                }
            }
        }
    }
    
    // Column reduction
    for (int j = 0; j < n; j++) {
        int minVal = INF;
        for (int i = 0; i < n; i++) {
            if (cost[i][j] < minVal && cost[i][j] != -1) {
                minVal = cost[i][j];
            }
        }
        if (minVal != INF && minVal != 0) {
            reductionCost += minVal;
            for (int i = 0; i < n; i++) {
                if (cost[i][j] != -1) {
                    cost[i][j] -= minVal;
                }
            }
        }
    }
    return reductionCost;
}

void copyMatrix(int dest[MAX][MAX], int src[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

void TSPBranchBound(int cost[MAX][MAX], int n, int curr_bound, int curr_weight, int level, int curr_path[]) {
    if (level == n) {
        if (cost[curr_path[level - 1]][curr_path[0]] != -1) {
            int curr_res = curr_weight + cost[curr_path[level - 1]][curr_path[0]];
            if (curr_res < final_cost) {
                for (int i = 0; i < n; i++) {
                    final_path[i] = curr_path[i];
                }
                final_path[n] = curr_path[0];
                final_cost = curr_res;
            }
        }
        return;
    }
    
    for (int i = 1; i < n; i++) {
        if (cost[curr_path[level - 1]][i] != -1 && !visited[i]) {
            int temp = curr_bound;
            curr_weight += cost[curr_path[level - 1]][i];
            
            // Create temporary cost matrix
            int temp_cost[MAX][MAX];
            copyMatrix(temp_cost, cost, n);
            
            // Set row and column to infinity
            for (int k = 0; k < n; k++) {
                temp_cost[curr_path[level - 1]][k] = -1;
                temp_cost[k][i] = -1;
            }
            temp_cost[i][0] = -1;
            
            vector<bool> rowRed(n, false), colRed(n, false);
            curr_bound = curr_bound + reduceMatrix(temp_cost, n, rowRed, colRed);
            
            if (curr_bound + curr_weight < final_cost) {
                visited[i] = true;
                curr_path[level] = i;
                TSPBranchBound(temp_cost, n, curr_bound, curr_weight, level + 1, curr_path);
            }
            
            curr_weight -= cost[curr_path[level - 1]][i];
            curr_bound = temp;
            
            for (int k = 0; k < n; k++) {
                visited[k] = false;
            }
            for (int k = 0; k < level; k++) {
                visited[curr_path[k]] = true;
            }
        }
    }
}

int solveTSP(int cost[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    
    int temp_cost[MAX][MAX];
    copyMatrix(temp_cost, cost, n);
    
    vector<bool> rowRed(n, false), colRed(n, false);
    int curr_bound = reduceMatrix(temp_cost, n, rowRed, colRed);
    
    int curr_path[MAX];
    visited[0] = true;
    curr_path[0] = 0;
    
    TSPBranchBound(temp_cost, n, curr_bound, 0, 1, curr_path);
    
    return final_cost;
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    
    int cost[MAX][MAX];
    cout << "Enter cost matrix (-1 for no edge):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
            if (i == j) cost[i][j] = -1;
        }
    }
    
    // Example matrix if user wants to skip input
    // int cost[MAX][MAX] = {
    //     {-1, 10, 15, 20},
    //     {10, -1, 35, 25},
    //     {15, 35, -1, 30},
    //     {20, 25, 30, -1}
    // };
    // n = 4;
    
    int minCost = solveTSP(cost, n);
    
    cout << "\nMinimum Tour Cost: " << minCost << endl;
    cout << "Tour Path: ";
    for (int i = 0; i <= n; i++) {
        cout << final_path[i] << " ";
    }
    cout << endl;
    
    return 0;
}