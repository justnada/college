// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>

void main() {
   int n, angka[12], kiri, kanan, tengah, temp, key;
   bool ketemu = false;

   printf("Masukan jumlah data : "); scanf("%i", &n);

   for (int i = 0; i < n ; i++) {
    printf("Angka ke - [%i] : ", i); scanf("%i", &angka[i]);
   }

    // sorting
    for (int i = 0; i<n; i++) {
        for (int j=0; j<n-1;j++) {
            if (angka[j] > angka[j+1]) {
                temp = angka[j];
                angka[j] = angka[j+1];
                angka[j+1]=temp;
            }

        }
    }

    printf("Data yg telah diurutkan adalah :");

    for (int i = 0; i < n; i++) {
        printf("\n%i", angka[i]);
    }
    
    printf("\nMasukan data yg dicari :"); scanf("%i", &key);
    
    kiri = 0;
    kanan = n -1;
    
    while (kiri <= kanan) {
        tengah = (kiri + kanan) / 2;
        
        if (key == angka[tengah]) {
            ketemu = true;
            break;
        } else if (key < angka[tengah]) {
            kanan = tengah - 1;
        } else {
            kiri = tengah + 1;
        }
    }
    
    if (ketemu == true) {
        printf("\nAngka ditemukan");
        printf("\nData berada pada index ke - %i", tengah);
    } else {
        printf("\nAngka tidak ditemukan");
    }
}