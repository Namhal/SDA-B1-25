#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa{
    string nama;
    string nim;
    float ipk;
};

int main(){
    const int jumlahMahasiswa = 5;
    Mahasiswa dataMahasiswa[jumlahMahasiswa];
    cout << "Input Data Mahasiswa\n";
    for (int i = 0; i < jumlahMahasiswa; i++){
        cout << "\nMahasiswa ke-" << i + 1 << endl;
        cout << "Nama : ";
        getline(cin >> ws, dataMahasiswa[i].nama);
        cout << "NIM  : ";
        getline(cin, dataMahasiswa[i].nim);
        cout << "IPK  : ";
        cin >> dataMahasiswa[i].ipk;
    }

    float ipkTertinggi = dataMahasiswa[0].ipk;
    int indeksTertinggi = 0;

    for (int i = 1; i < jumlahMahasiswa; i++){
        if (dataMahasiswa[i].ipk > ipkTertinggi){
            ipkTertinggi = dataMahasiswa[i].ipk;
            indeksTertinggi = i;
        }
    }

    cout << "\nMahasiswa dengan IPK Tertinggi\n";
    cout << "Nama : " << dataMahasiswa[indeksTertinggi].nama << endl;
    cout << "NIM  : " << dataMahasiswa[indeksTertinggi].nim << endl;
    cout << "IPK  : " << dataMahasiswa[indeksTertinggi].ipk << endl;
    return 0;
}