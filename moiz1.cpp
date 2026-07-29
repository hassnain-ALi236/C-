#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <ctime>
using namespace std;

// Maze dimensions
const int ROWS = 15;
const int COLS = 41;

char mazeOriginal[ROWS][COLS] = {
    "########################################",
    "#........#.........#.........#.........#",
    "#.####...#.#######.#.#######.#...####..#",
    "#....#.............#.............#.....#",
    "#.##.#.#####.#####.#.#####.#####.#.##..#",
    "#....#...#...#...........#...#...#.....#",
    "####.###.#.###.#########.###.#.###.#####",
    "#........#..........@........#.........#",
    "####.###.#.###.#########.###.#.###.#####",
    "#....#...#...#...........#...#...#.....#",
    "#.##.#.#####.#.#########.#.#####.#.##..#",
    "#....#.............#.............#.....#",
    "#.####...#.#######.#.#######.#...####..#",
    "#........#.........#.........#.........#",
    "########################################"
};

struct Pos { int x, y; };
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

// --- Console Helpers ---
void setColor(int c){ SetConsoleTextAttribute(hOut, c); }
void clearScreen(){ system("cls"); }
void resetCursor(){ COORD p={0,0}; SetConsoleCursorPosition(hOut,p); }

// Hides cursor for smooth graphics
void hideCursor(){ 
    CONSOLE_CURSOR_INFO i;
    i.dwSize = 25;
    i.bVisible = FALSE; 
    SetConsoleCursorInfo(hOut,&i); 
}

// Shows cursor for Menu input
void showCursor(){ 
    CONSOLE_CURSOR_INFO i;
    i.dwSize = 25;
    i.bVisible = TRUE; 
    SetConsoleCursorInfo(hOut,&i); 
}

int loadHighScore(){ int hs=0; ifstream f("highscore.txt"); if(f) f>>hs; return hs; }
void saveHighScore(int hs){ ofstream f("highscore.txt"); f<<hs; }

bool isFree(char maze[ROWS][COLS],int y,int x){
    if(y<0||y>=ROWS||x<0||x>=COLS-1) return false;
    return maze[y][x]!='#';
}

// --- Drawing ---
void drawMaze(char maze[ROWS][COLS],const Pos& pac,const Pos ghosts[],int gCount,
              int score,int highScore,int lives){
    resetCursor(); // No cls, just reset
    for(int y=0;y<ROWS;y++){
        for(int x=0;x<COLS-1;x++){
            bool ghostHere=false;
            for(int g=0;g<gCount;g++)
                if(ghosts[g].x==x&&ghosts[g].y==y){ 
                    setColor(12); cout<<'G'; setColor(7); 
                    ghostHere=true; break;
                }
            if(ghostHere) continue;

            if(pac.x==x&&pac.y==y){ 
                setColor(14); cout<<'@'; setColor(7); 
                continue;
            }
            if(maze[y][x]=='#'){ setColor(1); cout<<'#'; }
            else if(maze[y][x]=='.'){ setColor(15); cout<<'.'; }
            else cout<<' ';
            setColor(7);
        }
        cout<<'\n';
    }
    setColor(11);
    cout<<"Score: "<<score<<"   High Score: "<<highScore<<"   Lives: "<<lives<<"\n";
    setColor(10);
    cout<<"Use ARROW KEYS | Q to quit | Mega-Maze Mode\n";
    setColor(7);
}

