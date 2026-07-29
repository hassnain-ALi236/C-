#include <iostream>
#include<string>
using namespace std;
int studentCount = 0;
int i=0;
string login_email;
string student_name[100];
string cnic[100];
int matricmarks[100];
int intermediatemarks[100];
char A[100];
float aggregate[100];
int roll_no[100];
string password;
void Header();
void Menu();
void viewStudent();
int main() {
    Header(); 
    cout<<"Enter your Email to login"<<endl;
    cin>>login_email;
    cin.ignore();
    cout<<"Enter your password"<<endl;
    cin>>password;
    int choice;
    cout << "Enter your choice\n";
    cout << "Enter 1 for add student\n";
    cout << "Enter 2 for view student\n";
    cout << "Enter -1 for exit\n";
    cin >> choice;
    while(choice!=-1)
    {
        if(choice==1){
            Menu();
        }
        if(choice==2){
            viewStudent();
        }
    cout << "Enter your choice\n";
    cout << "Enter 1 for add student\n";
    cout << "Enter 2 for view student\n";
    cout << "Enter -1 for exit\n";
    cin >> choice;
    }
    return 0;
}
void viewStudent() {
    for (i = 0; i < studentCount; i++){
        cout<<"***********************************"<<endl;
        cout<<"          Student #"<<i+1 << " Details " <<endl;
        cout<<"**********************************"<<endl;
    cout << "Student name  =" << student_name[i]<<endl;
    cout << "Roll number   =" << roll_no[i]<<endl;
    cout << "section       =" << A[i] << endl;
    cout << "Inter Marks   =" << intermediatemarks[i] << endl;
    cout << "Matric Marks  =" << matricmarks[i] << endl;
    cout << "Uni Aggregate =" << aggregate[i] << endl;
}
}
void Header() {
    cout << "    ************************************** " << endl;
    cout << "    *   U    U   AAAAA  M     M   SSSSS  * " << endl;
    cout << "    *   U    U   A   A  MM   MM   S      * " << endl;
    cout << "    *   U    U   AAAAA  M  M  M   SSSSS  * " << endl;
    cout << "    *   U    U   A   A  M     M       S  * " << endl;
    cout << "    *     UUU    A   A  M     M   SSSSS  * " << endl;
    cout << "    ************************************** " << endl;            
    cout << endl;
}

void Menu() {
    
    cout << "1- Add Students" << endl;
    cout << "ADD student details "<<endl;
    cout <<"^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
    cin.ignore();
    cout <<"Enter  student name"<<endl;
    getline (cin, student_name[studentCount]);
    string Father_name;
    cout<<"Enter Father name"<<endl;
    getline (cin, Father_name);
    cout<<"Enter your cnic"<<endl;
    cin>>cnic[studentCount];
    cout<<" Enter Your roll no"<<endl;
    cin>>roll_no[studentCount];
     cout<<" Select your Section"<<endl;
    cin>>A[studentCount];
    cout<<"Enter your matric marks"<<endl;
    cin>>matricmarks[studentCount];
    cout<<"Enter your FSC marks"<<endl;
    cin>>intermediatemarks[studentCount];
    cout<<" Enter your uni aggregate"<<endl;
    cin>>aggregate[studentCount];
    studentCount++;
    cout << "2- Delete Students" << endl;
    cout << "3- Upload Record" << endl;
    cout << "4- View Students Record" << endl;
    cout << "5- Merit Calculate" << endl;
    cout << "6- Exit" << endl;
    cout << "Choose your option from the above"<<endl;
}