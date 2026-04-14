#include <iostream>
using namespace std;

struct Object {
    int weight;
    int profit;
    double pw_ratio;
};

void sortObjects(Object objects[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (objects[j].pw_ratio < objects[j + 1].pw_ratio) {
                Object temp = objects[j];
                objects[j] = objects[j + 1];
                objects[j + 1] = temp;
            }
        }
    }
}

double fractionalKnapsack(Object objects[], int n, int capacity) {
    for (int i = 0; i < n; i++) {
        objects[i].pw_ratio = (double)objects[i].profit / objects[i].weight;
    }
    sortObjects(objects, n);
    
    double totalProfit = 0.0;
    int currentCapacity = capacity;
    
    for (int i = 0; i < n; i++) {
        if (currentCapacity == 0) break;
        if (objects[i].weight <= currentCapacity) {
            totalProfit += objects[i].profit;
            currentCapacity -= objects[i].weight;
        } else {
            totalProfit += objects[i].pw_ratio * currentCapacity;
            currentCapacity = 0;
        }
    }
    return totalProfit;
}

int main() {
    Object objects[] = {{10, 60}, {20, 100}, {30, 120}};
    int n = 3;
    int capacity = 50;
    double maxProfit = fractionalKnapsack(objects, n, capacity);
    cout << "Maximum profit obtained: " << maxProfit << endl;
    return 0;
}