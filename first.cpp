#include <iostream>
#include <string>
using namespace std;
    string name;
    double cnic;
    string address;
    float matricmarks;
    float intermarks;
void addStudent() {
    cin.ignore();
    cout << "Enter Student name :";
    getline(cin, name);
    cout << "Enter Student CNIC: ";
    cin>>cnic;
    cin.ignore();
    cout << "Enter Student Address: ";
    getline(cin, address);
    cout << "Enter Student Matric Marks: ";
    cin >> matricmarks;
    cout << "Enter Student Inter Marks: ";
    cin >> intermarks;
}
void viewStudent() {
cout<<name<<"\t"<<cnic<<"\t"<<address<<"\t"<<matricmarks<<"\t"<<intermarks<<"\t";}
void menu() {
    cout<<"MENU :"<<endl;
    cout<<"1. Add student name :"<<endl;
    cout<<"2. Delete student name :"<<endl;
    cout<<"3. Update record :"<<endl;
    cout<<"4. View Student Record :"<<endl;
    cout<<"5. Merit Calculator :"<<endl;
    cout<<"6. Exit :"<<endl;
}
void header() {
cout<<"        **************************************************************************************************"<<endl;
cout<<"        **          $$    $$         $$          $$           $$       $$$$$$$$$$$$$$                   **"<<endl;
cout<<"        **          $$    $$        $$ $$        $$ $$     $$ $$       $$                               **"<<endl;
cout<<"        **          $$    $$       $$   $$       $$   $$  $$  $$       $$                               **"<<endl;
cout<<"        **          $$    $$      $$$$$$$$$      $$     $$    $$       $$$$$$$$$$$$$$                   **"<<endl;
cout<<"        **          $$    $$     $$       $$     $$           $$                    $$                  **"<<endl;
cout<<"        **          $$    $$    $$         $$    $$           $$                    $$                  **"<<endl;
cout<<"        **          $$$$$$$$   $$           $$   $$           $$       $$$$$$$$$$$$$$$                  **"<<endl;
cout<<"        *************************************************************************************************"<<endl;
}

int main() {
    header();
    menu();
    int opr1;
    int opr2;
    cout<<"Enter Operation from Menu : ";
    cin>>opr1;
    if (opr1==1)
    { addStudent();
    }
    cin.ignore();
    cout<<"Enter Operation from Menu : ";
    cin>>opr2;
    if (opr2==4) {
        viewStudent();
    }
}