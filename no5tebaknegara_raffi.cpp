#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <random>
using namespace std;

int main() {
    system("cls");
    string target, hint;
    int panjang, jumlahtersembunyi;
    vector<string> negara = {"norway", 
        "oman", 
        "indonesia", 
        "brunei", 
        "irlandia", 
        "skotlandia", 
        "amerika serikat", 
        "india", 
        "malaysia",
        "ghana",
        "korea selatan",    
        "inggris"
    };

    random_device rd;
    mt19937 g(rd());

    uniform_int_distribution<int> dist(0, negara.size() - 1);

char lagi;
string input;
int skor = 0;
do {
    target = negara[dist(g)];
    hint = target;
    panjang = target.length();
    
    vector<int> indeksHuruf;
    for (int i = 0; i < panjang; i++) {
        if (target[i] != ' ') {
            indeksHuruf.push_back(i);
        }
    }

    int jumlahHuruf = indeksHuruf.size();
    int jumlahtersembunyi = min(panjang / 2, jumlahHuruf);

    shuffle(indeksHuruf.begin(), indeksHuruf.end(), g);
    for (int i = 0; i < jumlahtersembunyi; i++) {
        hint[indeksHuruf[i]] = '_';
    }
        cout << "Tebak negara: " << hint << endl;
        cout << "Negara apa yang dimaksud? ";
        getline(cin, input);

        if (input == target) {
            skor++;
            cout << "Selamat! Anda benar." << endl;
            cout << "Skor Anda: " << skor << endl;
        } else {
            cout << "Maaf, jawaban Anda salah. Coba lagi." << endl;
            cout << "Skor Anda: " << skor << endl;
        }

    cout << "Ingin bermain lagi? (y/n): ";
    cin >> lagi;
    cout << endl;
    cin.ignore();
} while (lagi == 'y' || lagi == 'Y');
}