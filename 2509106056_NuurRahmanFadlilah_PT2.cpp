#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct Kereta {
    int nomor;
    string nama;
    string asal;
    string tujuan;
    double harga;
};
Kereta dataKereta[100];
int jumlahKereta = 0;

void lanjutsekalianbersih() {
    cout << "\nKilk enter untuk lanjut";
    cin.ignore();
    cin.get();
    system("cls");
}

void swapKereta(Kereta* a, Kereta* b) {
    Kereta t = *a;
    *a = *b;
    *b = t;
}

void lihat(Kereta* arr, int total) {
    if (total == 0) {
        cout << "kosong\n";
        return;
    }

    cout << "\nJADWAL\n";
    cout << left << setw(6) << "No" << setw(14) << "Nama" << setw(12) << "Asal" << setw(12) << "Tujuan" << setw(10) << "Harga" << endl;

    Kereta* p = arr;
    for (int i = 0; i < total; i++) {
        cout << left << setw(6) << (*(p + i)).nomor << setw(14) << (*(p + i)).nama << setw(12) << (*(p + i)).asal << setw(12) << (*(p + i)).tujuan << setw(10) << (*(p + i)).harga << endl;
    }
}

void tambah(Kereta* arr, int& total) {
    if (total >= 100) {
        cout << "penuh\n";
        return;
    }
    cout << "\nnomor: ";
    cin >> (*(arr + total)).nomor;
    cin.ignore();
    cout << "nama: ";
    getline(cin, (*(arr + total)).nama);
    cout << "asal: ";
    getline(cin, (*(arr + total)).asal);
    cout << "tujuan: ";
    getline(cin, (*(arr + total)).tujuan);
    cout << "harga: ";
    cin >> (*(arr + total)).harga;
    total++;
}

void cariRute(Kereta* arr, int total) {
    string a, b;
    cin.ignore();
    cout << "\nasal: ";
    getline(cin, a);
    cout << "tujuan: ";
    getline(cin, b);

    bool ada = false;

    for (int i = 0; i < total; i++) {
        cout << "Pengecekan kereta ke-" << i + 1 << ", " << (*(arr + i)).nama << ": " << (*(arr + i)).asal << " ke " << (*(arr + i)).tujuan << endl;
        if ((*(arr + i)).asal == a && (*(arr + i)).tujuan == b) {
            cout << "Jadwal ditemukan\n";
            cout << "Harga tiket: " << (*(arr + i)).harga << endl;
            ada = true;
            break;
        }
    }
    if (!ada) {
        cout << "Jadwal tidak ditemukan\n";
    }
}

int caripakeSearch(Kereta* arr, int total, int key) {
    int step = 1;
    while (step * step < total) {
        step++;
    }
    int awal = 0;
    while (awal < total && (*(arr + (step < total ? step : total) - 1)).nomor < key) {
        awal = step;
        step += step;
        if (awal >= total) return -1;
    }
    int batas = (step < total ? step : total);
    for (int i = awal; i < batas; i++) {
        if ((*(arr + i)).nomor == key) {
            return i;
        }
    }
    return -1;
}

void cariNomor(Kereta* arr, int total) {
    int k;
    cout << "\nnomor: ";
    cin >> k;
    cout << "Perjalanan kereta ";
    int h = caripakeSearch(arr, total, k);
    if (h != -1) {
        cout << (*(arr + h)).nama << " ";
        cout << (*(arr + h)).asal << " ke ";
        cout << (*(arr + h)).tujuan << endl;
    } else {
        cout << "tidak ada\n";
    }
}

void bagianmerge(Kereta* arr, int l, int m, int r) {
    Kereta temp[100];
    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r) {
        if ((*(arr + i)).nama < (*(arr + j)).nama) {
            temp[k] = *(arr + i);
            i++;
        } else {
            temp[k] = *(arr + j);
            j++;
        }
        k++;
    }

    while (i <= m) {
        temp[k] = *(arr + i);
        i++;
        k++;
    }

    while (j <= r) {
        temp[k] = *(arr + j);
        j++;
        k++;
    }
    for (int x = l; x <= r; x++) {
        *(arr + x) = temp[x];
    }
}

void diurutmerge(Kereta* arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        diurutmerge(arr, l, m);
        diurutmerge(arr, m + 1, r);
        bagianmerge(arr, l, m, r);
    }
}

void urutHarga(Kereta* arr, int total) {
    for (int i = 0; i < total - 1; i++) {
        int p = i;
        for (int j = i + 1; j < total; j++) {
            if ((*(arr + j)).harga < (*(arr + p)).harga) {
                p = j;
            }
        }
        if (p != i) swapKereta(arr + i, arr + p);
    }
}

int main() {
    dataKereta[0] = {101, "Mahakam", "Samarinda", "Balikpapan", 150000};
    dataKereta[1] = {205, "KuTim", "Bontang", "Samarinda", 90000};
    dataKereta[2] = {310, "BorNeo", "Balikpapan", "Berau", 200000};
    dataKereta[3] = {412, "Segiri", "Tenggarong", "Bontang", 120000};
    dataKereta[4] = {520, "KalTim", "Samarinda", "Berau", 175000};
    dataKereta[5] = {999, "Pulang", "Jakarta", "Solo", 999666};
    jumlahKereta = 6;
    int pilih;

    do {
        cout << "\nMenu\n";
        cout << "1 Lihat jadwal\n";
        cout << "2 Tambah jadwalnya\n";
        cout << "3 Cari sesuai rute\n";
        cout << "4 Cari nomor kereta\n";
        cout << "5 Urut sesuai nama\n";
        cout << "6 Urut sesuai harga\n";
        cout << "7 Keluar\n";
        cout << "pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            lihat(dataKereta, jumlahKereta);
            lanjutsekalianbersih();
        } 
        else if (pilih == 2) {
            tambah(dataKereta, jumlahKereta);
            lanjutsekalianbersih();
        } 
        else if (pilih == 3) {
            cariRute(dataKereta, jumlahKereta);
            lanjutsekalianbersih();
        } 
        else if (pilih == 4) {
            cariNomor(dataKereta, jumlahKereta);
            lanjutsekalianbersih();
        } 
        else if (pilih == 5) {
            diurutmerge(dataKereta, 0, jumlahKereta - 1);
            lihat(dataKereta, jumlahKereta);
            lanjutsekalianbersih();
        } 
        else if (pilih == 6) {;
            urutHarga(dataKereta, jumlahKereta);
            lihat(dataKereta, jumlahKereta);
            lanjutsekalianbersih();
        }
    } while (pilih != 7);
    cout<<"\nKeluar Program";
    return 0;
}