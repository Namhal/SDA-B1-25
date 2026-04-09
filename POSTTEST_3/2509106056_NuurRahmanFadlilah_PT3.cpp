#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

#define MAX 100

struct Kereta {
    int nomor;
    string nama;
    string asal;
    string tujuan;
    double harga;
};

struct Tiket {
    string namaPenumpang;
    string rute;
};

Kereta dataKereta[MAX];
int jumlahKereta = 0;

Tiket antrian[MAX];//queue
int front = -1, rear = -1;

Tiket riwayat[MAX];//stack
int top = -1;

void lanjutsekalianbersih() {
    cout << "\nKlik enter untuk lanjut";
    cin.ignore();
    cin.get();
    system("cls");
}

void swapKereta(Kereta* a, Kereta* b) {
    Kereta t = *a;
    *a = *b;
    *b = t;
}

void enqueue(Tiket t) {
    if (rear == MAX - 1) {
        cout << "Antrian penuh\n";
        return;
    }
    if (front == -1) front = 0;
    rear++;
    *(antrian + rear) = t;
    cout << "Masuk antrian\n";
}

Tiket dequeue() {
    if (front == -1 || front > rear) {
        cout << "Antrian kosong\n";
        return {"", ""};
    }
    Tiket t = *(antrian + front);
    front++;
    return t;
}

void tampilAntrian() {
    if (front == -1 || front > rear) {
        cout << "Antrian kosong\n";
        return;
    }
    cout << "\n=== ANTRIAN ===\n";
    Tiket* p = antrian;
    for (int i = front; i <= rear; i++) {
        cout << (p + i)->namaPenumpang << " - " << (p + i)->rute << endl;
    }
}

void push(Tiket t) {
    if (top == MAX - 1) {
        cout << "Riwayat penuh\n";
        return;
    }
    top++;
    *(riwayat + top) = t;
}

void pop() {
    if (top == -1) {
        cout << "Riwayat kosong\n";
        return;
    }
    cout << "Hapus transaksi: " << (*(riwayat + top)).namaPenumpang << endl;
    top--;
}

void tampilRiwayat() {
    if (top == -1) {
        cout << "Riwayat kosong\n";
        return;
    }
    cout << "\n=== RIWAYAT ===\n";
    Tiket* p = riwayat;
    for (int i = top; i >= 0; i--) {
        cout << (p + i)->namaPenumpang << " - " << (p + i)->rute << endl;
    }
}

void peek() {
    if (front != -1 && front <= rear)
        cout << "Depan antrian: " << (*(antrian + front)).namaPenumpang << endl;
    else
        cout << "Antrian kosong\n";
    if (top != -1)
        cout << "Terakhir riwayat: " << (*(riwayat + top)).namaPenumpang << endl;
    else
        cout << "Riwayat kosong\n";
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

void tambah(Kereta* arr, int& total) {
    if (total >= MAX) {
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
    cout << "\nasal: ";
    cin.ignore();
    getline(cin, a);
    cout << "tujuan: ";
    getline(cin, b);

    for (int i = 0; i < total; i++) {
        if ((*(arr + i)).asal == a && (*(arr + i)).tujuan == b) {
            cout << "Ditemukan, harga: " << (*(arr + i)).harga << endl;
            return;
        }
    }
    cout << "Tidak ditemukan\n";
}

void diurutmerge(Kereta* arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        diurutmerge(arr, l, m);
        diurutmerge(arr, m + 1, r);
        Kereta temp[MAX];
        int i = l, j = m + 1, k = l;
        while (i <= m && j <= r) {
            if ((*(arr + i)).nama < (*(arr + j)).nama)
                temp[k++] = *(arr + i++);
            else
                temp[k++] = *(arr + j++);
        }
        while (i <= m) temp[k++] = *(arr + i++);
        while (j <= r) temp[k++] = *(arr + j++);
        for (int x = l; x <= r; x++)
            *(arr + x) = temp[x];
    }
}

void urutHarga(Kereta* arr, int total) {
    for (int i = 0; i < total - 1; i++) {
        int p = i;
        for (int j = i + 1; j < total; j++) {
            if ((*(arr + j)).harga < (*(arr + p)).harga)
                p = j;
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
    dataKereta[6] = {199, "Cepat", "a", "s", 11111};
    jumlahKereta = 7;

    int pilih;
    do {
        cout << "\nMenu\n";
        cout << "1. Lihat jadwal\n";
        cout << "2. Tambah jadwal\n";
        cout << "3. Cari rute\n";
        cout << "4. Cari nomor\n";
        cout << "5. Urut nama\n";
        cout << "6. Urut harga\n";
        cout << "7. Beli tiket\n";
        cout << "8. Proses tiket\n";
        cout << "9. Tampil antrian\n";
        cout << "10. Tampil riwayat\n";
        cout << "11. Hapus transaksi terakhir\n";
        cout << "12. Lihat antrian terdepan dan riwayat terakhir\n";
        cout << "13. Keluar\n";
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
        else if (pilih == 6) {
            urutHarga(dataKereta, jumlahKereta);
            lihat(dataKereta, jumlahKereta);
            lanjutsekalianbersih();
        }
        else if (pilih == 7) {
            Tiket t;
            cin.ignore();
            cout << "\nNama  : "; getline(cin, t.namaPenumpang);
            cout << "Rute  : "; getline(cin, t.rute);
            enqueue(t);
            lanjutsekalianbersih();
        }
        else if (pilih == 8) {
            Tiket t = dequeue();
            if (t.namaPenumpang != "") {
                cout << "Diproses: " << t.namaPenumpang << endl;
                push(t);
            }
            lanjutsekalianbersih();
        }
        else if (pilih == 9) {
            tampilAntrian();
            lanjutsekalianbersih();
        }
        else if (pilih == 10) {
            tampilRiwayat();
            lanjutsekalianbersih();
        }
        else if (pilih == 11) {
            pop();
            lanjutsekalianbersih();
        }
        else if (pilih == 12) {
            peek();
            lanjutsekalianbersih();
        }
    } while (pilih != 13);
    cout << "\nKeluar Program";
    return 0;
}