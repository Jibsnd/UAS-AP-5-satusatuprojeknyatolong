#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// 1. Struktur Data Barang - sesuai spek pake struct
struct Barang
{
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

// Vector buat nyimpen semua barang
vector<Barang> inventaris;

// Prototipe fungsi - tiap menu 1 fungsi
void tambahBarang();
void tampilkanSemuaBarang();
void cariBarangTermahal();
void hitungTotalNilaiInventaris();
void cekRestock();
void updateStok();
void menuUtama();

// Fungsi validasi input angka
double inputHarga();
int inputStok();

// Fungsi cari barang, return pointer ke barang biar bisa diupdate
Barang *cariBarangByKode(const string &kode);

int main()
{
    menuUtama();
    return 0;
}

// 3. Menu Utama Loop
void menuUtama()
{
    int pilihan;
    do
    {
        cout << "\n\n";
        cout << " SISTEM MANAJEMEN INVENTARIS TOKO \n";
        cout << "\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Semua Barang\n";
        cout << "3. Cari Barang Termahal\n";
        cout << "4. Hitung Total Nilai Inventaris\n";
        cout << "5. Cek Restock Stok < 5\n";
        cout << "6. Update Stok\n";
        cout << "7. Keluar\n";
        cout << "\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        // Bersihin buffer biar getline aman
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan)
        {
        case 1:
            tambahBarang();
            break;
        case 2:
            tampilkanSemuaBarang();
            break;
        case 3:
            cariBarangTermahal();
            break;
        case 4:
            hitungTotalNilaiInventaris();
            break;
        case 5:
            cekRestock();
            break;
        case 6:
            updateStok();
            break;
        case 7:
            cout << "Terima kasih! Program selesai.\n";
            break;
        default:
            cout << "Pilihan tidak valid! Coba lagi.\n";
        }
    } while (pilihan != 7);
}

// 2. Validasi input harga
double inputHarga()
{
    double h;
    while (true)
    {
        cout << "Masukkan Harga: Rp ";
        cin >> h;
        if (cin.fail() || h < 0)
        {
            cout << "ERROR: Harga tidak boleh negatif atau huruf!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return h;
        }
    }
}

// 2. Validasi input stok
int inputStok()
{
    int s;
    while (true)
    {
        cout << "Masukkan Stok: ";
        cin >> s;
        if (cin.fail() || s < 0)
        {
            cout << "ERROR: Stok tidak boleh negatif atau huruf!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return s;
        }
    }
}

// Menu 1: Tambah Barang ke vector
void tambahBarang()
{
    Barang b;
    cout << "\n Tambah Barang Baru \n";
    cout << "Masukkan Kode Barang: ";
    getline(cin, b.kodeBarang);
    cout << "Masukkan Nama Barang: ";
    getline(cin, b.namaBarang);

    b.harga = inputHarga(); // validasi harga
    b.stok = inputStok();   // validasi stok

    inventaris.push_back(b);
    cout << "Barang berhasil ditambahkan!\n";
}

// Menu 2: Tampilkan tabel rapi
void tampilkanSemuaBarang()
{
    if (inventaris.empty())
    {
        cout << "\nInventaris kosong! Tambah barang dulu.\n";
        return;
    }

    cout << "\n Daftar Semua Barang\n";
    cout << left << setw(12) << "Kode"
         << setw(25) << "Nama Barang"
         << setw(15) << "Harga"
         << setw(10) << "Stok" << endl;
    cout << string(62, '-') << endl;

    for (const auto &b : inventaris)
    {
        cout << left << setw(12) << b.kodeBarang
             << setw(25) << b.namaBarang
             << "Rp " << setw(12) << fixed << setprecision(2) << b.harga
             << setw(10) << b.stok << endl;
    }
}

// Menu 3: Cari harga tertinggi
void cariBarangTermahal()
{
    if (inventaris.empty())
    {
        cout << "\nInventaris kosong!\n";
        return;
    }

    Barang *termahal = &inventaris[0];
    for (auto &b : inventaris)
    {
        if (b.harga > termahal->harga)
        {
            termahal = &b;
        }
    }

    cout << "\n Barang Termahal\n";
    cout << "Kode : " << termahal->kodeBarang << endl;
    cout << "Nama : " << termahal->namaBarang << endl;
    cout << "Harga : Rp " << fixed << setprecision(2) << termahal->harga << endl;
    cout << "Stok : " << termahal->stok << endl;
}

// Menu 4: Total nilai = harga * stok
void hitungTotalNilaiInventaris()
{
    double total = 0;
    for (const auto &b : inventaris)
    {
        total += b.harga * b.stok;
    }
    cout << "\n Total Nilai Inventaris\n";
    cout << "Total aset gudang: Rp " << fixed << setprecision(2) << total << endl;
}

// Menu 5: Cek stok < 5
void cekRestock()
{
    bool ada = false;
    cout << "\n BARANG YANG PERLU RESTOCK Stok < 5 \n";
    cout << left << setw(12) << "Kode" << setw(25) << "Nama Barang" << setw(10) << "Stok" << endl;
    cout << string(47, '-') << endl;

    for (const auto &b : inventaris)
    {
        if (b.stok < 5)
        {
            cout << left << setw(12) << b.kodeBarang
                 << setw(25) << b.namaBarang
                 << setw(10) << b.stok << endl;
            ada = true;
        }
    }
    if (!ada)
        cout << "Semua stok aman, tidak ada yang perlu direstock.\n";
}

// Fungsi cari + return pointer
Barang *cariBarangByKode(const string &kode)
{
    for (auto &b : inventaris)
    {
        if (b.kodeBarang == kode)
        {
            return &b; // return alamat memori barang
        }
    }
    return nullptr; // nggak ketemu
}

// Menu 6: Update Stok pake pointer
void updateStok()
{
    if (inventaris.empty())
    {
        cout << "\nInventaris kosong!\n";
        return;
    }

    string kode;
    cout << "\n Update Stok\n";
    cout << "Masukkan Kode Barang: ";
    getline(cin, kode);

    Barang *b = cariBarangByKode(kode); // pake pointer

    if (b == nullptr)
    {
        cout << "ERROR: Barang dengan kode '" << kode << "' tidak ditemukan!\n";
        return;
    }

    cout << "Barang ditemukan: " << b->namaBarang << " | Stok sekarang: " << b->stok << endl;

    int perubahan;
    cout << "Masukkan jumlah perubahan stok +tambah -kurang: ";
    cin >> perubahan;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Validasi stok nggak boleh negatif
    if (b->stok + perubahan < 0)
    {
        cout << "ERROR: Stok tidak boleh jadi negatif! Transaksi gagal.\n";
    }
    else
    {
        b->stok += perubahan; // ubah lewat pointer
        cout << "Stok berhasil diupdate! Stok baru: " << b->stok << endl;
    }
}