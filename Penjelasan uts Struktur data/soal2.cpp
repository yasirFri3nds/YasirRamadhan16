#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Peralatan {
    string kode;
    string nama;
    int jumlah;
    string kondisi;
};

void tambahPeralatan(const string& kode, const string& nama, int jumlah, const string& kondisi) {
    ofstream file("inventaris.txt", ios::app);  
    if (file.is_open()) {
        file << kode << " " << nama << " " << jumlah << " " << kondisi << endl;
        file.close();
        cout << "Data peralatan berhasil ditambahkan.\n";
    } else {
        cout << "Gagal membuka file!\n";
    }
}

vector<Peralatan> bacaDataPeralatan() {
    ifstream file("inventaris.txt");
    vector<Peralatan> peralatanList;
    if (file.is_open()) {
        Peralatan alat;
        while (file >> alat.kode >> alat.nama >> alat.jumlah >> alat.kondisi) {
            peralatanList.push_back(alat);
        }
        file.close();
    } else {
        cout << "Gagal membuka file!\n";
    }
    return peralatanList;
}

void updateFile(const vector<Peralatan>& peralatanList) {
    ofstream file("inventaris.txt", ios::trunc);  
    if (file.is_open()) {
        for (const auto& alat : peralatanList) {
            file << alat.kode << " " << alat.nama << " " << alat.jumlah << " " << alat.kondisi << endl;
        }
        file.close();
    } else {
        cout << "Gagal membuka file!\n";
    }
}

void ubahPeralatan(const string& kode) {
    vector<Peralatan> peralatanList = bacaDataPeralatan();
    bool ditemukan = false;
    for (auto& alat : peralatanList) {
        if (alat.kode == kode) {
            cout << "Masukkan nama baru: ";
            cin >> alat.nama;
            cout << "Masukkan jumlah baru: ";
            cin >> alat.jumlah;
            cout << "Masukkan kondisi baru: ";
            cin >> alat.kondisi;
            ditemukan = true;
            break;
        }
    }
    if (ditemukan) {
        updateFile(peralatanList);
        cout << "Data peralatan berhasil diubah.\n";
    } else {
        cout << "Data peralatan dengan kode " << kode << " tidak ditemukan.\n";
    }
}

void hapusPeralatan(const string& kode) {
    vector<Peralatan> peralatanList = bacaDataPeralatan();
    bool ditemukan = false;
    auto it = remove_if(peralatanList.begin(), peralatanList.end(), [&](Peralatan& alat) {
        return alat.kode == kode;
    });
    if (it != peralatanList.end()) {
        peralatanList.erase(it, peralatanList.end());
        updateFile(peralatanList);
        cout << "Data peralatan berhasil dihapus.\n";
    } else {
        cout << "Data peralatan dengan kode " << kode << " tidak ditemukan.\n";
    }
}

void tampilkanLaporan() {
    vector<Peralatan> peralatanList = bacaDataPeralatan();
    sort(peralatanList.begin(), peralatanList.end(), [](const Peralatan& a, const Peralatan& b) {
        return a.kode < b.kode;
    });
    cout << "Laporan Inventaris Peralatan:\n";
    for (const auto& alat : peralatanList) {
        cout << "Kode: " << alat.kode
             << ", Nama: " << alat.nama
             << ", Jumlah: " << alat.jumlah
             << ", Kondisi: " << alat.kondisi << endl;
    }
}

int main() {
    int pilihan;
    string kode, nama, kondisi;
    int jumlah;

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Peralatan\n";
        cout << "2. Ubah Peralatan\n";
        cout << "3. Hapus Peralatan\n";
        cout << "4. Tampilkan Laporan\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan kode: ";
                cin >> kode;
                cout << "Masukkan nama: ";
                cin >> nama;
                cout << "Masukkan jumlah: ";
                cin >> jumlah;
                cout << "Masukkan kondisi: ";
                cin >> kondisi;
                tambahPeralatan(kode, nama, jumlah, kondisi);
                break;
            case 2:
                cout << "Masukkan kode peralatan yang akan diubah: ";
                cin >> kode;
                ubahPeralatan(kode);
                break;
            case 3:
                cout << "Masukkan kode peralatan yang akan dihapus: ";
                cin >> kode;
                hapusPeralatan(kode);
                break;
            case 4:
                tampilkanLaporan();
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 5);

    return 0;
}