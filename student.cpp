#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int i=0;
string name[500],fathername[500],cnic[500],age[500],rollno[500],emailaddress[500];

string reg_username,reg_password;

void addstudent();
void HEADER();
void viewstudent();
void updatestudent();
void deletestudent();
void viewrecord();
void saverecord();
void welcomescreen();
void sign_up();
bool login();

void addstudent(){
cout<<"ENTER YOUR NAME :";
cin>>name[i];
cout<<"ENTER YOUR FATHER NAME :";
cin>>fathername[i];
cout<<"ENTER YOUR CNIC :";
cin>>cnic[i];
cout<<"ENTER YOUR AGE :";
cin>>age[i];
cout<<"ENTER YOUR ROLL NO :";
cin>>rollno[i];
cin.ignore();
cout<<"ENTER YOUR EMAIL ADDRESS :";
cin>>emailaddress[i];
cout << " " << endl;
cout << " *******************************************"<<endl;
cout<<"    CONGRATS STUDENT ADDED SUCCESSFULLY"<<endl;
cout << " *******************************************"<<endl;
cout<<  " " <<endl;
}
void HEADER(){
    cout << " SIMPLE DESIGN "<<endl;
    cout << " " <<endl;
    cout << "==================================================" << endl;
    cout << "    STUDENT MANAGEMENT SYSTEM " << endl;
    cout << "==================================================" << endl;
    cout << " " <<endl;
}
void welcomescreen(){

    cout<<"############################################################"<<endl;
    cout<<"#                                                           #"<<endl;
    cout<<"#        WELCOME TO STUDENT MANAGEMENT SYSTEM               #"<<endl;
    cout<<"#                                                           #"<<endl;
    cout<<"#            STUDENT MANAGEMENT SYSTEM                      #"<<endl;
    cout<<"#                                                           #"<<endl;
    cout<<"#        * ADD STUDENT                                      #"<<endl;
    cout<<"#        * VIEW STUDENT                                     #"<<endl;
    cout<<"#        * STUDENT FEE CALCULATION                          #"<<endl;
    cout<<"#        * UPDATE STUDENT DATA                              #"<<endl;
    cout<<"#        * DELETE STUDENT DATA                              #"<<endl;
    cout<<"#                                                           #"<<endl;
    cout<<"#        DEVELOPED BY: MIAN HASSNAIN                        #"<<endl;
    cout<<"############################################################"<<endl;
    cout<<"                                        "<<endl;
        }
       
     void viewstudent(){
        
     for(int j=0;j<i;j++){
     if(i==0){
     cout<<"No Student Found"<<endl;
     return;}
     cout<<"*****************************"<<endl;
     cout<<"Student Number "<<j+1<<endl;
     cout<<"*****************************"<<endl;
     cout<<"Name: "<<name[j]<<endl;
     cout<<"Father Name: "<<fathername[j]<<endl;
     cout<<"CNIC: "<<cnic[j]<<endl;
     cout<<"Age: "<<age[j]<<endl;
     cout<<"Roll No: "<<rollno[j]<<endl;
     cout<<"Email Address: "<<emailaddress[j]<<endl;
        }
    cout << " " << endl;
    }

    void stdfee(){
        cin.ignore();

string A1;
string A2;
double a1,a2;
string fee,y,category;
double tution_fee,admission_fee,total_fee;
for(int k=0;k<i;k++){
    cout << " Enter student category (A1/A2):";
   cin>>category;
   if( category=="A1"){
        tution_fee=55000;
    admission_fee=55000;
    cout << " Your tution fee is : " << tution_fee << endl;
    cout << " Your admission fee is : " << admission_fee << endl;
    total_fee=tution_fee+admission_fee;
        cout<<"Your total fee is : "<< total_fee<<endl;
   }
    if(category=="A2"){
        tution_fee=73500;
        admission_fee=73500;
       cout << " Your tution fee is : "  <<  tution_fee << endl;
    cout << " Your admission fee is : "  <<  admission_fee << endl;
        total_fee=tution_fee+admission_fee;
        cout<<"Your total fee is : "<< total_fee <<endl;    }
   }
   cout << " " << endl;
}
void updatestudent(){
if (i==0){
    cout<<"No Student Found"<<endl;
    return;}
string searchRollNo;
cout<<"Enter Roll No. to update data:";
cin>>searchRollNo;
int index=-1;
for ( int j=0;j<i;j++){
    if(rollno[j]==searchRollNo){
        index=j;
        break;
}
}
if( index==-1){
    cout << " NO STUDENT FOUND " << endl;
    return;
}
cout<<"CURRENT DETAILS"<<endl;
viewstudent();
cout<<"\n UPDATE DETAILS \n";
cout<<"Name: " << name[index] << endl;
cin>>name[index];
cin.ignore();
cout<<"Father Name: "<<endl;
cin>>fathername[index];
cout<<"Roll No: " << rollno[index] << endl;
cin>>rollno[index];
cout<<"CNIC: " << cnic[index] << endl;
cin>>cnic[index];
cout<<"Age: " << age[index] << endl;
cin>>age[index];
cout<<"Email Address: " << emailaddress[index] << endl;
cin>>emailaddress[index];
cout << " " <<endl;
cout << " ==============================================="<<endl;
cout << "    STUDENT DETAILS UPDATED SUCCESSFULLY " << endl;
cout << " ===============================================" << endl;
cout << " " <<endl;
}

