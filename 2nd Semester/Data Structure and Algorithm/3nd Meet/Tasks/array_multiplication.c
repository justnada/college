#include <stdio.h>

int main() {
    int A[2][3] = {2, 4, 3, 3, 2, 5};
    int B[3][5] = {3, 2, 5, 7, 4, 2, 4, 6, 3, 2, 3, 3, 2, 5, 4};
    int C[2][5] = {};
    int I, J, K;
    
    for (I = 0; I < 3; I++) {
        for (J = 0; J < 5; J++) {
            for (K = 0; K < 3; K++) {
                C[I][J] = C[I][J] + A[I][K] * B[K][J];
            }
        }
    }
    
    for (I = 0; I < 2; I++) {
        for (J = 0; J < 5; J++) {
            printf("%3d", C[I][J]);
        }
        printf("\n");
    }
}