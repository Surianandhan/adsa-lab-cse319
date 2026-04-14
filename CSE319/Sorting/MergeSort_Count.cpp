#include <iostream>
#include <stdlib.h>
using namespace std;

int comparisons = 0, swaps = 0;

void merge(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++) L[i] = A[p + i];
    for (int j = 0; j < n2; j++) R[j] = A[q + 1 + j];
    
    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            swaps++;
            j++;
        }
        k++;
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
}

void mergeSort(int A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main() {
    int sizes[] = {1000, 2000, 5000};
    
    for (int j = 0; j < 3; j++) {
        int n = sizes[j];
        int* A = new int[n];
        
        // Ordered input
        for (int i = 0; i < n; i++) A[i] = i;
        comparisons = 0, swaps = 0;
        mergeSort(A, 0, n - 1);
        cout << "n=" << n << " Ordered: Comparisons=" << comparisons << " Swaps=" << swaps << endl;
        
        // Reverse ordered input
        for (int i = 0; i < n; i++) A[i] = n - i;
        comparisons = 0, swaps = 0;
        mergeSort(A, 0, n - 1);
        cout << "n=" << n << " Reverse: Comparisons=" << comparisons << " Swaps=" << swaps << endl;
        
        // Random input
        for (int i = 0; i < n; i++) A[i] = rand() % n;
        comparisons = 0, swaps = 0;
        mergeSort(A, 0, n - 1);
        cout << "n=" << n << " Random: Comparisons=" << comparisons << " Swaps=" << swaps << endl;
        
        delete[] A;
    }
    return 0;
}