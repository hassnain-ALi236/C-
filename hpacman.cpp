#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

/* ---------- CURSOR POSITIONING ---------- */
void setCursorPosition(int xPos, int yPos) {
    COORD coordinate;
    coordinate.X = xPos;
    coordinate.Y = yPos;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

/* ---------- GAME BOARD ---------- */
char gameBoard[14][52] = {
    "###################################################",
    "#P..........#.................#...................#",
    "#.............................#...................#",
    "#.##....##.....................#..................#",
    "#.#.....#.....................###########.........#",
    "#.#.....#...#.............................#.......#",
    "#.#.....#...##########..........######....#.......#",
    "#.#.....#............#..........#....#....#.......#",
    "#.#######........................#.G..#....########",
    "#....................#..........#....#............#",
    "#.........................G.....######............#",
    "#.......G............#............................#",
    "#....................##########.............G.....#",
    "###################################################"
};

// Separate array for tracking collectibles
char foodMap[14][52];

/* ---------- GAME VARIABLES ---------- */
int playerRow = 1, playerCol = 1;
int enemy1Row = 8, enemy1Col = 37;
int enemy2Row = 10, enemy2Col = 26;
int enemy3Row = 11, enemy3Col = 9;
int enemy4Row = 12, enemy4Col = 44;
int currentScore = 0;
int remainingLives = 3;
int moveCounter = 0;

/* ---------- DATA PERSISTENCE ---------- */
void recordScore() {
    ofstream fileStream;
    fileStream.open("game_records.txt", ios::app);
    
    if (fileStream.is_open()) {
        fileStream << "Points: " << currentScore << " | Remaining Lives: " << remainingLives << endl;
        fileStream.close();
        cout << "\n\nGame data saved successfully!" << endl;
    } else {
        cout << "\n\nFile error occurred!" << endl;
    }
}

int retrieveTopScore() {
    ifstream fileStream("game_records.txt");
    int topScore = 0;
    
    if (fileStream.is_open()) {
        string textLine;
        while (getline(fileStream, textLine)) {
            size_t position = textLine.find("Points: ");
            if (position != string::npos) {
                string scoreText = textLine.substr(position + 8);
                int extractedScore = atoi(scoreText.c_str());
                if (extractedScore > topScore) {
                    topScore = extractedScore;
                }
            }
        }
        fileStream.close();
    }
    return topScore;
}

/* ---------- SETUP FOOD MAP ---------- */
void setupFoodMap() {
    int row = 0;
    while (row < 14) {
        int col = 0;
        while (col < 52) {
            foodMap[row][col] = gameBoard[row][col];
            col++;
        }
        row++;
    }
}

/* ---------- RENDER BOARD ---------- */
void renderBoard() {
    int row = 0;
    do {
        int col = 0;
        do {
            cout << gameBoard[row][col];
            col++;
        } while (col < 51);
        cout << endl;
        row++;
    } while (row < 14);
    
    int topScore = retrieveTopScore();
    cout << "\nPoints: " << currentScore << "   Lives: " << remainingLives;
    if (topScore > 0) {
        cout << "   Best Score: " << topScore;
    }
    cout << endl;
}

/* ---------- REFRESH STATS ---------- */
void refreshStats() {
    setCursorPosition(0, 15);
    int topScore = retrieveTopScore();
    cout << "Points: " << currentScore << "   Lives: " << remainingLives;
    if (topScore > 0) {
        cout << "   Best Score: " << topScore;
    }
    cout << "     ";
}

/* ---------- ENEMY INTELLIGENCE ---------- */
void updateEnemyPosition(int &enemyRow, int &enemyCol) {
    int previousRow = enemyRow, previousCol = enemyCol;
    
    // Clear enemy from display
    setCursorPosition(enemyCol, enemyRow);
    if (foodMap[enemyRow][enemyCol] == '.') {
        cout << '.';
    } else {
        cout << ' ';
    }
    
    // Calculate chase direction
    int rowDelta = 0, colDelta = 0;
    
    // Prioritize movement axis based on distance
    if (abs(playerRow - enemyRow) > abs(playerCol - enemyCol)) {
        // Prioritize vertical movement
        rowDelta = (playerRow > enemyRow) ? 1 : (playerRow < enemyRow) ? -1 : 0;
    } else {
        // Prioritize horizontal movement
        colDelta = (playerCol > enemyCol) ? 1 : (playerCol < enemyCol) ? -1 : 0;
    }
    
    // Calculate target position
    int targetRow = enemyRow + rowDelta;
    int targetCol = enemyCol + colDelta;
    
    // Validate and move
    if (targetRow >= 1 && targetRow <= 12 && targetCol >= 1 && targetCol <= 49 && gameBoard[targetRow][targetCol] != '#') {
        enemyRow = targetRow;
        enemyCol = targetCol;
    } else {
        // Alternative movement when blocked
        if (rowDelta != 0) {
            // Try horizontal instead
            int altCol = enemyCol + ((playerCol > enemyCol) ? 1 : -1);
            if (altCol >= 1 && altCol <= 49 && gameBoard[enemyRow][altCol] != '#') {
                enemyCol = altCol;
            }
        } else {
            // Try vertical instead
            int altRow = enemyRow + ((playerRow > enemyRow) ? 1 : -1);
            if (altRow >= 1 && altRow <= 12 && gameBoard[altRow][enemyCol] != '#') {
                enemyRow = altRow;
            }
        }
    }
    
    // Display enemy at new position
    setCursorPosition(enemyCol, enemyRow);
    cout << 'G';
}

/* ---------- GAME EXECUTION ---------- */
int main() {
    srand(time(0));
    system("cls");
    
    setupFoodMap();
    renderBoard();

    while (remainingLives > 0) {

        /* ---------- PLAYER INPUT ---------- */
        if (_kbhit()) {
            int keyPress = _getch();
            if (keyPress == 0 || keyPress == 224)
                keyPress = _getch();

            int previousRow = playerRow, previousCol = playerCol;

            // Arrow key detection
            switch (keyPress) {
                case 72: // Up arrow
                    if (playerRow > 1) playerRow--;
                    break;
                case 80: // Down arrow
                    if (playerRow < 12) playerRow++;
                    break;
                case 75: // Left arrow
                    if (playerCol > 1) playerCol--;
                    break;
                case 77: // Right arrow
                    if (playerCol < 49) playerCol++;
                    break;
            }

            // Validate movement
            if (gameBoard[playerRow][playerCol] != '#') {
                
                // Check for food collection
                if (foodMap[playerRow][playerCol] == '.') {
                    currentScore += 10;
                    foodMap[playerRow][playerCol] = ' ';
                    refreshStats();
                }

                setCursorPosition(previousCol, previousRow);
                // Restore food if present at old position
                cout << ((foodMap[previousRow][previousCol] == '.') ? '.' : ' ');

                gameBoard[previousRow][previousCol] = (foodMap[previousRow][previousCol] == '.') ? '.' : ' ';
                gameBoard[playerRow][playerCol] = 'P';

                setCursorPosition(playerCol, playerRow);
                cout << 'P';
            } else {
                // Revert invalid movement
                playerRow = previousRow;
                playerCol = previousCol;
            }
        }

        /* ---------- ENEMY UPDATES ---------- */
        moveCounter++;
        if (moveCounter >= 5) {
            updateEnemyPosition(enemy1Row, enemy1Col);
            updateEnemyPosition(enemy2Row, enemy2Col);
            updateEnemyPosition(enemy3Row, enemy3Col);
            updateEnemyPosition(enemy4Row, enemy4Col);
            moveCounter = 0;
        }

        /* ---------- COLLISION DETECTION ---------- */
        bool collisionDetected = (playerRow == enemy1Row && playerCol == enemy1Col) ||
                                 (playerRow == enemy2Row && playerCol == enemy2Col) ||
                                 (playerRow == enemy3Row && playerCol == enemy3Col) ||
                                 (playerRow == enemy4Row && playerCol == enemy4Col);
        
        if (collisionDetected) {
            remainingLives--;

            // Reset positions
            playerRow = 1; playerCol = 1;
            enemy1Row = 8; enemy1Col = 37;
            enemy2Row = 10; enemy2Col = 26;
            enemy3Row = 11; enemy3Col = 9;
            enemy4Row = 12; enemy4Col = 44;

            system("cls");
            
            // Restore board state
            for (int r = 0; r < 14; r++) {
                for (int c = 0; c < 52; c++) {
                    if (foodMap[r][c] == '.') {
                        gameBoard[r][c] = '.';
                    } else if (gameBoard[r][c] != '#' && gameBoard[r][c] != 'P' && gameBoard[r][c] != 'G') {
                        gameBoard[r][c] = ' ';
                    }
                }
            }
            
            gameBoard[playerRow][playerCol] = 'P';
            
            renderBoard();
            setCursorPosition(20, 17);
            cout << "Life Lost! Remaining: " << remainingLives;
            Sleep(1800);
            setCursorPosition(20, 17);
            cout << "                                    ";
            refreshStats();
        }

        Sleep(90);
    }

    // Game over sequence
    setCursorPosition(15, 18);
    cout << "GAME OVER! FINAL POINTS: " << currentScore << "    ";
    
    recordScore();
    
    setCursorPosition(15, 19);
    getch();
    return 0;
}