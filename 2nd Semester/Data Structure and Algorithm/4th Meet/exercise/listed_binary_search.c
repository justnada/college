// Online C compiler to run C program online
#include <stdio.h>

void main() {
    int array[5] = {1, 2, 3, 4, 5};
    int cari;
    int posisiTerendah = 0, posisiTertinggi = 5, posisiTengah;

    for (int i = 0; i  < 5; i++) {
        printf("Data %i tersimpan pada urutan ke -%i", array[i], i+1);
        printf("\n");
    }

    // process binary search
    printf("Masukkan bilangan yg anda cari = ");scanf("%i", &cari);

    while (posisiTerendah <= posisiTertinggi)
    {
        posisiTengah = (posisiTerendah + posisiTertinggi) / 2;

        if (cari > array[posisiTengah]) {
            posisiTerendah = posisiTengah + 1;
        } else if (cari < array[posisiTengah]) {
            posisiTertinggi = posisiTengah - 1;
        } else {
            posisiTerendah = posisiTertinggi + 1;
        }
    }
    
    if (cari == array[posisiTengah]) {
        printf("Data ditemukan pada urutan ke %i", posisiTengah + 1);
        printf("\n");
    } else {
        printf("Data yg dicari tidak ditemukan\n");
    }
    
}