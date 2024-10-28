#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct Buku {
    string ISBN;
    string judul;
    string pengarang;
    int tahun_terbit;

    Buku(string i, string j, string p, int t)
        : ISBN(i), judul(j), pengarang(p), tahun_terbit(t) {}
};

const int MAX_BUKU = 100;
Buku* perpustakaan[MAX_BUKU];
int total_buku = 0;

stack<Buku*> riwayat_peminjaman;

queue<Buku*> antrian_peminjaman;

void tambahBuku(string isbn, string judul, string pengarang, int tahun) {
    if (total_buku < MAX_BUKU) {
        perpustakaan[total_buku++] = new Buku(isbn, judul, pengarang, tahun);
        cout << "Buku berhasil ditambahkan!\n";
    } else {
        cout << "Perpustakaan penuh!\n";
    }
}

Buku* cariBuku(string isbn) {
    for (int i = 0; i < total_buku; i++) {
        if (perpustakaan[i]->ISBN == isbn) {
            return perpustakaan[i];
        }
    }
    return nullptr;
}

void tampilkanBuku() {
    cout << "Daftar Buku di Perpustakaan:\n";
    for (int i = 0; i < total_buku; i++) {
        cout << "ISBN: " << perpustakaan[i]->ISBN << ", Judul: " << perpustakaan[i]->judul
             << ", Pengarang: " << perpustakaan[i]->pengarang
             << ", Tahun: " << perpustakaan[i]->tahun_terbit << endl;
    }
}

void pinjamBuku(string isbn) {
    Buku* buku = cariBuku(isbn);
    if (buku) {
        antrian_peminjaman.push(buku);
        cout << "Buku dengan ISBN " << isbn << " ditambahkan ke dalam antrian peminjaman.\n";
    } else {
        cout << "Buku tidak ditemukan.\n";
    }
}

void kembalikanBuku() {
    if (!antrian_peminjaman.empty()) {
        Buku* buku = antrian_peminjaman.front();
        antrian_peminjaman.pop();
        riwayat_peminjaman.push(buku);
        cout << "Buku dengan ISBN " << buku->ISBN << " berhasil dikembalikan dan disimpan dalam riwayat peminjaman.\n";
    } else {
        cout << "Tidak ada buku dalam antrian peminjaman.\n";
    }
}

void tampilkanRiwayatPeminjaman() {
    stack<Buku*> temp = riwayat_peminjaman;
    cout << "Riwayat Peminjaman Buku:\n";
    while (!temp.empty()) {
        Buku* buku = temp.top();
        temp.pop();
        cout << "ISBN: " << buku->ISBN << ", Judul: " << buku->judul << endl;
    }
}

int main() {
    int pilihan;
    string isbn, judul, pengarang;
    int tahun;

    do {
        cout << "\nManajemen Perpustakaan:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Cari Buku\n";
        cout << "3. Tampilkan Semua Buku\n";
        cout << "4. Pinjam Buku\n";
        cout << "5. Kembalikan Buku\n";
        cout << "6. Tampilkan Riwayat Peminjaman\n";
        cout << "0. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan ISBN: "; cin >> isbn;
                cout << "Masukkan Judul: "; cin.ignore(); getline(cin, judul);
                cout << "Masukkan Pengarang: "; getline(cin, pengarang);
                cout << "Masukkan Tahun Terbit: "; cin >> tahun;
                tambahBuku(isbn, judul, pengarang, tahun);
                break;

            case 2:
                cout << "Masukkan ISBN untuk mencari buku: ";
                cin >> isbn;
                if (Buku* buku = cariBuku(isbn)) {
                    cout << "Buku Ditemukan:\n";
                    cout << "ISBN: " << buku->ISBN << ", Judul: " << buku->judul
                         << ", Pengarang: " << buku->pengarang
                         << ", Tahun: " << buku->tahun_terbit << endl;
                } else {
                    cout << "Buku tidak ditemukan.\n";
                }
                break;

            case 3:
                tampilkanBuku();
                break;

            case 4:
                cout << "Masukkan ISBN buku yang ingin dipinjam: ";
                cin >> isbn;
                pinjamBuku(isbn);
                break;

            case 5:
                kembalikanBuku();
                break;

            case 6:
                tampilkanRiwayatPeminjaman();
                break;

            case 0:
                cout << "Keluar dari program.\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
                break;
        }
    } while (pilihan != 0);

    for (int i = 0; i < total_buku; i++) {
        delete perpustakaan[i];
    }

    return 0;
}
