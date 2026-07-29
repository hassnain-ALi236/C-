#include <iostream>      
#include <string>        
#include <fstream>       
#include <cstdlib>       // rand(), srand() ke liye
#include <ctime>         // time() ke liye

const int MAX = 12;      // maximum board size

int r, c, m;             // rows, columns, mines

// game record save karne ka function
void saverecord(const std::string &playerName, const std::string &levelName, const std::string &result);
void inigame();
void placemines();
void calcualate_mines();
void displayboard();
void gameloop();
void saverecord();                                 
void instructions();
void gamerecord();

// minesweeper board aur reveal status
char board[MAX][MAX];
bool revealed[MAX][MAX];

using namespace std;

string playerName, levelName;
int revealedSafe = 0;    // kitne safe cells reveal ho chuke
int safeCells = 0;       // total safe cells

// game board initialize karna
void inigame() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            board[i][j] = '-';       // initially sab hidden
            revealed[i][j] = false; 
                }
    }
}

// randomly mines place karna
void placemines() {
    int placed = 0;
    while (placed < m) {
        int R = rand() % r;
        int C = rand() % c;
        if (board[R][C] != '*') {
            board[R][C] = '*';   
            placed++;
        }
    }
}

// har cell ke around mines count karna
void calcualate_mines() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (board[i][j] == '*') {
                continue;   // agar khud mine hai to skip
            }
            int count = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue;
                    int ni = i + x;
                    int nj = j + y;
                    if (ni >= 0 && ni < r && nj >= 0 && nj < c) {
                        if (board[ni][nj] == '*') {
                            count++;
                        }
                    }
                }
            }
            board[i][j] = count + '0';   // number store as character
        }
    }
}

// board ko screen par show karna
void displayboard() {
    system("cls");    
    cout << "   ";
    for (int col = 0; col < c; col++) {
        cout << col << " ";
    }
    cout << endl;

    for (int i = 0; i < r; i++) {
        cout << i << " |";
        for (int j = 0; j < c; j++) {
            if (revealed[i][j]) {
                cout << board[i][j] << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
}

// selected cell ko reveal karna (recursive)
void revealcell(int R, int C) {
    if (R < 0 || R >= r || C < 0 || C >= c || revealed[R][C]) {
        return;
    }

    revealed[R][C] = true;

    if (board[R][C] != '*') {
        revealedSafe++;
    }

    if (board[R][C] == '0') {
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (x == 0 && y == 0) continue;
                revealcell(R + x, C + y);
            }
        }
    }
}

// main game loop
void gameloop() {
    int R, C;
    while (true) {
        displayboard();
        cout << "Enter row and column to reveal ( -1  -1 to exit): ";
        cin >> R >> C;

        if (R == -1 && C == -1) {
            cout << "Game exited." << endl;
            break;
        }

        revealcell(R, C);

        // mine hit condition
        if (board[R][C] == '*') {
            displayboard();
            cout << "Game Over! You hit a mine." << endl;
            saverecord(playerName, levelName, "Lose");
            break;
        }

        // win condition
        if (revealedSafe == safeCells) {
            displayboard();
            cout << "Congratulations! You revealed all safe cells!" << endl;
            saverecord(playerName, levelName, "Win");
            break;
        }
    }
}

// game instructions
void instructions() {
    cout << "==============================" << endl;
    cout << "Welcome to Minesweeper!" << endl;
    cout << "==============================" << endl;
    cout << endl;
    cout << "Uncover all cells without mines to win." << endl;
    cout << "Enter row and column numbers to reveal a cell." << endl;
    cout << endl;
    cout << "==============================" << endl;
    cout << "Good luck!" << endl;
    cout << "==============================" << endl;
}

// game result file me save karna
void saverecord(const string &playerName, const string &levelName, const string &result) {
    ofstream fout("scores.txt", ios::app);
    if (fout.is_open()) {
        fout << playerName << " " << levelName << " " << result << endl;
        fout.close();
    } else {
        cout << "Error: Unable to save score." << endl;
    }
}

// previous game records show karna
void gamerecord() {
    ifstream fin("scores.txt");
    if (fin.is_open()) {
        string line;
        cout << "\n------- HIGH SCORES -------\n";
        while (getline(fin, line)) {
            cout << line << endl;
        }
        cout << "===========================\n";
        fin.close();
    } else {
        cout << "No scores found.\n";
    }
}

int main() {
    int choice = 0;

    while (choice != 4) {
        cout << "1- Instructions" << endl;
        cout << "2- Start Game" << endl;
        cout << "3- View History" << endl;
        cout << "4- Exit" << endl;
        cin >> choice;

        if (choice == 1) {
            instructions();
        }

        if (choice == 2) {
            cout << "GAME LEVELS:" << endl;
            cout << "1- Easy (8x8 with 10 mines)" << endl;
            cout << "2- Medium (10x10 with 20 mines)" << endl;
            cout << "3- Hard (12x12 with 30 mines)" << endl;

            int levchoice;
            cin >> levchoice;

            cout << "Enter player name: ";
            cin.ignore();
            getline(cin, playerName);

            if (levchoice == 1) {
                levelName = "Easy";
                r = 8; c = 8; m = 10;
            }
            else if (levchoice == 2) {
                levelName = "Medium";
                r = 10; c = 10; m = 20;
            }
            else if (levchoice == 3) {
                levelName = "Hard";
                r = 12; c = 12; m = 30;
            }

            srand(time(0));     // random seed
            inigame();
            placemines();
            calcualate_mines();

            safeCells = r * c - m;
            revealedSafe = 0;

            gameloop();
        }

        if (choice == 3) {
            gamerecord();
        }

        if (choice == 4) {
            cout << "Exiting the game. Goodbye!" << endl;
            break;
        }
    }
    return 0;
}
