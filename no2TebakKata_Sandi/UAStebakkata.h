#ifndef UASTEBAKKATA_H
#define UASTEBAKKATA_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <cctype>


using namespace std;

#undef max
#undef main

struct KataGame{
    string kataAsli;
    string statusTebakan;
    int nyawa;
};

struct Skor{
    string nama;
    int nilai;
};

extern string bankKata[15];

void clearScreen();
void pilihKesulitan(KataGame *game, int &level);
void inisialisasiGame(KataGame *game);

void tampilkanGame(
    KataGame game,
    char tebakanSalah[],
    int jumlahSalah
);

bool sudahDitebak(
    char huruf,
    string status,
    char salah[],
    int jumlahSalah
);

void prosesTebakan(
    KataGame *game,
    char huruf,
    char salah[],
    int *jumlahSalah
);

bool menang(KataGame game);

void beriHint(KataGame *game);

int hitungSkor(
    int level,
    int nyawa
);

void updateLeaderboard(
    Skor papan[],
    int &jumlah,
    string nama,
    int skor
);

void tampilLeaderboard(
    Skor papan[],
    int jumlah
);

#endif