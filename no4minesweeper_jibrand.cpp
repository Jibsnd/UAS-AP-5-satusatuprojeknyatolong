#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//DEKLARASI CLASS UTAMA
class MinesweeperGame {
private:
    // --- State & Variabel Permainan ---
    int size;
    int totalBombs;
    int flagsPlaced;
    int board[10][10];       
    bool opened[10][10];     
    bool flagged[10][10];    
    bool gameOver;
    bool gameWon;
    bool isFirstMove;        
    time_t startTime;

    // LOGIKA INTERNAL (BOM & ANGKA)
    
    // Fungsi: Menaruh bom secara acak, menghindari klik pertama pemain
    void placeBombs(int firstR, int firstC) {
        int bombsPlaced = 0;
        while (bombsPlaced < totalBombs) {
            int r = rand() % size;
            int c = rand() % size;
            
            // Hindari koordinat langkah pertama
            if (r == firstR && c == firstC) continue;

            if (board[r][c] != -1) {
                board[r][c] = -1;
                bombsPlaced++;
            }
        }
    }

    // Fungsi: Menghitung jumlah bom di 8 arah sekitar kotak
    void calculateAdjacency() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == -1) continue; 
                
                int count = 0;
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        int ni = i + dr;
                        int nj = j + dc;
                        if (ni >= 0 && ni < size && nj >= 0 && nj < size) {
                            if (board[ni][nj] == -1) count++;
                        }
                    }
                }
                board[i][j] = count;
            }
        }
    }

    // BAGIAN ALGORITMA FLOOD FILL
    
    // Fungsi: Membuka area kosong secara rekursif
    void floodFill(int r, int c) {
        // Base case: Cek batas papan dan status kotak
        if (r < 0 || r >= size || c < 0 || c >= size) return;
        if (opened[r][c] || flagged[r][c]) return;

        opened[r][c] = true;

        // Jika kosong (0), teruskan ke 8 tetangga
        if (board[r][c] == 0) {
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr != 0 || dc != 0) {
                        floodFill(r + dr, c + dc);
                    }
                }
            }
        }
    }

    // KONDISI MENANG

    // Fungsi: Mengecek apakah semua bom sudah ditandai dengan benar
    void checkWinCondition() {
        int correctFlags = 0;
        int incorrectFlags = 0;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (flagged[i][j]) {
                    if (board[i][j] == -1) correctFlags++;
                    else incorrectFlags++;
                }
            }
        }

        if (correctFlags == totalBombs && incorrectFlags == 0) {
            gameWon = true;
            gameOver = true;
        }
    }

public:
    // --- Constructor ---
    MinesweeperGame() {
        gameOver = false;
        gameWon = false;
        flagsPlaced = 0;
        isFirstMove = true; 
    }

    // SETUP & INISIALISASI
    
    // Fungsi: Mengatur ukuran papan dan jumlah bom sebelum main
    void setup() {
        cout << "\n--- SETUP PERMAINAN ---\n";
        
        do {
            cout << "Masukkan ukuran papan (4-10): ";
            cin >> size;
        } while (size < 4 || size > 10);

        int maxBombs = (size * size) - 1;
        do {
            cout << "Masukkan jumlah bom (1-" << maxBombs << "): ";
            cin >> totalBombs;
        } while (totalBombs < 1 || totalBombs > maxBombs);

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                board[i][j] = 0;
                opened[i][j] = false;
                flagged[i][j] = false;
            }
        }

        flagsPlaced = 0;
        gameOver = false;
        gameWon = false;
        isFirstMove = true; 
        startTime = time(0); 
    }

    // TAMPILAN UI
    
    // Fungsi: Mencetak papan permainan ke console
    void displayBoard(bool revealAll = false) {
        cout << "\n===============================\n";
        
        int elapsedSeconds = time(0) - startTime;
        cout << "Waktu: " << elapsedSeconds << " detik | ";
        cout << "Sisa Bom (Estimasi): " << totalBombs - flagsPlaced << "\n\n";

        cout << "    ";
        for (int c = 0; c < size; ++c) cout << c + 1 << " ";
        cout << "\n   ";
        for (int c = 0; c < size; ++c) cout << "--";
        cout << "\n";

        for (int r = 0; r < size; ++r) {
            if (r + 1 < 10) cout << r + 1 << "  |";
            else cout << r + 1 << " |";

            for (int c = 0; c < size; ++c) {
                if (revealAll && board[r][c] == -1) {
                    cout << "* ";
                } else if (flagged[r][c]) {
                    cout << "F ";
                } else if (!opened[r][c]) {
                    cout << "# ";
                } else {
                    if (board[r][c] == 0) cout << ". ";
                    else cout << board[r][c] << " ";
                }
            }
            cout << "\n";
        }
        cout << "===============================\n";
    }

    // LOOP UTAMA PERMAINAN
 
    // Fungsi: Mengelola input pemain 
    void play() {
        while (!gameOver) {
            displayBoard();
            
            char action;
            int r, c;
            cout << "\nAksi - (B)uka / (T)andai / (H)apus Tanda\n";
            cout << "Format: [Aksi] [Baris] [Kolom] (contoh: B 2 3): ";
            cin >> action >> r >> c;

            r--; c--; // Konversi input 1..N menjadi index 0..N-1

            if (r < 0 || r >= size || c < 0 || c >= size) {
                cout << "=> Koordinat tidak valid! Silakan coba lagi.\n";
                continue;
            }

            if (action == 'B' || action == 'b') {
                if (flagged[r][c]) {
                    cout << "=> Kotak ini ditandai bendera. Hapus tanda dulu untuk membuka!\n";
                } else {
                    // Logika Langkah Pertama Aman
                    if (isFirstMove) {
                        placeBombs(r, c);       
                        calculateAdjacency();   
                        isFirstMove = false;    
                    }

                    if (board[r][c] == -1) {
                        gameOver = true; // Kena Bom!
                    } else {
                        floodFill(r, c); // Buka area aman
                    }
                }
            } 
            else if (action == 'T' || action == 't') {
                if (!opened[r][c] && !flagged[r][c]) {
                    flagged[r][c] = true;
                    flagsPlaced++;
                }
            } 
            else if (action == 'H' || action == 'h') {
                if (flagged[r][c]) {
                    flagged[r][c] = false;
                    flagsPlaced--;
                }
            } 
            else {
                cout << "=> Aksi tidak dikenali.\n";
            }

            checkWinCondition();
        }

        // --- Akhir Permainan ---
        displayBoard(true); 
        int totalTime = time(0) - startTime;
        
        cout << "\n*** PERMAINAN BERAKHIR ***\n";
        if (gameWon) {
            cout << "SELAMAT! KAMU MENANG! Semua bom berhasil ditandai.\n";
        } else {
            cout << "BOOOM! Kamu menginjak bom! GAME OVER.\n";
        }
        cout << "Waktu total: " << totalTime << " detik.\n";
        cout << "**************************\n";
    }
};

    //FUNGSI MAIN MENU 
int main() {
    srand(time(0)); // Seed untuk randomizer
    int pilihan;

    do {
        cout << "\n=== MAIN MENU MINESWEEPER++ ===\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilih (1/2): ";
        cin >> pilihan;

        if (pilihan == 1) {
            MinesweeperGame game;
            game.setup();
            game.play();
        } else if (pilihan != 2) {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 2);

    cout << "Terima kasih sudah bermain!\n";
    return 0;
}