void deletestudent() {
    string dellrollno;
    int index = -1;
    cout << "Enter Roll No to delete student: ";
    cin >> dellrollno;
    for (int j=0;j<i;  j++) {
        if (rollno[j] == dellrollno) {
            index = j;
            break;
        }
    }
    if (index == -1) {    
        cout << "No Student Found\n";
        return;
    }
    for (int j = index; j < i - 1; j++) {
        name[j] = name[j + 1];
        fathername[j] = fathername[j + 1];
        cnic[j] = cnic[j + 1];
        age[j] = age[j + 1];
        rollno[j] = rollno[j + 1];
        }
        i--;
        cout << " " << endl;
    cout  << " *******************************************"<<endl;
     cout << "        STUDENT DELETED SUCCESSFULLY           "<< endl;  
     cout << " *******************************************"<<endl;
     cout << " " << endl;
}
void saverecord(){
    ofstream fout ( "file.txt", ios::app );
    if (fout.is_open()) {
        for ( int j=0;j<i; j++){
            fout<< name[j]<<endl;
            fout<< fathername[j]<<endl;
            fout<< cnic[j]<<endl;
            fout<< age[j]<<endl;
            fout<< rollno[j]<<endl;
            fout<< emailaddress[j]<<endl;
        }
        fout.close();
    }
    else {
        cout << " No STUDENT DATA SAVE " << endl;
    }
}
void viewrecord(){
    ifstream fin("file.txt");
    if(!fin.is_open()){
        cout << " No STUDENT DATA FOUND " << endl;
        return;
    }
    string line;
    cout << "===================================" << endl;
    cout << "        STUDENT RECORDS (FILE)      " << endl;
    cout << "===================================" << endl;
    while(getline(fin, line)){
        cout << line << endl;
    }
    fin.close();
    cout << "===================================" << endl;
}
void sign_up(){
    cout << " *****************************************"<<endl;
    cout << "        SIGN UP PANEL "<<endl;
    cout << " *****************************************"<<endl;
    cout << " "<<endl;
    string first_name,last_name,user_name,password;
    cout<<"Enter your First name: ";
    cin>>first_name;
    cout<<"Enter your Last name: ";
    cin>>last_name;
    cin.ignore();
    cout<<"Username: ";
    getline(cin,user_name);
    cout<<"Choose your Password: ";
    cin>>password;
    reg_username=user_name;
    reg_password=password;
    cout<<" SIGN UP SUCCESSFULL "<<endl;
    cout<<" "<<endl;
}
bool login(){
    string username,pass;
    cin.ignore();
    cout<<"Enter your Username: ";
    getline(cin,username);
    cout<<"Enter your Password: ";
    cin>>pass;
    if(reg_username==username && reg_password==pass){
        cout<<"Login Successful\n";
        cout<<" "<<endl;
        return true;
    }
    else{
        cout<<"Try Again\n";
        return false;
    }
}


int main(){
    system("cls");
    welcomescreen();
    sign_up();
    bool loggedIn=false;
    int choice=0;
while(choice!= 2)
{
    if(!loggedIn){
        cout<<"1. Login\n";
        cout<<"  2. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice==1){
            loggedIn=login();
        }
        else if(choice==-1){
            break;
        }
        continue;
    }
    cout <<"===================================" << endl;
    cout<<"   Enter your choice from menu :"<<endl;
    cout<<"==================================="<<endl;
    cout << "  " << endl;
    cout <<"1- ADD STUDENT "<<endl;
    cout <<"2- VIEW LOGO " << endl;
    cout <<"3- VIEW RECORDS " << endl;
    cout <<"4- VIEW STUDENT"<<endl;
    cout <<"5- VIEW STUDENT FEE DETAILS"<<endl;
    cout <<"6- UPDATE STUDENT DETAILS"<<endl;
    cout <<"7- DELETE STUDENT"<<endl;
    cout << "  " << endl;
    cout <<"Enter -1 to exit"<<endl;
    if(!(cin>>choice)){
        cin.clear();
        cin.ignore(10000,'\n');
        cout<<" INVALID INPUT , PLEASE ENTER A NUMBER "<<endl;
        continue;
    }
     cout << "  " << endl;
     cout <<"===================================" << endl;
if ( choice ==1 )
    {
        addstudent(); 
        
        i++;
        saverecord();
    }
     else   if ( choice ==2 )
    {
      HEADER();
      continue;
    }
    else if ( choice ==3 )
    {
        viewrecord();
    }
    else if ( choice ==4 )
    {
        viewstudent();
    }
    else if ( choice ==5 )
    {
        stdfee();
    }
    else if ( choice ==6 )
    {
       updatestudent();
       saverecord();
    }
    else if (choice==7)
    {
        deletestudent();
        saverecord();
    }
    else if ( choice == -1 )
    {
        cout << " EXITING PROGRAM " << endl;
    }
    else if (choice==7)
    {
        viewrecord();
    }
    else 
    {
        cin.ignore();
        cout << " INVALID CHOICE , PLEASE TRY AGAIN " << endl;
    
}   
}
    return 0;
}