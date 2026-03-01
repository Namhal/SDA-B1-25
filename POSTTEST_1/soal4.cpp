#include <iostream>
using namespace std;

int tukarNilai(int *angka1, int *angka2){
    int sementara;
    sementara = *angka1;
    *angka1 = *angka2;
    *angka2 = sementara;
    return 1;
}

int main(){
    int nilaiPertama;
    int nilaiKedua;
    cout << "Masukkan nilai pertama : ";
    cin >> nilaiPertama;
    cout << "Masukkan nilai kedua : ";
    cin >> nilaiKedua;
    cout << "\nSebelum ditukar :" << endl;
    cout << "Nilai pertama = " << nilaiPertama << endl;
    cout << "Nilai kedua   = " << nilaiKedua << endl;
    tukarNilai(&nilaiPertama, &nilaiKedua);
    cout << "\nSesudah ditukar :" << endl;
    cout << "Nilai pertama = " << nilaiPertama << endl;
    cout << "Nilai kedua   = " << nilaiKedua << endl;
    return 0;
}