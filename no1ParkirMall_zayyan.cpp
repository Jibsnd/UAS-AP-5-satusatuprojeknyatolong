#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

struct Petugas
{
    string nama;
    string id;

    string isipetugas()
    {
        cout << "\nMasukkan nama: ";
        getline(cin, nama);
        cout << "Masukkan ID  : ";
        getline(cin, id);
        return nama + " " + id;
    }
};

struct Mobil
{
    string plat;
    string merk;
    string warna;
    time_t waktuMasuk;
};

void hitungDurasi(time_t masuk, int &jam, int &menit, int &detik, int &totalDetik) {
    time_t sekarang = time(0);
    totalDetik = static_cast<int>(difftime(sekarang, masuk)); 
    
    jam = totalDetik / 3600;
    int sisaDetik = totalDetik % 3600;
    menit = sisaDetik / 60;
    detik = sisaDetik % 60;
}

const int max_parkir = 5;

void TambahKendaraan(vector<Mobil>* daftarMobil)
{
    if (daftarMobil->size() >= max_parkir)
    {
        cout << "\nMohon maaf, kapasitas parkiran hanya memuat 5 mobil" << endl;
        return;
    }
        int jumlahmobil;
                cout << "Masukkan jumlah mobil yang akan diparkirkan: ";
                cin >> jumlahmobil;
                cin.ignore();

                if (jumlahmobil > max_parkir)
                {
                    cout << "Maaf, parkiran hanya dapat memuat 5 mobil." << endl;
                    return;
                }
                
                for (int i = 0; i < jumlahmobil; i++)
                {
                    Mobil m;
                    cout << "\nMobil ke-" << i + 1 << ":" << endl;
                    cout << "Masukkan plat nomor mobil: ";
                    getline(cin, m.plat);
                    cout << "Masukkan merk mobil: ";
                    getline(cin, m.merk);
                    cout << "Masukkan warna mobil: ";
                    getline(cin, m.warna);
                    m.waktuMasuk = time(0);
                    daftarMobil->push_back(m);
                }
}

void TampilkanKendaraan(const vector<Mobil>* daftarMobil)
{
    if (daftarMobil->empty())
    {
        cout << "\nBelum ada mobil yang terparkir." << endl;
        return;
    }

    cout << "\nDaftar mobil yang sudah terparkir: " << endl;
    for (size_t i = 0; i < daftarMobil->size(); i++)
    {
        const Mobil& m = (*daftarMobil)[i]; 

        cout << "Mobil ke-" << i + 1 << endl;
        cout << "Plat nomor: " << m.plat << endl;
        cout << "Merk: " << m.merk << endl;
        cout << "Warna: " << m.warna << endl;

        int jam, menit, detik, totalDetik;
        hitungDurasi(m.waktuMasuk, jam, menit, detik, totalDetik);

        cout << "Waktu parkir : " << jam << " jam " << menit << " menit " << detik << " detik\n\n";
    }
}

void Pembayaran(vector<Mobil>* daftarMobil)
{
    if (daftarMobil->empty())
    {
        cout << "\nBelum ada kendaraan yang terparki." << endl;
        return;
    }
    TampilkanKendaraan(daftarMobil);

    string cariPlat;
    bool ditemukan = false;

    while (!ditemukan) 
    {
        cout << "Masukkan plat mobil yang ingin dibayar : ";
        getline(cin, cariPlat);

        for (auto it = daftarMobil->begin(); it != daftarMobil->end(); ++it) 
        {
            if (it->plat == cariPlat) 
            {
                ditemukan = true;
                int jam, menit, detik, totalDetik;
                hitungDurasi(it->waktuMasuk, jam, menit, detik, totalDetik);

                int biaya = totalDetik * 2; 
                
                cout << "\nB I A Y A  P A R K I R : Rp" << biaya << "\n";
                cout << "=================================================================\n\n";

                daftarMobil->erase(it);
                return; 
            }
        }
    }
}


int main()
{
    system ("Cls");
    cout << "==================================================================";
    cout << "\n------------------------- SELAMAT DATANG -------------------------";
    cout << "\n                   DI PORTAL PARKIR KHUSUS MOBIL                   ";
    cout << "\n                          MALL PRIENAL                           ";
    cout << "\n==================================================================" << endl; 

    cout << "\nKami senang anda telah hadir.";
    cout << "\nSilahkan masukkan informasi anda yang akan bertugas hari ini.  ";
    Petugas petugas;
    petugas.isipetugas();

    

    vector<Mobil> daftarmobil;    
    int pilihan;
    
    do
    {
        cout << "\nSilahkan input opsi berikut dalam bentuk angka." << endl;
        cout << "1. Tambahkan Daftar Kendaraan" << endl;
        cout << "2. Tampilkan Daftar Kendaraan" << endl;
        cout << "3. Pembayaran" << endl;
        cout << "4. Keluar Program" << endl;
        cout << "\nMasukkan opsi: ";
        cin >> pilihan;
        cin.ignore();
        
        switch (pilihan)
        {
            case 1: 
                {
                    TambahKendaraan(&daftarmobil);
                    break;
                }
            case 2: 
                {
                    TampilkanKendaraan(&daftarmobil);   
                    break;
                }
            case 3: 
                {
                    Pembayaran(&daftarmobil);
                    break;
                }
            case 4: 
                {
                    cout << "\nTerima kasih telah menggunakan portal parkir kami. Sampai jumpa!" << endl;
                    break;
                }
            default:
                cout << "Opsi tidak valid. Silakan coba lagi." << endl;
        }
    }
    while (pilihan != 4);

    system("pause");
}