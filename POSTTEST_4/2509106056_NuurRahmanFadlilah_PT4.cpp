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

struct Node {
    Tiket data;
    Node* next;
};

Node* front = NULL;
Node* rear = NULL;
Node* top = NULL;

Kereta dataKereta[MAX];
int jumlahKereta = 0;

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
    Node* n = new Node;
    n->data = t;
    n->next = NULL;
    if (front == NULL) {
        front = n;
        rear = n;
    } else {
        rear->next = n;
        rear = n;
    }
    cout << "Masuk antrian\n";
}

bool dequeue(Tiket* hasil) {
    if (front == NULL) {
        cout << "Kosong\n";
        return false;
    } else {
        Node* temp = front;
        *hasil = temp->data;
        front = front->next;
        delete temp;
        if (front == NULL) {
            rear = NULL;
        }
        return true;
    }
}

void tampilAntrian() {
    if (front == NULL) {
        cout << "Antrian kosong\n";
        return;
    }
    cout << "\n=== ANTRIAN ===\n";
    Node* bantu = front;
    while (bantu != NULL) {
        cout << bantu->data.namaPenumpang << " - " << bantu->data.rute << endl;
        bantu = bantu->next;
    }
}

void push(Tiket t) {
    Node* baru = new Node{t, top};
    top = baru;
}

void pop() {
    if (top == NULL) {
        cout << "Riwayat kosong\n";
        return;
    }
    Node* hapus = top;
    cout << "Hapus transaksi: " << hapus->data.namaPenumpang << endl;
    top = top->next;
    delete hapus;
}

void tampilRiwayat() {
    if (top == NULL) {
        cout << "Riwayat kosong\n";
        return;
    }
    cout << "\n=== RIWAYAT ===\n";
    Node* bantu = top;
    while (bantu != NULL) {
        cout << bantu->data.namaPenumpang << " - " << bantu->data.rute << endl;
        bantu = bantu->next;
    }
}

void peek() {
    if (front != NULL)
        cout << "Depan antrian: " << front->data.namaPenumpang << endl;
    else
        cout << "Antrian kosong\n";
    if (top != NULL)
        cout << "Terakhir riwayat: " << top->data.namaPenumpang << endl;
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

    for (int i = 0; i < total; i++) {
        cout << left << setw(6) << arr[i].nomor << setw(14) << arr[i].nama << setw(12) << arr[i].asal << setw(12) << arr[i].tujuan << setw(10) << arr[i].harga << endl;
    }
}

int caripakeSearch(Kereta* arr, int total, int key) {
    for (int i = 0; i < total; i++) {
        if (arr[i].nomor == key) {
            return i;
        }
    }
    return -1;
}

void cariNomor(Kereta* arr, int total) {
    int k;
    cout << "\nnomor: ";
    cin >> k;

    int h = caripakeSearch(arr, total, k);
    if (h != -1) {
        cout << arr[h].nama << " " << arr[h].asal << " ke " << arr[h].tujuan << endl;
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
    cin >> arr[total].nomor;
    cin.ignore();
    cout << "nama: ";
    getline(cin, arr[total].nama);
    cout << "asal: ";
    getline(cin, arr[total].asal);
    cout << "tujuan: ";
    getline(cin, arr[total].tujuan);
    cout << "harga: ";
    cin >> arr[total].harga;
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
        if (arr[i].asal == a && arr[i].tujuan == b) {
            cout << "Ditemukan, harga: " << arr[i].harga << endl;
            return;
        }
    }
    cout << "Tidak ditemukan\n";
}
// zzz
void diurutmerge(Kereta* arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        diurutmerge(arr, l, m);
        diurutmerge(arr, m + 1, r);
        Kereta temp[MAX];
        int i = l, j = m + 1, k = l;
        while (i <= m && j <= r) {
            if (arr[i].nama < arr[j].nama)
                temp[k++] = arr[i++];
            else
                temp[k++] = arr[j++];
        }
        while (i <= m) temp[k++] = arr[i++];
        while (j <= r) temp[k++] = arr[j++];
        for (int x = l; x <= r; x++)
            arr[x] = temp[x];
    }
}

void urutHarga(Kereta* arr, int total) {
    for (int i = 0; i < total - 1; i++) {
        int p = i;
        for (int j = i + 1; j < total; j++) {
            if (arr[j].harga < arr[p].harga)
                p = j;
        }
        if (p != i) swapKereta(&arr[i], &arr[p]);
    }
}

int main() {
    dataKereta[0] = {101, "Mahakam", "Samarinda", "Balikpapan", 150000};
    dataKereta[1] = {205, "KuTim", "Bontang", "Samarinda", 90000};
    dataKereta[2] = {310, "BorNeo", "Balikpapan", "Berau", 200000};
    dataKereta[3] = {412, "Segiri", "Tenggarong", "Bontang", 120000};
    dataKereta[4] = {520, "KalTim", "Samarinda", "Berau", 175000};
    dataKereta[5] = {111, "Cepat", "a", "s", 175999};
    jumlahKereta = 6;

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
        cout << "12. Lihat data terdepan dan terakhir\n";
        cout << "13. Keluar\n";
        cout << "pilih: ";
        cin >> pilih;

        if (pilih == 1) lihat(dataKereta, jumlahKereta);
        else if (pilih == 2) tambah(dataKereta, jumlahKereta);
        else if (pilih == 3) cariRute(dataKereta, jumlahKereta);
        else if (pilih == 4) cariNomor(dataKereta, jumlahKereta);
        else if (pilih == 5) {
            diurutmerge(dataKereta, 0, jumlahKereta - 1);
            lihat(dataKereta, jumlahKereta);
        }
        else if (pilih == 6) {
            urutHarga(dataKereta, jumlahKereta);
            lihat(dataKereta, jumlahKereta);
        }
        else if (pilih == 7) {
            Tiket t;
            cin.ignore();
            cout << "\nNama  : "; getline(cin, t.namaPenumpang);
            cout << "Rute  : "; getline(cin, t.rute);
            enqueue(t);
        }
        else if (pilih == 8) {
            Tiket t;
            if (dequeue(&t)) {
                cout << "Diproses: " << t.namaPenumpang << endl;
                push(t);
            }
        }
        else if (pilih == 9) tampilAntrian();
        else if (pilih == 10) tampilRiwayat();
        else if (pilih == 11) pop();
        else if (pilih == 12) peek();
        if (pilih != 13) lanjutsekalianbersih();
    } while (pilih != 13);
    cout << "\nKeluar Program";
    return 0;
}