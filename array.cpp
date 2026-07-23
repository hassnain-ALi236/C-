/*#include <iostream>
using namespace std;
int main() {
   int a =10;
    int *b= &a;
   cout <<b;
    return 0;
}*/
/*
#include <iostream>
using namespace std;
int main(){
    int n;
int nmbr[]={5, 7, 9, 11, 15, 4};
for (int i=0; i<6; i++){
    n=nmbr[i];
    bool isPrime=true;
    for(int j=2; j<=n/2; j++){
        if(n%j==0){
            isPrime=false;
            break;
        }
    }
    int sum=0;
    if(isPrime && n>1){
        
        cout << "===================================" << endl;
                 cout<<n<<" is a prime number"<<endl;
        cout << "===================================" << endl;
        sum+=n;
    }
    
}

     
return 0;

}*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
 const int grid_size=3;
 char board[grid_size][grid_size]={{'o','o','X'},{'o','o','X'},{'X','X','o'}};
bool checkrows(char symbol){
    int count=0;
    for ( int rows=0; rows<grid_size; rows++){
        count=0;
        for(int cols=0; cols<grid_size; cols++){
            if(board[rows][cols]==symbol){
                count++;
            }
        }
        if(count==grid_size){
            return true;
        }
    }
    return false;
}
bool checkcolumns(char symbol){
    int count=0;
    for ( int cols=0; cols<grid_size; cols++){
        count=0;
        for(int rows=0; rows<grid_size; rows++){
            if(board[rows][cols]==symbol){
                count++;
            }
        }
        if(count==grid_size){
            return true;
        }
    }
    return false;
}
bool checkdiagonals(char symbol){
    int count=0;
    for (int i=0; i<grid_size; i++){
        if(board[i][i]==symbol){
            count++;
        }
    }
    if(count==grid_size){
        return true;
    }
    count=0;
    for (int i=0; i<grid_size; i++){
        if(board[i][grid_size-1-i]==symbol){
            count++;
        }
    }
    if(count==grid_size){
        return true;
    }
    return false;
}
bool iswin(char symbol){
 
 
    return checkrows(symbol) || checkcolumns(symbol) || checkdiagonals(symbol);
}
int main(){
checkrows('X');
checkcolumns('X');
checkdiagonals('X');
if(iswin('X')){
    cout << "X WINS" << endl;
}
   
    
    return 0;
}