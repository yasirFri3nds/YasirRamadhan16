#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Pelanggan {
    int nomor_antrian;  
    int waktu_layanan;  
};

class Queue {
private:
    queue<Pelanggan> pelangganQueue;   

public:
    void enqueue(Pelanggan p) {
        pelangganQueue.push(p);
    }

    Pelanggan dequeue() {
        Pelanggan depan = pelangganQueue.front();
        pelangganQueue.pop();
        return depan;
    }

    bool isEmpty() {
        return pelangganQueue.empty();
    }

    int size() {
        return pelangganQueue.size();
    }
};

void simulasiAntrian(Queue &antrian, int waktu_layanan[], int jumlah_loket) {
    vector<int> waktu_tunggu(jumlah_loket, 0);  
    int total_waktu_tunggu = 0;  
    int pelanggan_terlayani = 0;  

    while (!antrian.isEmpty()) {
        for (int i = 0; i < jumlah_loket; ++i) {
            if (antrian.isEmpty()) break;  

            Pelanggan p = antrian.dequeue();  
            waktu_tunggu[i] += p.waktu_layanan;  
            total_waktu_tunggu += waktu_tunggu[i]; 
            pelanggan_terlayani++;  

            cout << "Pelanggan nomor antrian " << p.nomor_antrian 
                 << " dilayani di loket " << (i + 1) 
                 << " dengan waktu layanan " << p.waktu_layanan 
                 << " menit." << endl;
        }
    }

    int rata_rata_waktu_tunggu = (pelanggan_terlayani > 0) ? total_waktu_tunggu / pelanggan_terlayani : 0;
    int sisa_antrian = antrian.size(); 

    cout << "\nStatistik:" << endl;
    cout << "Rata-rata waktu tunggu: " << rata_rata_waktu_tunggu << " menit" << endl;
    cout << "Pelanggan terlayani: " << pelanggan_terlayani << endl;
    cout << "Sisa antrian: " << sisa_antrian << endl;
}

int main() {
    Queue antrian;               
    int jumlah_pelanggan, jumlah_loket = 3;

    cout << "Masukkan jumlah pelanggan: ";
    cin >> jumlah_pelanggan;

    for (int i = 1; i <= jumlah_pelanggan; ++i) {
        Pelanggan p;
        p.nomor_antrian = i;    
        cout << "Masukkan waktu layanan untuk pelanggan nomor " << i << " (dalam menit): ";
        cin >> p.waktu_layanan; 
        antrian.enqueue(p);    
    }

    simulasiAntrian(antrian, nullptr, jumlah_loket);

    return 0;
}