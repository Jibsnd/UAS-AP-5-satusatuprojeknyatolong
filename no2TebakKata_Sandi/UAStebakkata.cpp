#include "UAStebakkata.h"
using namespace std;

string bankKata[15] = {
    "INDONESIA","BRAZIL","CHINA","JERMAN","ITALIA",
    "PORTUGAL","JEPANG","THAILAND","FRANCIS","INDIA",
    "BELANDA","RUSIA","TURKEY","ARGENTINA","MESIR"
};

void clearScreen(){
    system("cls");
}

void pilihKesulitan(KataGame *game, int &level){
    cout << "=== PILIH KESULITAN ===\n";
    cout << "1. Easy (8 Nyawa)\n";
    cout << "2. Medium (6 Nyawa)\n";
    cout << "3. Hard (4 Nyawa)\n";
    cout << "Pilihan : ";
    cin >> level;

    if(level == 1)
        game->nyawa = 8;
    else if(level == 2)
        game->nyawa = 6;
    else
        game->nyawa = 4;
}

void inisialisasiGame(KataGame *game){
    int idx = rand() % 15;

    game->kataAsli = bankKata[idx];
    game->statusTebakan =
        string(game->kataAsli.length(), '_');
}

void tampilkanGame(
    KataGame game,
    char tebakanSalah[],
    int jumlahSalah
){
    cout << "\nJumlah Huruf : " << game.kataAsli.length();
    cout << "\nNyawa : " << game.nyawa;

    cout << "\n\nKata : ";
    for(char c : game.statusTebakan)
        cout << c << ' ';

    cout << "\n\nHuruf Salah : ";

    if(jumlahSalah == 0)
        cout << "-";

    for(int i = 0; i < jumlahSalah; i++)
        cout << tebakanSalah[i] << ' ';

    cout << endl;
}

bool sudahDitebak(
    char huruf,
    string status,
    char salah[],
    int jumlahSalah
){
    huruf = toupper(huruf);

    for(char c : status)
        if(c == huruf)
            return true;

    for(int i = 0; i < jumlahSalah; i++)
        if(salah[i] == huruf)
            return true;

    return false;
}

void prosesTebakan(
    KataGame *game,
    char huruf,
    char salah[],
    int *jumlahSalah
){
    huruf = toupper(huruf); // 🔥 penting biar konsisten

    bool ketemu = false;

    for(int i = 0; i < game->kataAsli.length(); i++)
    {
        if(game->kataAsli[i] == huruf)
        {
            game->statusTebakan[i] = huruf;
            ketemu = true;
        }
    }

    if(!ketemu)
    {
        salah[*jumlahSalah] = huruf;
        (*jumlahSalah)++;
        game->nyawa--;
    }
}

bool menang(KataGame game){
    return game.kataAsli == game.statusTebakan;
}

void beriHint(KataGame *game){
    if(game->nyawa <= 1)
        return;

    for(int i = 0; i < game->kataAsli.length(); i++)
    {
        if(game->statusTebakan[i] == '_')
        {
            game->statusTebakan[i] = game->kataAsli[i];
            game->nyawa--;
            break;
        }
    }
}

int hitungSkor(int level, int nyawa){
    int pengali;

    if(level == 1) pengali = 10;
    else if(level == 2) pengali = 20;
    else pengali = 30;

    return nyawa * pengali;
}

void updateLeaderboard(
    Skor papan[],
    int &jumlah,
    string nama,
    int skor
){
    if(jumlah < 5)
    {
        papan[jumlah].nama = nama;
        papan[jumlah].nilai = skor;
        jumlah++;
    }
    else
    {
        int minIdx = 0;

        for(int i = 1; i < 5; i++)
        {
            if(papan[i].nilai < papan[minIdx].nilai)
                minIdx = i;
        }

        if(skor > papan[minIdx].nilai)
        {
            papan[minIdx].nama = nama;
            papan[minIdx].nilai = skor;
        }
    }

    // sorting aman
    for(int i = 0; i < jumlah - 1; i++)
    {
        for(int j = i + 1; j < jumlah; j++)
        {
            if(papan[j].nilai > papan[i].nilai)
            {
                Skor temp = papan[i];
                papan[i] = papan[j];
                papan[j] = temp;
            }
        }
    }
}

void tampilLeaderboard(Skor papan[], int jumlah){
    cout << "\n=====================\n";
    cout << "     LEADERBOARD\n";
    cout << "=====================\n";

    for(int i = 0; i < jumlah; i++)
    {
        cout << i + 1 << ". "
             << papan[i].nama
             << " - "
             << papan[i].nilai
             << " poin\n";
    }
}