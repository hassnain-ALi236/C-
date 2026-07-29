#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int EASY = 10;
const int MEDIUM = 15;
const int HARD = 20;

class Minesweeper {
private:
    int size;
    int mineCount;
    char** board;          // Actual board with mines and numbers
    bool** revealed;       // Track revealed cells
    bool** flagged;        // Track flagged cells
    int revealedCount;
    bool gameOver;
    bool won;

public:
    Minesweeper(int s, int mines) {
        size = s;
        mineCount = mines;
        revealedCount = 0;
        gameOver = false;
        won = false;

        // Dynamically allocate 2D arrays
        board = new char*[size];
        revealed = new bool*[size];
        flagged = new bool*[size];

        for (int i = 0; i < size; i++) {
            board[i] = new char[size];
            revealed[i] = new bool[size];
            flagged[i] = new bool[size];
        }

        initializeBoard();
    }

    ~Minesweeper() {
        // Free memory
        for (int i = 0; i < size; i++) {
            delete[] board[i];
            delete[] revealed[i];
            delete[] flagged[i];
        }
        delete[] board;
        delete[] revealed;
        delete[] flagged;
    }

    void initializeBoard() {
        // Initialize all cells
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = '0';
                revealed[i][j] = false;
                flagged[i][j] = false;
            }
        }

        placeMines();
        calculateNumbers();
    }

    void placeMines() {
        int placedMines = 0;
        srand(time(0));

        while (placedMines < mineCount) {
            int row = rand() % size;
            int col = rand() % size;

            if (board[row][col] != '*') {
                board[row][col] = '*';
                placedMines++;
            }
        }
    }

    void calculateNumbers() {
        // Directions: up, down, left, right, and 4 diagonals
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == '*') continue;

                int count = 0;
                // Check all 8 adjacent cells
                for (int k = 0; k < 8; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];

                    if (isValid(ni, nj) && board[ni][nj] == '*') {
                        count++;
                    }
                }
                board[i][j] = '0' + count;
            }
        }
    }

    bool isValid(int row, int col) {
        return row >= 0 && row < size && col >= 0 && col < size;
    }

    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void displayBoard(bool showMines = false) {
        system("cls");
        
        cout << "\n\t\t=== MINESWEEPER GAME ===" << endl;
        cout << "\t\tMines: " << mineCount << " | Flags Available: " << mineCount << endl;
        cout << "\t\tRevealed: " << revealedCount << "/" << (size * size - mineCount) << endl << endl;

        // Print column numbers
        cout << "     ";
        for (int j = 0; j < size; j++) {
            cout << j << "   ";
        }
        cout << endl;

        // Print top border
        cout << "   +";
        for (int j = 0; j < size; j++) {
            cout << "---+";
        }
        cout << endl;

        // Print board
        for (int i = 0; i < size; i++) {
            cout << " " << i << " |";
            
            for (int j = 0; j < size; j++) {
                if (flagged[i][j] && !showMines) {
                    setColor(12); // Red
                    cout << " F ";
                    setColor(7);  // White
                } else if (revealed[i][j] || showMines) {
                    if (board[i][j] == '*') {
                        setColor(12); // Red
                        cout << " * ";
                        setColor(7);
                    } else if (board[i][j] == '0') {
                        cout << "   ";
                    } else {
                        setColor(10); // Green
                        cout << " " << board[i][j] << " ";
                        setColor(7);
                    }
                } else {
                    setColor(8); // Gray
                    cout << " - ";
                    setColor(7);
                }
                cout << "|";
            }
            
            cout << endl;

            // Print horizontal border
            cout << "   +";
            for (int j = 0; j < size; j++) {
                cout << "---+";
            }
            cout << endl;
        }

        cout << "\n Commands: R = Reveal | F = Flag | Q = Quit" << endl;
    }

    void revealCell(int row, int col) {
        if (!isValid(row, col) || revealed[row][col] || flagged[row][col]) {
            return;
        }

        revealed[row][col] = true;
        revealedCount++;

        // If mine hit
        if (board[row][col] == '*') {
            gameOver = true;
            return;
        }

        // If empty cell, reveal adjacent cells recursively
        if (board[row][col] == '0') {
            int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

            for (int k = 0; k < 8; k++) {
                revealCell(row + dx[k], col + dy[k]);
            }
        }
    }

    void toggleFlag(int row, int col) {
        if (!isValid(row, col) || revealed[row][col]) {
            return;
        }
        flagged[row][col] = !flagged[row][col];
    }

    bool checkWin() {
        if (revealedCount == (size * size - mineCount)) {
            won = true;
            gameOver = true;
            return true;
        }
        return false;
    }

    void play() {
        char action;
        int row, col;

        while (!gameOver) {
            displayBoard();

            cout << "\nEnter action (R/F): ";
            cin >> action;
            action = toupper(action);

            if (action == 'Q') {
                gameOver = true;
                cout << "\nGame quit! Thanks for playing!" << endl;
                return;
            }

            cout << "Enter row: ";
            cin >> row;
            cout << "Enter column: ";
            cin >> col;

            if (!isValid(row, col)) {
                cout << "\nInvalid position! Press any key to continue...";
                getch();
                continue;
            }

            if (action == 'R') {
                revealCell(row, col);
            } else if (action == 'F') {
                toggleFlag(row, col);
            } else {
                cout << "\nInvalid action! Press any key to continue...";
                getch();
                continue;
            }

            checkWin();
        }

        // Game over - show final board
        displayBoard(true);

        if (won) {
            setColor(10);
            cout << "\n\t*** CONGRATULATIONS! YOU WON! ***" << endl;
            setColor(7);
        } else {
            setColor(12);
            cout << "\n\t*** GAME OVER! YOU HIT A MINE! ***" << endl;
            setColor(7);
        }

        cout << "\nPress any key to continue...";
        getch();
    }
};

void displayMenu() {
    system("cls");
    cout << "\n\n";
    cout << "\t ========================================" << endl;
    cout << "\t|                                        |" << endl;
    cout << "\t|       MINESWEEPER GAME IN C++         |" << endl;
    cout << "\t|                                        |" << endl;
    cout << "\t ========================================" << endl;
    cout << "\n\t Select Difficulty Level:" << endl;
    cout << "\t 1. Easy   (10x10, 10 mines)" << endl;
    cout << "\t 2. Medium (15x15, 30 mines)" << endl;
    cout << "\t 3. Hard   (20x20, 60 mines)" << endl;
    cout << "\t 4. Exit" << endl;
    cout << "\n\t Enter your choice: ";
}

int main() {
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                Minesweeper game(10, 10);
                game.play();
                break;
            }
            case 2: {
                Minesweeper game(15, 30);
                game.play();
                break;
            }
            case 3: {
                Minesweeper game(20, 60);
                game.play();
                break;
            }
            case 4:
                running = false;
                cout << "\n\tThank you for playing! Goodbye!" << endl;
                break;
            default:
                cout << "\n\tInvalid choice! Press any key to continue...";
                getch();
        }
    }

    return 0;
}