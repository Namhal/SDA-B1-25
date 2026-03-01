#include <iostream>
using namespace std;


int FindMin(int data[], int jumlahData, int &indexMin){
    int nilaiMin = data[0];
    indexMin = 0;
    for (int i = 1; i < jumlahData; i++){
        if (data[i] < nilaiMin){
            nilaiMin = data[i];
            indexMin = i;
        }
    }
    return nilaiMin;
}

int main(){
    int fibonacci[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int minimum;
    int posisiMin;
    cout << "Isi Array : ";
    for (int i = 0; i < 8; i++){
        cout << fibonacci[i] << " ";
    }
    cout << endl << endl;
    minimum = FindMin(fibonacci, 8, posisiMin);
    cout << "Nilai minimum : " << minimum << ", Index ke-" << posisiMin << endl;
    return 0;
}

/*
Tmin (Best Case)
(kondisi: tidak ada data lebih kecil)

Tmin(n)
= C1 + C2 + C3n + C4(n-1) + C5(n-1) + C8

= 1 + 1 + n + (n-1) + (n-1) + 1
= 3n + 1

Big-O Best Case :
O(n)

Tmax (Worst Case)
(kondisi: setiap data lebih kecil dari sebelumnya)

Tmax(n)
= C1 + C2 + C3n + C4(n-1)
+ C5(n-1) + C6(n-1) + C7(n-1) + C8

= 1 + 1 + n + (n-1) + (n-1) + (n-1) + (n-1) + 1
= 5n - 1

Big-O Worst Case :
O(n)
*/