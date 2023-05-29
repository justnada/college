#include <stdio.h>
#include <stdbool.h>

void number_one() {
    int nada[2][5] = {2, 2, 1, 1, 5, 1, 0, 6, 9, 4};
    int nada_i, nada_j;

    printf("\n=== Jawaban nomor 1 ===\n");

    for (nada_i = 0; nada_i < 2; nada_i++) {
        for (nada_j = 0; nada_j < 5; nada_j++) {
            printf("%3i", nada[nada_i][nada_j]);
        }
        printf("\n");
    }
}

void number_two() {
    int nada[2][5] = {2, 2, 1, 1, 5, 1, 0, 6, 9, 4};
    int lingga[2][5] = {2, 2, 1, 1, 5, 1, 0, 6, 3, 7};
    
    printf("\n=== Jawaban nomor 2 ===\n");
    printf("Array yang ingin dikalikan tidak memenuhi syarat karena perbedaan panjang kolom dan baris, yaitu nada[2][5] dan lingga[2][5]\n");
}

void number_three() {
    int nada[2][5] = {2, 2, 1, 1, 5, 1, 0, 6, 9, 4};
    int lingga[2][5] = {2, 2, 1, 1, 5, 1, 0, 6, 3, 7};
    int result[2][5] = {};
    int nada_i, nada_j, nada_k;

    for (nada_i = 0; nada_i < 2; nada_i++) {
        for (nada_j = 0; nada_j < 5; nada_j++) {
           result[nada_i][nada_j] = nada[nada_i][nada_j] + lingga[nada_i][nada_j];
        }
    }

    printf("\n=== Jawaban nomor 3 ===\n");

    for (nada_i = 0; nada_i < 2; nada_i++) {
        for (nada_j = 0; nada_j < 5; nada_j++) {
            printf("%3d", result[nada_i][nada_j]);
        }
        printf("\n");
    }
}

void number_four() {
    int nada[2][5] = {2, 2, 1, 1, 5, 1, 0, 6, 9, 4};
    int lingga[2][5] = {2, 2, 1, 1, 5, 1, 0, 6, 3, 7};
    int nada_result[2][5] = {};
    int nada_i, nada_j, nada_k;

    for (nada_i = 0; nada_i < 2; nada_i++) {
        for (nada_j = 0; nada_j < 5; nada_j++) {
           nada_result[nada_i][nada_j] = nada[nada_i][nada_j] - lingga[nada_i][nada_j];
        }
    }

    printf("\n=== Jawaban nomor 4 ===\n");

    for (nada_i = 0; nada_i < 2; nada_i++) {
        for (nada_j = 0; nada_j < 5; nada_j++) {
            printf("%3d", nada_result[nada_i][nada_j]);
        }
        printf("\n");
    }
}

void number_five() {
    int nada[10] = {2, 2, 1, 1, 5, 1, 0, 6, 9, 4};
    int nada_n, nada_left = 0, nada_right = 9, nada_middle, nada_temp, nada_key, nada_i, nada_j;
    bool nada_found = false;
    
    printf("\n=== Jawaban nomor 5 ===\n");
    
    // sorting
    for (nada_i = 0; nada_i < 10; nada_i++) {
        for (nada_j = 0; nada_j < 10 - 1; nada_j++) {
            if (nada[nada_j] > nada[nada_j+1]) {
                nada_temp = nada[nada_j];
                nada[nada_j] = nada[nada_j+1];
                nada[nada_j+1] = nada_temp;
            }
        }
    }
    
    printf("Data telah diurutkan :");

    for (nada_i = 0; nada_i < 10; nada_i++) {
        printf("%3i", nada[nada_i]);
    }
    
    // input key
    printf("\nMasukan data yg dicari : "); scanf("%i", &nada_key);
    
    // binary search
    while (nada_left <= nada_right) {
        nada_middle = (nada_left + nada_right) / 2;
        
        if (nada_key == nada[nada_middle]) {
            nada_found = true;
            break;
        } else if (nada_key < nada[nada_middle]) {
            nada_right = nada_middle - 1;
        } else {
            nada_left = nada_middle + 1;
        }
    }
    
    if (nada_found) {
        printf("\nADA\n");
    } else {
        printf("\nTIDAK ADA\n");
    }
}

void number_six() {
    int nada[10] = {2, 2, 1, 1, 5, 1, 0, 6, 9, 4};
    int nada_n = 5, nada_key;
    bool nada_found = false;
    
    printf("\n=== Jawaban nomor 6 ===\n");
    
    // input key
    printf("Masukan data yg dicari : "); scanf("%i", &nada_key);
    
    // sequential search
    for (int i = 0; i < 10; i++) {
        if (nada_key == nada[i]) {
            nada_found = true;
            break;
        }
    }
    
    if (nada_found) {
        printf("\nADA\n");
    } else {
        printf("\nTIDAK ADA\n");
    }
}

void number_seven() {
    int nada[2][5] = {2, 2, 1, 1, 5, 1, 0, 6, 9, 4};
    int nada_key;
    bool nada_found = false;
    
    printf("\n=== Jawaban nomor 7 ===\n");
    
    // input key
    printf("Masukan data yg dicari : "); scanf("%i", &nada_key);
    
    // sequential search
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            if (nada_key == nada[i][j]) {
                nada_found = true;
                break;
            }
        }
    }
    
    if (nada_found) {
        printf("\nADA\n");
    } else {
        printf("\nTIDAK ADA\n");
    }
}

void main() {
  number_one();
  number_two();
  number_three();
  number_four();
  number_five();
  number_six();
  number_seven();
}