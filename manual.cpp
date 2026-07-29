#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
const int MAX=12;
int r,c,m;
char board[MAX][MAX];
bool revealed[MAX][MAX];
using namespace std;

// ================== GAME FUNCTIONS ==================
void inigame(){
    for (int i=0;i<r;i++){
        for ( int j=0;j<c;j++){
            board[i][j]='-';
            revealed[i][j]=false;
        }
    }
}

void placemines(){
    int placed=0;
    while ( placed<m){
        int R=rand() % r;
        int C = rand () % c;
        if ( board[R][C] !='*'){
            board[R][C]='*';
            placed++;
        }
    }
}

void calcualate_mines(){
    for ( int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(board[i][j]=='*') continue;
            int count=0;
            for(int x=-1;x<=1;x++){
                for(int y=-1;y<=1;y++){
                    if(x==0 && y==0) continue;
                    int ni=i+x;
                    int nj=j+y;
                    if(ni>=0 && ni<r && nj>=0 && nj<c){
                        if(board[ni][nj]=='*') count++;
                    }
                }
            }
            board[i][j]=count+'0';
        }
    }
}

void displayboard(){
    system("cls");
    cout<<"   ";
    for ( int col=0;col<c;col++) cout<<col<<" ";
    cout<<endl;
    for ( int i=0;i<r;i++){
        cout<<i<<" |";
        for ( int j=0;j<c;j++){
            if(revealed[i][j]) cout<<board[i][j]<<" ";
            else cout<<"- ";
        }
        cout<<endl;
    }
}

void revealcell(int R,int C){
    if(R<0 || R>=r || C<0 || C>=c || revealed[R][C]) return;
    revealed[R][C]=true;
    if(board[R][C]=='0'){
        for(int x=-1;x<=1;x++){
            for(int y=-1;y<=1;y++){
                if(x==0 && y==0) continue;
                revealcell(R+x,C+y);
            }
        }
    }
}

// ================== FILE HANDLING ==================
void saveScore(const string &playerName, const string &levelName, const string &result){
    ofstream fout("scores.txt", ios::app); // append mode
    if(fout.is_open()){
        fout << playerName << " " << levelName << " " << result << endl;
        fout.close();
    } else {
        cout << "Error: Unable to open file to save score." << endl;
    }
}

void viewScores(){
    ifstream fin("scores.txt");
    if(fin.is_open()){
        string line;
        cout << "\n===== HIGH SCORES =====\n";
        while(getline(fin,line)){
            cout << line << endl;
        }
        cout << "=======================\n";
        fin.close();
    } else {
        cout << "No scores found.\n";
    }
}

// ================== INSTRUCTIONS ==================
void instructions(){
    cout << "==============================" << endl;
    cout<<  "Welcome to Minesweeper!"<<endl;
    cout << "==============================" << endl;
    cout << "Uncover all cells without mines to win."<<endl;
    cout<<"Enter row and column numbers to reveal a cell."<<endl;
    cout<<"Good luck!"<<endl;
}

// ================== GAME LOOP ==================
void gameloop(const string &playerName, const string &levelName){
    int R,C;
    int safeCells = r*c - m;
    int revealedSafe = 0;
    bool gameOver = false;

    while(true){
        displayboard();
        cout<<"Enter row and column to reveal (-1 -1 to exit): ";
        cin>>R>>C;
        if(R==-1 && C==-1){
            cout<<"Game exited."<<endl;
            break;
        }

        if(board[R][C]=='*'){
            displayboard();
            cout<<"Game Over! You hit a mine."<<endl;
            saveScore(playerName, levelName, "Lose");
            gameOver = true;
            break;
        }

        // Reveal cell
        int prevRevealed = revealedSafe;
        revealcell(R,C);

        // Count revealed safe cells
        revealedSafe = 0;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(revealed[i][j] && board[i][j]!='*') revealedSafe++;
            }
        }

        if(revealedSafe == safeCells){
            displayboard();
            cout<<"🎉 Congratulations! You revealed all safe cells!"<<endl;
            saveScore(playerName, levelName, "Win");
            break;
        }
    }
}

// ================== MAIN ==================
int main (){
    srand(time(0));
    int choice;

    while(true){
        cout << "\n===== MAIN MENU =====\n";
        cout << "1- Instructions\n2- Start Game\n3- View Scores\n4- Exit\n";
        cin >> choice;

        if(choice==1){
            instructions();
        }
        else if(choice==2){
            string playerName;
            cout << "Enter your name: ";
            cin >> playerName;

            cout << "Select Level:\n";
            cout << "1- Easy (8x8, 10 mines)\n2- Medium (10x10, 20 mines)\n3- Hard (12x12, 30 mines)\n";
            int levchoice;
            cin >> levchoice;
            string levelName;
            if(levchoice==1){ r=8;c=8;m=10; levelName="Easy"; }
            else if(levchoice==2){ r=10;c=10;m=20; levelName="Medium"; }
            else if(levchoice==3){ r=12;c=12;m=30; levelName="Hard"; }
            else{ cout<<"Invalid level! Defaulting to Easy.\n"; r=8;c=8;m=10; levelName="Easy"; }

            inigame();
            placemines();
            calcualate_mines();
            gameloop(playerName, levelName);
        }
        else if(choice==3){
            viewScores();
        }
        else if(choice==4){
            cout<<"Exiting the game. Goodbye!"<<endl;
            break;
        }
        else{
            cout<<"Invalid choice! Try again."<<endl;
        }
    }

    return 0;
}
