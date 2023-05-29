// Online C compiler to run C program online
#include <stdio.h>

int main() {
    int P[2][3] = {2, 1, 2, 1, 2, 3};
    int Q[3][3] = {2, 1, 4, 1, 2, 3, 2, 2, 1};
    int R[2][3] = {};
    int I, J, K;
    
    for (I = 0; I < 3; I++) {
        for (J = 0; J < 3; J++) {
            for (K = 0; K < 3; K++) {
                R[I][J] = R[I][J] + P[I][K] * Q[K][J];
            }
        }
    }
    
    for (I = 0; I < 2; I++) {
        for (J = 0; J < 3; J++) {
            printf("%3d", R[I][J]);
        }
        printf("\n");
    }
}