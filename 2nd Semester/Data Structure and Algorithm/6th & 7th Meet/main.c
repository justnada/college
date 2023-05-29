
// Online C compiler to run C program online
#include <stdio.h>

int main() {
    // bubble
    int n = 7;
    int A[7] = {15, 10, 7, 22, 17, 5, 12};
    int x, i, k;
    
    for (i = 0; i < n; i++) {
        printf("%4i", A[i]);
    }
    
    for (k = 0; k < n - 1; k++) {
        for (i = 0; i < n - 1 - k; i++) {
            // printf("\n%i > %i", A[i], A[i+1]);
            if (A[i] > A[i+1]) {
                x = A[i];
                A[i] = A[i+1];
                A[i+1] = x;
            }
        }
        // printf("\n");
    }
    
    printf("\n========================================\n");
    
    for (i = 0; i < n; i++) {
        printf("%4i", A[i]);
    }
    
    
    // selection
    // int n = 7;
    // int A[7] = {15, 10, 7, 22, 17, 5, 12};
    // int x, i, j, k;
    
    // for (i = 0; i < n; i++) {
    //     printf("%4i", A[i]);
    // }
    
    // printf("\n");
    
    // for (k = 0; k < n - 2; k++) {
    //     // printf("\nNilai K : %d", k);
        
    //     j = k;
        
    //     // printf("\nnilai j : %d", j);
        
    //     for (i = k+1; i <= n-1; i++) {
    //         if (A[i] < A[j]) {
    //             j = i;
    //         }
    //     }
        
    //     x = A[j];
    //     A[j] = A[k];
    //     A[k] = x;
    // }
    
    // printf("\n");
    
    // for (i = 0; i < n; i++) {
    //     printf("%4i", A[i]);
    // }
    
}