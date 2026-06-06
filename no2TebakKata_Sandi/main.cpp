#include "UAStebakkata.h"

using namespace std;

int main()
{
    srand(time(0));

    Skor leaderboard[5];
    int jumlahLeaderboard = 0;

    char ulang = 'Y';

    while(ulang == 'Y' || ulang == 'y')
    {
        KataGame game;
        int level;

        pilihKesulitan(&game, level);
        inisialisasiGame(&game);

        char tebakanSalah[26];
        int jumlahSalah = 0;

        while(game.nyawa > 0 && !menang(game))
        {
            clearScreen();

            cout << "=================================\n";
            cout << "        GAME TEBAK KATA\n";
            cout << "=================================\n";

            tampilkanGame(
                game,
                tebakanSalah,
                jumlahSalah
            );

            string input;

            cout << "\nMasukkan huruf (? untuk hint): ";
            cin >> input;

            if(input.length() != 1)
            {
                cout << "\nMasukkan 1 huruf saja!\n";
                system("pause");
                continue;
            }

            char huruf = toupper(input[0]);

            if(huruf == '?')
            {
                beriHint(&game);
                continue;
            }

            if(sudahDitebak(
                huruf,
                game.statusTebakan,
                tebakanSalah,
                jumlahSalah
            ))
            {
                cout << "\nHuruf sudah ditebak!\n";
                system("pause");
                continue;
            }

            prosesTebakan(
                &game,
                huruf,
                tebakanSalah,
                &jumlahSalah
            );
        }

        clearScreen();

        if(menang(game))
        {
            cout << "\nSELAMAT!\n";
            cout << "Kata : " << game.kataAsli << endl;

            string nama;

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Masukkan Nama : ";
            getline(cin, nama);

            int skor = hitungSkor(level, game.nyawa);

            cout << "Skor : " << skor << endl;

            updateLeaderboard(
                leaderboard,
                jumlahLeaderboard,
                nama,
                skor
            );
        }
        else
        {
            cout << "\nGAME OVER!\n";
            cout << "Kata yang benar : " << game.kataAsli << endl;
        }

        tampilLeaderboard(
            leaderboard,
            jumlahLeaderboard
        );

        cout << "\nMain Lagi? (Y/N): ";
        cin >> ulang;
    }

    return 0;
}