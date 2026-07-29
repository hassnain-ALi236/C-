/*
#include <iostream>
#include <fstream>
using namespace std;
string Username, Password;
void savedata();
void loaddata();
bool logincheck(string user, string pass);

void signup(){
    string use,pass;
    cout << " +++++++++++++++++++++++++++++++++\n";
    cout << " |        SIGN UP PAGE           |\n";
    cout << " +++++++++++++++++++++++++++++++++\n";
    cout << " Enter Username: ";
    cin >> use;
    cout << " Enter Password: ";
    cin >> pass;
    Username=use;
    Password=pass;
}
void login(){
    cout << "======================================\n";
    cout << " |         LOGIN PAGE            |\n";
    cout << "======================================\n";
    string user,pass;
    cout << " Enter Username: ";
    cin >> user;
    cout << " Enter Password: ";
    cin >> pass;
    if(user==Username && pass==Password){
        cout << "Login Successful!\n";
    }else{
        cout << "Invalid Username or Password.\n";
    }
    logincheck(user,pass);
    if(logincheck(user,pass)){
        cout << "Login Successful from file data!\n";
}

else{
    cout << "Invalid Username or Password from file data!\n";
}
}
int main() {
    int choice=0;
        loaddata();
        while(choice!= 3){
    cout << " +++++++++++++++++++++++++++++++++\n";
    cout << " |   WELCOME TO THE SYSTEM       |\n";
    cout << " +++++++++++++++++++++++++++++++++\n";
    cout << " 1. Sign Up\n";
    cout << " 2. Login\n";
    cout << " 3. Exit\n";
    cout << " Enter your choice: ";
    cin >> choice;
 if(choice==1){
     signup();
     savedata();
    }
    else if(choice==2){
        login();
        savedata();
    }
    else if(choice==3){
        cout << "Exiting the system. Goodbye!\n";
    
    }else{
        cout << "Invalid choice. Please try again.\n";
    }
       
}
return 0;
}

void savedata(){
    ofstream file("data.txt",ios::app);
    if(file.is_open()){
        file << Username << endl;
        file << Password << endl;
        file.close();
        cout << "Data Saved Successfully.\n";
    }else{
        cout << "Error opening file.\n";
    }

}
void loaddata(){
    ifstream file("data.txt");
    if(file.is_open()){
        getline(file, Username);
        getline(file, Password);
        file.close();
        cout << "Data Loaded Successfully.\n";
    }else{
        cout << "Error opening file.\n";
    }
}
bool logincheck(string user, string pass){
    ifstream file("data.txt");
    string fileUser, filePass;
    if(file.is_open()){
        while(getline(file, fileUser) && getline(file, filePass)){
            if(fileUser==user && filePass==pass){
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}*/

#include <iostream>
using namespace std;

char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char current = 'X';

void display() {
    cout << "\n";
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool checkWin() {
    // Check rows and columns
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    // Check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    return false;
}

int main() {
    int choice, row, col;
    
    for(int turn = 0; turn < 9; turn++) {
        display();
        cout << "Player " << current << ", enter position (1-9): ";
        cin >> choice;
        
        row = (choice - 1) / 3;
        col = (choice - 1) % 3;
        
        if(choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Invalid move!\n";
            turn--;
            continue;
        }
        
        board[row][col] = current;
        
        if(checkWin()) {
            display();
            cout << "Player " << current << " wins!\n";
            return 0;
        }
        
        current = (current == 'X') ? 'O' : 'X';
    }
    
    display();
    cout << "It's a draw!\n";
    return 0;
}
/*
```

---

## **Complete Output (with improvements):**
```
Board:
o o X 
o o X 
X X o 

X WINS*/