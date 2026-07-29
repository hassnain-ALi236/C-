#include <iostream>
#include <cstdlib> //random and srand
#include <ctime> //time for srand
using namespace std;
const int ROWS=8;
const int COLS=8;
const int MINES=10;
char board[ROWS][COLS];
bool revealed[ROWS][COLS];
void inotializeBoard();
void initializeBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '-';
            revealed[i][j] = false;
        }
    }
}
void placeMines(){
    int placed=0;
    while(placed < MINES){
        int r= rand() % ROWS; //random row
        int c= rand() % COLS; //random column
        if(board[r][c] != '*'){ 
            board[r][c]='*';
            placed++;
        }
    }
}
void calculateNumbers(){
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLS; j++){
            if(board[i][j]=='*')
                continue;
            int count=0;
            for(int x=-1; x<=1; x++){  //
                for(int y=-1; y<=1; y++){ //check all 8 neighbors
                    int ni=i+x; //new i
                    int nj=j+y;     //new j
                    if(ni>=0 && ni<ROWS && nj>=0 && nj<COLS){ //valid neighbor
                        if(board[ni][nj]=='*') //if neighbor is mine
                            count++;
                    }
                }
            }
            board[i][j]= count + '0'; //convert to char
        }
    }
}
void displayBoard(){
    system("cls"); 
    cout << "   ";
    for(int c=0; c<COLS; c++) //column numbers
        cout << c << " "; 
    cout << endl;
    for(int i=0; i<ROWS; i++){ 
        cout << i << " |";
        for(int j=0; j<COLS; j++){
            if(revealed[i][j])
                cout << board[i][j] << " ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}
void revealCell(int r, int c){
    if(r<0 || r>=ROWS || c<0 || c>=COLS || revealed[r][c])
        return;
    revealed[r][c]=true;
    if(board[r][c]=='0'){
        for(int x=-1; x<=1; x++){
            for(int y=-1; y<=1; y++){
                if(x!=0 || y!=0)
                    revealCell(r+x, c+y);
            }
        }
    }
}
void gameLoop(){
    int r, c;
    while(true){
        displayBoard();
        cout << "Enter row and column to reveal (e.g., 3 4): ";
        cin >> r >> c;
        if(r<0 || r>=ROWS || c<0 || c>=COLS){
            cout << "Invalid coordinates. Try again.\n";
            continue;
        }
        if(board[r][c]=='*'){
            for(int i=0; i<ROWS; i++){
                for(int j=0; j<COLS; j++){
                    if(board[i][j]=='*')
                        revealed[i][j] = true;
                }
            }
            displayBoard();
            cout << "\nGame Over! You hit a mine.\n";
            system("pause");
            break;
        }


        revealCell(r, c);
    }
}  
int main(){
 srand(static_cast<unsigned int>(time(0)));
    initializeBoard();
    placeMines();
    calculateNumbers();
    gameLoop();
    return 0;
}