#include <iostream>
using namespace std;

int* reverseArray(int* arr, int n){
    int* awal = arr;
    int* akhir = arr + n - 1;
    while (awal < akhir){
        int sementara = *awal;
        *awal = *akhir;
        *akhir = sementara;
        awal++;
        akhir--;
    }
    return arr;
}

int main(){
    int dataPrima[7] = {2, 3, 5, 7, 11, 13, 17};
    int jumlahData = 7;
    int* ptr = dataPrima;
    cout << "Array sebelum dibalik:\n";
    for (int i = 0; i < jumlahData; i++){
        cout << "Nilai : " << *(ptr + i) << " , Alamatnya :  " << (ptr + i) << endl;
    }

    ptr = reverseArray(dataPrima, jumlahData);
    cout << "\nArray sesudah dibalik:\n";
    for (int i = 0; i < jumlahData; i++){
        cout << "Nilai : " << *(ptr + i) << " , Alamatnya : " << (ptr + i) << endl;
    }
    return 0;
}