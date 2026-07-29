    #include <iostream>
    #include <conio.h>
    #include <windows.h>
    #include <cstdlib>
    #include <ctime>
    #include <fstream>
    #include <string>
    using namespace std;
    void gotooxy();
    void saveScore();
    int loadHighScore();
    void initDotGrid();
    void printMaze();
    void updateScore();
    void moveGhost(int &gx, int &gy);

    /* ---------- GOTXY FUNCTION ---------- */
    void gotoxy(int x, int y) {
        COORD c;
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    /* ---------- MAZE ---------- */
    char grid[17][76] = {
        "###########################################################################",
        "#P....................................#...................................#",
        "#.....########.......#................#...................##############..#",
        "#.....#..............#................#...............................#...#",
        "#.....#..............##################...............................#...#",
        "#.....########................................................########....#",
        "#.........................................................#...............#",
        "#..........................######.........................#...............#",
        "#..........................#....#.................................#########",
        "#..........................#....#.....................................#...#",
        "#..........................#....#.........................#...........#...#",
        "#..........#############...#....#.........................#...........#...#",
        "#..........#...............#....#######...................#...........#...#",
        "#..........#...............#..................##############..........#...#",
        "#..........#...............#..G.......................................#G..#",
        "#..........#...............#..........................................#...#",
        "###########################################################################"
    };

    // Grid to track dots separately (ghosts won't eat these)
    char dotGrid[17][76];

    /* ---------- VARIABLES ---------- */
    int px = 1, py = 1;          // Player position
    int g1x = 14, g1y = 22;      // Ghost 1
    int g2x = 14, g2y = 70;      // Ghost 2
    int g3x = 8, g3y = 30;       // Ghost 3
    int g4x = 10, g4y = 50;      // Ghost 4
    int g5x = 6, g5y = 40;       // Ghost 5
    int score = 0;
    int lives = 3;
    int ghostMoveCounter = 0;

    /* ---------- FILE HANDLING FUNCTIONS ---------- */
    void saveScore() {
        ofstream outFile;
        outFile.open("pac.txt", ios::app);
        
        if (outFile.is_open()) {
            outFile << "Score: " << score << " | Lives Left: " << lives << endl;
            outFile.close();
            cout << "\n\nScore successfully saved to pac.txt!" << endl;
        } else {
            cout << "\n\nError: Could not create/open pac.txt file!" << endl;
        }
    }

    int loadHighScore() {
        ifstream inFile("pac.txt");
        int highScore = 0;
        
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                size_t pos = line.find("Score: ");
                if (pos != string::npos) {
                    string scoreStr = line.substr(pos + 7);
                    int tempScore = atoi(scoreStr.c_str());
                    if (tempScore > highScore) {
                        highScore = tempScore;
                    }
                }
            }
            inFile.close();
        }
        return highScore;
    }

    /* ---------- INITIALIZE DOT GRID ---------- */
    void initDotGrid() {
        for (int i = 0; i < 17; i++) {
            for (int j = 0; j < 76; j++) {
                dotGrid[i][j] = grid[i][j];
            }
        }
    }

    /* ---------- PRINT MAZE ---------- */
    void printMaze() {
        for (int i = 0; i < 17; i++) {
            for (int j = 0; j < 75; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
        
        int highScore = loadHighScore();
        cout << "\nScore: " << score << "   Lives: " << lives;
        if (highScore > 0) {
            cout << "   High Score: " << highScore;
        }
        cout << endl;
    }

    /* ---------- UPDATE SCORE ---------- */
    void updateScore() {
        gotoxy(0, 18);
        int highScore = loadHighScore();
        cout << "Score: " << score << "   Lives: " << lives;
        if (highScore > 0) {
            cout << "   High Score: " << highScore;
        }
        cout << "     ";
    }

    /* ---------- GHOST CHASE MOVEMENT ---------- */
    void moveGhost(int &gx, int &gy) {
        int old_gx = gx, old_gy = gy;
        
        // Clear ghost from screen (restore dot if present)
        gotoxy(gy, gx);
        if (dotGrid[gx][gy] == '.') {
            cout << '.';
        } else {
            cout << ' ';
        }
        
        // Chase logic: move towards Pacman
        int dx = 0, dy = 0;
        
        // Determine direction to chase Pacman
        if (abs(px - gx) > abs(py - gy)) {
            // Move vertically
            if (px > gx) dx = 1;      // Move down
            else if (px < gx) dx = -1; // Move up
        } else {
            // Move horizontally
            if (py > gy) dy = 1;      // Move right
            else if (py < gy) dy = -1; // Move left
        }
        
        // Try to move in chase direction
        int new_gx = gx + dx;
        int new_gy = gy + dy;
        
        // Check if new position is valid (not a wall and within bounds)
        if (new_gx >= 1 && new_gx <= 15 && new_gy >= 1 && new_gy <= 73 && grid[new_gx][new_gy] != '#') {
            gx = new_gx;
            gy = new_gy;
        } else {
            // If can't move towards Pacman, try alternative directions
            // Try the other axis
            if (dx != 0) {
                // Was trying vertical, now try horizontal
                if (py > gy && gy < 73 && grid[gx][gy + 1] != '#') {
                    gy++;
                } else if (py < gy && gy > 1 && grid[gx][gy - 1] != '#') {
                    gy--;
                }
            } else {
                // Was trying horizontal, now try vertical
                if (px > gx && gx < 15 && grid[gx + 1][gy] != '#') {
                    gx++;
                } else if (px < gx && gx > 1 && grid[gx - 1][gy] != '#') {
                    gx--;
                }
            }
        }
        
        // Draw ghost at new position
        gotoxy(gy, gx);
        cout << 'G';
    }

    /* ---------- MAIN ---------- */
    int main() {
        srand(time(0));
        system("cls");
        
        // Initialize dot grid
        initDotGrid();
        
        printMaze();

        while (lives > 0) {

            /* ---------- PLAYER MOVEMENT ---------- */
            if (_kbhit()) {
                int key = _getch();
                if (key == 0 || key == 224)
                    key = _getch();

                int oldx = px, oldy = py;

                if (key == 72 && px > 1) px--;      // Up
                if (key == 80 && px < 15) px++;     // Down
                if (key == 75 && py > 1) py--;      // Left
                if (key == 77 && py < 73) py++;     // Right

                if (grid[px][py] != '#') {
                    
                    // Check if there's a dot in dotGrid (not grid)
                    if (dotGrid[px][py] == '.') {
                        score += 5;
                        dotGrid[px][py] = ' ';  // Remove dot from dotGrid
                        updateScore();
                    }

                    gotoxy(oldy, oldx);
                    // Restore dot if present
                    if (dotGrid[oldx][oldy] == '.') {
                        cout << '.';
                    } else {
                        cout << ' ';
                    }

                    grid[oldx][oldy] = (dotGrid[oldx][oldy] == '.') ? '.' : ' ';
                    grid[px][py] = 'P';

                    gotoxy(py, px);
                    cout << 'P';
                }
                else {
                    px = oldx;
                    py = oldy;
                }
            }

            /* ---------- GHOST MOVEMENT ---------- */
            // Ghosts move every 4 frames (slower than player for fair gameplay)
            ghostMoveCounter++;
            if (ghostMoveCounter >= 4) {
                moveGhost(g1x, g1y);
                moveGhost(g2x, g2y);
                moveGhost(g3x, g3y);
                moveGhost(g4x, g4y);
                moveGhost(g5x, g5y);
                ghostMoveCounter = 0;
            }

            /* ---------- COLLISION ---------- */
            if ((px == g1x && py == g1y) || (px == g2x && py == g2y) || (px == g3x && py == g3y) || (px == g4x && py == g4y) || (px == g5x && py == g5y)) {
                lives--;

                px = 1; py = 1;
                g1x = 14; g1y = 22;
                g2x = 14; g2y = 70;
                g3x = 8; g3y = 30;
                g4x = 10; g4y = 50;
                g5x = 6; g5y = 40;

                system("cls");
                
                // Restore grid from dotGrid
                for (int i = 0; i < 17; i++) {
                    for (int j = 0; j < 76; j++) {
                        if (dotGrid[i][j] == '.') {
                            grid[i][j] = '.';
                        } else if (grid[i][j] != '#' && grid[i][j] != 'P' && grid[i][j] != 'G') {
                            grid[i][j] = ' ';
                        }
                    }
                }
                
                grid[px][py] = 'P';
                
                printMaze();
                gotoxy(30, 20);
                cout << "Life Lost! Lives remaining: " << lives;
                Sleep(1500);
                gotoxy(30, 20);
                cout << "                                    ";
                updateScore();
            }

            Sleep(100);
        }

        // Save score to file when game ends
        gotoxy(25, 21);
        cout << "GAME OVER! FINAL SCORE: " << score << "    ";
        
        saveScore();
        
        gotoxy(25, 22);
        getch();
        return 0;
    }