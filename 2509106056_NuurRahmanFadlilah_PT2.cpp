#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct Kereta{
    int nomor;
    string nama;
    string asal;
    string tujuannya;
    double harga;
};
Kereta dataKereta[100];
int jumlahKereta = 0;

void bersih(){
    system("cls");
}

void lanjut(){
    cout << "\nLanjut kilk enter";
    cin.ignore();
    cin.get();
}

void tukar(Kereta &a, Kereta &b){
    Kereta t = a;
    a = b;
    b = t;
}

void lihat(Kereta daftar[], int total){
    if(total == 0){
        cout << "Kosong\n";
        return;
    }
    cout << "\nData Kereta\n";
    cout << left << setw(6) << "No" << setw(14) << "Nama" << setw(12) << "Asal" << setw(12) << "Tujuan" << setw(10) << "Harga" << endl;
    for(int i=0;i<total;i++){
        cout << left << setw(6) << daftar[i].nomor << setw(14) << daftar[i].nama << setw(12) << daftar[i].asal << setw(12) << daftar[i].tujuannya << setw(10) << daftar[i].harga << endl;
    }
}

void tambah(Kereta daftar[], int &total){
    if(total >= 100){
        cout << "Penuh\n";
        return;
    }
    cout << "\nTambah\n";
    cout << "Nomor : ";
    cin >> daftar[total].nomor;
    cin.ignore();
    cout << "Nama  : ";
    getline(cin, daftar[total].nama);
    cout << "Asal  : ";
    getline(cin, daftar[total].asal);
    cout << "Tujuan: ";
    getline(cin, daftar[total].tujuannya);
    cout << "Harga : ";
    cin >> daftar[total].harga;
    total++;
}

void rute(Kereta daftar[], int total){
    string x,y;
    cin.ignore();
    cout << "Asal: ";
    getline(cin,x);
    cout << "Tujuan: ";
    getline(cin,y);
    bool ada=false;
    for(int i=0;i<total;i++){
        if(daftar[i].asal==x && daftar[i].tujuannya==y){
            cout << "\nAda\n";
            cout << daftar[i].nama << endl;
            cout << daftar[i].asal << " - " << daftar[i].tujuannya << endl;
            cout << daftar[i].harga << endl;
            ada=true;
            break;
        }
    }
    if(!ada) cout << "Tidak ada\n";
}

int cariNomor(Kereta daftar[], int total, int key){
    int step = 1;
    while(step*step < total) step++;
    int prev = 0;
    while(prev < total && daftar[(step<total?step:total)-1].nomor < key){
        prev = step;
        step += step;
        if(prev >= total) return -1;
    }
    int batas = (step<total?step:total);
    for(int i=prev;i<batas;i++){
        if(daftar[i].nomor == key) return i;
    }
    return -1;
}

void cari(Kereta daftar[], int total){
    int k;
    cout << "Nomor: ";
    cin >> k;
    int h = cariNomor(daftar,total,k);
    if(h!=-1){
        cout << daftar[h].nama << " ";
        cout << daftar[h].asal << " ke ";
        cout << daftar[h].tujuannya << endl;
    }
    else{
        cout << "Tidak ada\n";
    }
}

void mergeData(Kereta daftar[], int l, int m, int r){
    Kereta temp[100];
    int i=l;
    int j=m+1;
    int k=l;
    while(i<=m && j<=r){
        if(daftar[i].nama < daftar[j].nama){
            temp[k]=daftar[i];
            i++;
        }
        else{
            temp[k]=daftar[j];
            j++;
        }
        k++;
    }

    while(i<=m){
        temp[k]=daftar[i];
        i++; 
        k++;
    }

    while(j<=r){
        temp[k]=daftar[j];
        j++; 
        k++;
    }

    for(int x=l;x<=r;x++){
        daftar[x]=temp[x];
    }
}

void urutNama(Kereta daftar[], int l, int r){
    if(l<r){
        int m=(l+r)/2;
        urutNama(daftar,l,m);
        urutNama(daftar,m+1,r);
        mergeData(daftar,l,m,r);
    }
}

void urutHarga(Kereta daftar[], int total){
    for(int i=0;i<total-1;i++){
        int p=i;
        for(int j=i+1;j<total;j++){
            if(daftar[j].harga < daftar[p].harga){
                p=j;
            }
        }
        if(p!=i) tukar(daftar[i],daftar[p]);
    }
}

int main(){
    dataKereta[0]={101,"Mahakam","Samarinda","Balikpapan",150000};
    dataKereta[1]={205,"KuTim","Bontang","Samarinda",90000};
    dataKereta[2]={310,"BorNeo","Balikpapan","Berau",200000};
    dataKereta[3]={412,"Segiri","Tenggarong","Bontang",120000};
    dataKereta[4]={520,"KalTim","Samarinda","Berau",175000};
    dataKereta[5]={999,"Pulang","Jakarta","Solo",999666};
    jumlahKereta=6;

    int pilih;
    do{
        cout << "\nMenu\n";
        cout << "1 Lihat jadwal\n";
        cout << "2 Tambah jadwal\n";
        cout << "3 Cari rute\n";
        cout << "4 Cari nomor\n";
        cout << "5 Urut sesuai nama\n";
        cout << "6 Urut sesuai harga\n";
        cout << "7 Keluar\n";
        cout << "pilih: ";
        cin >> pilih;

        if(pilih==1){
            bersih();
            lihat(dataKereta,jumlahKereta);
            lanjut();
            bersih();
        }
        else if(pilih==2){
            bersih();
            tambah(dataKereta,jumlahKereta);
            lanjut();
            bersih();
        }
        else if(pilih==3){
            bersih();
            rute(dataKereta,jumlahKereta);
            lanjut();
            bersih();
        }
        else if(pilih==4){
            bersih();
            cari(dataKereta,jumlahKereta);
            lanjut();
            bersih();
        }
        else if(pilih==5){
            bersih();
            urutNama(dataKereta,0,jumlahKereta-1);
            lihat(dataKereta,jumlahKereta);
            lanjut();
            bersih();
        }
        else if(pilih==6){
            bersih();
            urutHarga(dataKereta,jumlahKereta);
            lihat(dataKereta,jumlahKereta);
            lanjut();
            bersih();
        }
    }while(pilih!=7);
    return 0;
}