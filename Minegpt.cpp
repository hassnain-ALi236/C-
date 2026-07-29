#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ROWS = 8;
const int COLS = 8;
const int MINES = 10;

char board[ROWS][COLS];
bool revealed[ROWS][COLS];

// Function Prototypes
void initializeBoard();
void placeMines();
void calculateNumbers();
void displayBoard();
bool makeMove();
bool checkWin();

// ---------------- MAIN ----------------
int main() {
    srand(time(0));

    initializeBoard();
    placeMines();
    calculateNumbers();

    bool gameOver = false;

    while (!gameOver) {
        displayBoard();

        if (!makeMove()) {
            cout << "\n💥 BOOM! You hit a mine. GAME OVER 💥\n";
            gameOver = true;
            break;
        }

        if (checkWin()) {
            displayBoard();
            cout << "\n🎉 CONGRATULATIONS! YOU WIN 🎉\n";
            gameOver = true;
        }
    }

    return 0;
}

// ---------------- FUNCTIONS ----------------

void initializeBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '-';
            revealed[i][j] = false;
        }
    }
}

void placeMines() {
    int placed = 0;
    while (placed < MINES) {
        int r = rand() % ROWS;
        int c = rand() % COLS;

        if (board[r][c] != '*') {
            board[r][c] = '*';
            placed++;
        }
    }
}

void calculateNumbers() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (board[i][j] == '*')
                continue;

            int count = 0;

            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    int ni = i + x;
                    int nj = j + y;

                    if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS) {
                        if (board[ni][nj] == '*')
                            count++;
                    }
                }
            }

            board[i][j] = count + '0';
        }
    }
}

void displayBoard() {
    system("cls");

    cout << "------------------------------------\n";
    cout << "|        MINESWEEPER GAME           |\n";
    cout << "------------------------------------\n\n";

    cout << "   ";
    for (int j = 0; j < COLS; j++)
        cout << j << " ";
    cout << endl;

    for (int i = 0; i < ROWS; i++) {
        cout << i << "  ";
        for (int j = 0; j < COLS; j++) {
            if (revealed[i][j])
                cout << board[i][j] << " ";
            else
                cout << "# ";
        }
        cout << endl;
    }
}

bool makeMove() {
    int r, c;
    cout << "\nEnter row and column: ";
    cin >> r >> c;
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
        cout << "Invalid position!\n";
        return true;
    }

    revealed[r][c] = true;

    if (board[r][c] == '*')
        return false;

    return true;
}

bool checkWin() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != '*' && !revealed[i][j])
                return false;
        }
    }
    return true;
}
