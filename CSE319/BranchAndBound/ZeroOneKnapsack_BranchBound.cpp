#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Item {
    int weight;
    int value;
};

struct Node {
    int level;
    int profit;
    int weight;
    double bound;
};

bool cmp(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double bound(Node u, int n, int W, Item items[]) {
    if (u.weight >= W) return 0;
    
    double profitBound = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;
    
    while (j < n && totalWeight + items[j].weight <= W) {
        totalWeight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }
    
    if (j < n) {
        profitBound += (W - totalWeight) * ((double)items[j].value / items[j].weight);
    }
    
    return profitBound;
}

int knapsackBranchBound(int W, Item items[], int n) {
    sort(items, items + n, cmp);
    
    queue<Node> Q;
    Node u, v;
    
    u.level = -1;
    u.profit = u.weight = 0;
    u.bound = bound(u, n, W, items);
    Q.push(u);
    
    int maxProfit = 0;
    
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        
        if (u.level == n - 1) continue;
        
        v.level = u.level + 1;
        
        // Take the item
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
        
        if (v.weight <= W && v.profit > maxProfit) {
            maxProfit = v.profit;
        }
        
        v.bound = bound(v, n, W, items);
        if (v.bound > maxProfit) {
            Q.push(v);
        }
        
        // Skip the item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, items);
        if (v.bound > maxProfit) {
            Q.push(v);
        }
    }
    
    return maxProfit;
}

int main() {
    int n, W;
    
    cout << "Enter number of items: ";
    cin >> n;
    
    Item items[n];
    cout << "Enter weight and value of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].value;
    }
    
    cout << "Enter knapsack capacity: ";
    cin >> W;
    
    int maxProfit = knapsackBranchBound(W, items, n);
    
    cout << "\nMaximum profit: " << maxProfit << endl;
    
    // Example test case
    // Item items[] = {{10, 60}, {20, 100}, {30, 120}};
    // n = 3, W = 50 -> Output: 220
    
    return 0;
}