// --- Game Logic ---
void gamePlay(){
    hideCursor(); // HIDE cursor during gameplay for smoothness
    srand((unsigned)time(0));

    // Copy original maze to game maze
    char maze[ROWS][COLS];
    for(int y=0;y<ROWS;y++)
        for(int x=0;x<COLS;x++)
            maze[y][x]=mazeOriginal[y][x];

    Pos pacStart={20,7};
    Pos pac=pacStart;
    Pos ghosts[4]={{1,1},{38,1},{1,13},{38,13}};
    Pos gStart[4]={{1,1},{38,1},{1,13},{38,13}};
    int gCount=4;
    int score=0,lives=3;
    int highScore=loadHighScore();

    // Count dots
    int totalDots=0;
    for(int y=0;y<ROWS;y++)
        for(int x=0;x<COLS-1;x++){
            if(maze[y][x]==' ') maze[y][x]='.';
            if(maze[y][x]=='.') totalDots++;
        }

    clearScreen();

    // Main Game Loop
    while(lives>0){
        drawMaze(maze,pac,ghosts,gCount,score,highScore,lives);
        
        // WIN CONDITION
        if(score>=totalDots){
            resetCursor();
            setColor(10);
            cout<<"\n\n      CONGRATULATIONS! YOU WON!      \n";
            setColor(7);
            Sleep(2000);
            break;
        }

        int nX=pac.x, nY=pac.y;
        if(_kbhit()){
            int ch=_getch();
            if(ch==224){ ch=_getch();
                if(ch==72) nY--;
                else if(ch==80) nY++;
                else if(ch==75) nX--;
                else if(ch==77) nX++;
            }else if(ch=='q'||ch=='Q') break;
        }

        if(isFree(maze,nY,nX)){
            if(maze[nY][nX]=='.'){ score++; maze[nY][nX]=' '; }
            pac.x=nX; pac.y=nY;
        }

        // Ghost AI
        for(int i=0;i<gCount;i++){
            int dir=rand()%4, gx=ghosts[i].x, gy=ghosts[i].y;
            if(dir==0&&isFree(maze,gy-1,gx)) gy--;
            else if(dir==1&&isFree(maze,gy+1,gx)) gy++;
            else if(dir==2&&isFree(maze,gy,gx-1)) gx--;
            else if(dir==3&&isFree(maze,gy,gx+1)) gx++;
            ghosts[i].x=gx; ghosts[i].y=gy;
        }

        // Collision
        bool caught=false;
        for(int i=0;i<gCount;i++)
            if(ghosts[i].x==pac.x&&ghosts[i].y==pac.y) caught=true;

        if(caught){
            lives--;
            resetCursor();
            setColor(12);
            cout<<"\n      CAUGHT! Lives left: "<<lives<<"      \n"; setColor(7);
            Sleep(1000);
            pac=pacStart;
            for(int i=0;i<gCount;i++) ghosts[i]=gStart[i];
        }

        if(score>highScore) highScore=score;
        Sleep(80);
    }

    saveHighScore(loadHighScore()>score?loadHighScore():score);
    clearScreen();
    setColor(14);
    cout<<"GAME OVER, MOIZ!\n";
    cout<<"Final Score: "<<score<<endl;
    setColor(7);
    Sleep(2000);
}

// --- Menus ---
void showHighScore(){
    clearScreen();
    int hs=loadHighScore();
    setColor(11);
    cout<<"=========== HIGH SCORE ===========\n";
    setColor(14);
    cout<<"Highest Score so far: "<<hs<<"\n";
    setColor(7);
    cout<<"\nPress any key to return...";
    _getch();
}

void showInstructions(){
    clearScreen();
    setColor(10);
    cout<<"=========== INSTRUCTIONS ===========\n";
    setColor(7);
    cout<<"1. Use ARROW KEYS to move Pac-Man (@)\n";
    cout<<"2. Eat all dots (.) to win.\n";
    cout<<"3. Avoid ghosts (G). Touch and lose a life.\n";
    cout<<"4. You have 3 lives.\n";
    cout<<"5. Press Q to Quit during game.\n\n";
    cout<<"Press any key to return...";
    _getch();
}

void mainMenu() {
    hideCursor();
    int selected = 0;
    const char* items[] = {"Start Game", "High Score", "Instructions", "Exit"};
    const int itemCount = 4;

    while (true) {
        clearScreen();
        setColor(14);
        cout << "========== PAC-MAN DELUXE ==========\n\n";
        for (int i = 0; i < itemCount; i++) {
            if (i == selected) {
                setColor(11);
                cout << " > " << items[i] << " <\n";
                setColor(7);
            } else {
                cout << "   " << items[i] << "\n";
            }
        }
        cout << "\nUse UP/DOWN ARROWS to move | ENTER to select";

        int ch = _getch();
        if (ch == 224) { // arrow prefix
            ch = _getch();
            if (ch == 72) {              // Up
                selected--;
                if (selected < 0) selected = itemCount - 1;
            } else if (ch == 80) {       // Down
                selected++;
                if (selected >= itemCount) selected = 0;
            }
        } else if (ch == 13) { // Enter key
            if (selected == 0) { gamePlay(); } 
            else if (selected == 1) { showHighScore(); } 
            else if (selected == 2) { showInstructions(); } 
            else if (selected == 3) {
                clearScreen();
                setColor(10);
                cout << "Goodbye, Moiz!\n";
                setColor(7);
                Sleep(1000);
                break;
            }
        }
    }
}

int main(){
    mainMenu();
    return 0;
}