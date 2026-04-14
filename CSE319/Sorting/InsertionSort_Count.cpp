#include <iostream>
#include <stdlib.h>
using namespace std;

void insertionSort(int A[], int n, int &comparisons, int &swaps) {
    for (int j = 1; j < n; j++) {
        int key = A[j];
        int i = j - 1;
        while (i > -1 && A[i] > key) {
            comparisons++;
            A[i + 1] = A[i];
            swaps++;
            i = i - 1;
        }
        comparisons++;
        A[i + 1] = key;
    }
}

int main() {
    int sizes[] = {1000, 2000, 5000};
    
    for (int j = 0; j < 3; j++) {
        int n = sizes[j];
        int* A = new int[n];
        
        // Ordered input
        for (int i = 0; i < n; i++) A[i] = i;
        int comp = 0, swaps = 0;
        insertionSort(A, n, comp, swaps);
        cout << "n=" << n << " Ordered: Comparisons=" << comp << " Swaps=" << swaps << endl;
        
        // Reverse ordered input
        for (int i = 0; i < n; i++) A[i] = n - i;
        comp = 0, swaps = 0;
        insertionSort(A, n, comp, swaps);
        cout << "n=" << n << " Reverse: Comparisons=" << comp << " Swaps=" << swaps << endl;
        
        // Random input
        for (int i = 0; i < n; i++) A[i] = rand() % n;
        comp = 0, swaps = 0;
        insertionSort(A, n, comp, swaps);
        cout << "n=" << n << " Random: Comparisons=" << comp << " Swaps=" << swaps << endl;
        
        delete[] A;
    }
    return 0;
}