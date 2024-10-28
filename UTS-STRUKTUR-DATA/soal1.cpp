#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string NIM;
    string nama;
    float IPK;
};

Mahasiswa* daftarMahasiswa[10];
int jumlahMahasiswa = 0;

void tambahMahasiswa(const string& NIM, const string& nama, float IPK) {
    if (jumlahMahasiswa < 10) {  
        Mahasiswa* mhs = new Mahasiswa{NIM, nama, IPK};
        daftarMahasiswa[jumlahMahasiswa++] = mhs;
        cout << "Data mahasiswa berhasil ditambahkan.\n";
    } else {
        cout << "Data mahasiswa sudah penuh.\n";
    }
}

void hapusMahasiswa(const string& NIM) {
    bool ditemukan = false;
    for (int i = 0; i < jumlahMahasiswa; ++i) {
        if (daftarMahasiswa[i]->NIM == NIM) {
            delete daftarMahasiswa[i];  
            for (int j = i; j < jumlahMahasiswa - 1; ++j) {
                daftarMahasiswa[j] = daftarMahasiswa[j + 1];
            }
            daftarMahasiswa[--jumlahMahasiswa] = nullptr;
            ditemukan = true;
            cout << "Data mahasiswa dengan NIM " << NIM << " berhasil dihapus.\n";
            break;
        }
    }
    if (!ditemukan) {
        cout << "Mahasiswa dengan NIM " << NIM << " tidak ditemukan.\n";
    }
}

void tampilkanMahasiswa() {
    if (jumlahMahasiswa == 0) {
        cout << "Tidak ada data mahasiswa.\n";
    } else {
        cout << "Data Mahasiswa:\n";
        for (int i = 0; i < jumlahMahasiswa; ++i) {
            cout << "NIM: " << daftarMahasiswa[i]->NIM
                 << ", Nama: " << daftarMahasiswa[i]->nama
                 << ", IPK: " << daftarMahasiswa[i]->IPK << endl;
        }
    }
}

void urutkanMahasiswa() {
    for (int i = 0; i < jumlahMahasiswa - 1; ++i) {
        for (int j = 0; j < jumlahMahasiswa - i - 1; ++j) {
            if (daftarMahasiswa[j]->IPK < daftarMahasiswa[j + 1]->IPK) {
                Mahasiswa* temp = daftarMahasiswa[j];
                daftarMahasiswa[j] = daftarMahasiswa[j + 1];
                daftarMahasiswa[j + 1] = temp;
            }
        }
    }
    cout << "Data mahasiswa telah diurutkan berdasarkan IPK.\n";
}

int main() {
    int pilihan;
    string NIM, nama;
    float IPK;

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Mahasiswa\n";
        cout << "2. Hapus Mahasiswa\n";
        cout << "3. Tampilkan Data Mahasiswa\n";
        cout << "4. Urutkan Mahasiswa Berdasarkan IPK\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan NIM: ";
                cin >> NIM;
                cout << "Masukkan Nama: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan IPK: ";
                cin >> IPK;
                tambahMahasiswa(NIM, nama, IPK);
                break;
            case 2:
                cout << "Masukkan NIM mahasiswa yang akan dihapus: ";
                cin >> NIM;
                hapusMahasiswa(NIM);
                break;
            case 3:
                tampilkanMahasiswa();
                break;
            case 4:
                urutkanMahasiswa();
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 5);

    for (int i = 0; i < jumlahMahasiswa; ++i) {
        delete daftarMahasiswa[i];
    }

    return 0;
}