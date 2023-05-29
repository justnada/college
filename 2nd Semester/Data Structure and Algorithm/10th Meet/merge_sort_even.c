// Online C compiler to run C program online
#include <stdio.h>

int max = 8;
int data[8];
int temp[8];

 void merge(int data[], int temp[], int kiri, int tengah, int kanan) {
        int i, left_end, num_elements, tmp_pos;
        left_end = tengah - 1;
        tmp_pos = kiri;
        num_elements = kanan - kiri + 1;
        
        while ((kiri <= left_end) && (tengah <= kanan)) {
            if (data[kiri] <= data[tengah]) {
                temp[tmp_pos] = data[kiri];
                tmp_pos = tmp_pos + 1;
                kiri = kiri + 1;
            } else {
                temp[tmp_pos] = data[tengah];
                tmp_pos = tmp_pos + 1;
                tengah = tengah + 1;
            }
        }
        
        while (kiri <= left_end) {
            temp[tmp_pos] = data[kiri];
            kiri = kiri + 1;
            tmp_pos = tmp_pos + 1;
        }
        
        while (tengah <= kanan) {
            temp[tmp_pos] = data[tengah];
            tengah = tengah + 1;
            tmp_pos = tmp_pos + 1;
        }
        
        for (i = 0; i <= num_elements; i++) {
            data[kanan] = temp[kanan];
            kanan = kanan - 1;
        }
    }
    
void m_sort(int data[], int temp[], int kiri, int kanan) {
    int tengah;
    
    if (kanan > kiri) {
        tengah = (kanan + kiri) / 2;
        m_sort(data, temp, kiri, tengah);
        m_sort(data, temp, tengah + 1, kanan);
        merge(data, temp, kiri, tengah+1, kanan);
    }
}

void merge_sort(int data[], int temp[], int array_size) {
    m_sort(data, temp, 0, array_size - 1);
}

int main() {
    int i;
    
    printf("Masukan data sebelum terurut : \n");
    
    for (i = 0; i < max; i++) {
        printf("data ke %i : ", i + 1);
        scanf("%d", &data[i]);
    }
    
    merge_sort(data, temp, max);
    
    printf("\n\nData setelah terurut :");
    
    for (i = 0; i < max; i++) {
        printf("%d ", data[i]);
        printf("\n");
    }
    
    return 0;
    
}