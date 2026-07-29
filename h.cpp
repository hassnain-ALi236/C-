#include <iostream>
#include<fstream>
#include <cmath>
using namespace std;

int totalStudents = 0;
string reg_username;
string reg_password;
string stdName[100], guardianName[100], idCard[100];
int stdAge[100], registrationNo[100], matricmarks[100], intermarks[100];
double meritcalculation[100], finalAggregate[100];
char section[100];

void header();
void menu();
void update_student();
void deletestudent();
void addstudent();
void viewstudent();
void login();
void sign_up();
void meritcal();
void loadfromfile();
void saveToFile();

int main() {
    int choice = 0; 
    loadfromfile();
    sign_up();
    while (choice != -1) {
        menu();
        cin >> choice;
        if (choice == 1) {
            login();
        }
        else if (choice == 2) {
            header();
        }
        else if (choice == 3) {
            addstudent();
            saveToFile();
        }
        else if (choice == 4) {
            viewstudent();
        }
        else if (choice == 5) {
            meritcal();
        }
        else if (choice == 6) {
            update_student();
            saveToFile();
        }
        else if (choice == 7) {
            deletestudent();
            saveToFile();
        }
        else if (choice == -1) {
            cout << "\n*** Program Terminated Successfully ***\n";
            break;
        }
        else {
            cout << "\n*** Invalid Choice! Try Again ***\n";  
        }
    }
    return 0;
}

void header() {
    cout << "\n";
    cout << "    ====================================== " << endl;	
    cout << "    ||  UU  UU  AAAA  MM MM  SSSSS     || " << endl;
    cout << "    ||  UU  UU  A  A  MMMMM  SS         || " << endl;
    cout << "    ||  UU  UU  AAAA  MMMMM  SSSSS      || " << endl;
    cout << "    ||  UU  UU  A  A  MM MM     SS      || " << endl;
    cout << "    ||   UUUU   A  A  MM MM  SSSSS      || " << endl;
    cout << "    ====================================== " << endl;
    cout << "\n";
}

void login() {
    string username, pass;
    cin.ignore(); 
    cout << "\n---------- LOGIN PANEL ----------\n";
    cout << "Enter Username: ";
    getline(cin, username);
    cout << "Enter Password: ";
    cin >> pass;
    if (reg_username == username && reg_password == pass) {  
        cout << "\n*** Login Successful! Welcome Back ***\n";
    }
    else {
        cout << "\n*** Incorrect Credentials! Try Again ***\n";
    }
}

void sign_up() {
    string first_name, last_name, user_name, email, password;
    cout << "\n========== REGISTRATION FORM ==========\n";
    cout << "First Name: ";
    cin >> first_name;
    cout << "Last Name: ";
    cin >> last_name;
    cin.ignore(); 
    cout << "Username: ";
    getline(cin, user_name);
    cout << "Password: ";
    cin >> password;
    reg_username = user_name;
    reg_password = password;
    cout << "\n*** REGISTRATION SUCCESSFUL ***\n\n";
}

void addstudent() {
    cout << "\n========== ADD NEW STUDENT ==========\n";
    cout << "Student Name: ";
    cin >> stdName[totalStudents];
    cout << "Guardian Name: ";
    cin >> guardianName[totalStudents];
    cin.ignore();
    cout << "Registration Number: ";
    cin >> registrationNo[totalStudents];
    cout << "Section: ";
    cin >> section[totalStudents];   
    cout << "ID Card Number: ";
    cin >> idCard[totalStudents];
    cout << "Age: ";
    cin >> stdAge[totalStudents];
    cout << "Matric Marks (out of 1100): ";
    cin >> matricmarks[totalStudents];
    cout << "Inter Marks (out of 1200): ";
    cin >> intermarks[totalStudents];

    totalStudents++;
    cout << "\n*** Student Added Successfully ***\n";
}

void meritcal() {
    if(totalStudents == 0){
       cout << "\n*** NO STUDENT RECORD FOUND! ADD STUDENTS FIRST ***\n";
       return;
    }
    
    cout << "\n========== AGGREGATE CALCULATION ==========\n";
    for(int i = 0; i < totalStudents; i++){
        meritcalculation[i] = ((matricmarks[i] / 1100.0) * 30) + 
                              ((intermarks[i] / 1200.0) * 70);
        
        finalAggregate[i] = meritcalculation[i];
        
        cout << "\n>> Student " << i+1 << ": " << stdName[i] << endl;
        cout << "   Final Aggregate: " << finalAggregate[i] << "%\n";
    }
}

void viewstudent() {
    if (totalStudents == 0) {
        cout << "\n*** No Student Record Available ***\n";
        return;
    }
    cout << "\n========== STUDENT RECORDS ==========\n";
    for (int i = 0; i < totalStudents; i++) {
        cout << "\n---------------------------------\n";
        cout << "   STUDENT #" << i + 1 << endl;
        cout << "---------------------------------\n";
        cout << "Name: " << stdName[i] << endl;
        cout << "Guardian: " << guardianName[i] << endl;
        cout << "Reg No: " << registrationNo[i] << endl;
        cout << "Section: " << section[i] << endl;
        cout << "ID Card: " << idCard[i] << endl;
        cout << "Age: " << stdAge[i] << " years" << endl;
        cout << "Matric Marks: " << matricmarks[i] << "/1100" << endl;
        cout << "Inter Marks: " << intermarks[i] << "/1200" << endl;
        cout << "Aggregate: " << finalAggregate[i] << "%" << endl;
    }
}

void update_student() {
    if (totalStudents == 0) {
        cout << "\n*** No Student Record Available ***\n";
        return;
    }
    int searchRollNo;
    cout << "\n========== UPDATE STUDENT RECORD ==========\n";
    cout << "Enter Registration No to Update: ";
    cin >> searchRollNo;
    int index = -1;
    for (int i = 0; i < totalStudents; i++) {
        if (registrationNo[i] == searchRollNo) {
            index = i;
            break;
        }
    }
    if (index == -1) {      
        cout << "\n*** Student Not Found ***\n";
        return;
    }
    
    cout << "\n--- CURRENT INFORMATION ---\n";
    cout << "Name: " << stdName[index] << endl;
    cout << "Guardian: " << guardianName[index] << endl;
    cout << "Reg No: " << registrationNo[index] << endl;
    cout << "Section: " << section[index] << endl;
    cout << "ID Card: " << idCard[index] << endl;
    cout << "Age: " << stdAge[index] << endl;
    cout << "Matric Marks: " << matricmarks[index] << endl;
    cout << "Inter Marks: " << intermarks[index] << endl;

    cout << "\n--- ENTER NEW INFORMATION ---\n";
    cout << "New Name: ";
    cin >> stdName[index];
    cout << "New Guardian: ";
    cin >> guardianName[index];
    cout << "New Reg No: ";
    cin >> registrationNo[index];
    cout << "New Section: ";
    cin >> section[index];
    cin.ignore();
    cout << "New ID Card: ";
    cin >> idCard[index];
    cout << "New Age: ";
    cin >> stdAge[index];
    cout << "New Matric Marks: ";
    cin >> matricmarks[index];
    cout << "New Inter Marks: ";
    cin >> intermarks[index];
    
    meritcalculation[index] = ((matricmarks[index] / 1100.0) * 30) +
                              ((intermarks[index] / 1200.0) * 70);
    finalAggregate[index] = meritcalculation[index];
    
    cout << "\n*** Record Updated Successfully ***\n";
    cout << "Updated Aggregate: " << finalAggregate[index] << "%\n";
}

void deletestudent() {
    int dellrollno, index = -1;
    cout << "\n========== DELETE STUDENT RECORD ==========\n";
    cout << "Enter Registration No to Delete: ";
    cin >> dellrollno;
    for (int i = 0; i < totalStudents; i++) {
        if (registrationNo[i] == dellrollno) {
            index = i;
            break;
        }
    }
    if (index == -1) {    
        cout << "\n*** Student Not Found ***\n";
        return;
    }
    for (int i = index; i < totalStudents - 1; i++) {
        stdName[i] = stdName[i + 1];
        guardianName[i] = guardianName[i + 1];
        idCard[i] = idCard[i + 1];
        stdAge[i] = stdAge[i + 1];
        registrationNo[i] = registrationNo[i + 1];
        section[i] = section[i + 1];
        matricmarks[i] = matricmarks[i + 1];
        intermarks[i] = intermarks[i + 1];
        finalAggregate[i] = finalAggregate[i + 1];
    }
    totalStudents--;
    cout << "\n*** Student Record Deleted Successfully ***\n";
}

void menu() {
    cout << "\n======================================\n";
    cout << "       STUDENT MANAGEMENT MENU       \n";
    cout << "======================================\n";
    cout << " [1] Login Account\n";
    cout << " [2] Display Header\n";
    cout << " [3] Add New Student\n";
    cout << " [4] View All Students\n";
    cout << " [5] Calculate Aggregate\n";
    cout << " [6] Update Student Info\n";
    cout << " [7] Delete Student Record\n";
    cout << " [-1] Exit Program\n";
    cout << "======================================\n";
    cout << "Enter Your Choice: ";
}

void saveToFile() {
    ofstream file("student_data.txt");
    if (!file) {
        cout << "\n*** File Error! Unable to Save ***\n";
        return;
    }
    
    file << totalStudents << endl;
    for (int i = 0; i < totalStudents; i++) {
        file << stdName[i] << endl;
        file << guardianName[i] << endl;
        file << registrationNo[i] << endl;
        file << section[i] << endl;
        file << idCard[i] << endl;
        file << stdAge[i] << endl;
        file << matricmarks[i] << endl;
        file << intermarks[i] << endl;
        file << finalAggregate[i] << endl;
    }
    file.close();
    cout << "\n*** Data Saved to File Successfully ***\n";
}

void loadfromfile(){
    ifstream file("student_data.txt");
    if (!file) {
        cout << "\n*** No Previous Data File Found ***\n";
        return;
    }
    
    file >> totalStudents;
    file.ignore();
    for (int i = 0; i < totalStudents; i++) {
        getline(file, stdName[i]);
        getline(file, guardianName[i]);
        file >> registrationNo[i];
        file >> section[i];
        file.ignore();
        getline(file, idCard[i]);
        file >> stdAge[i];
        file >> matricmarks[i];
        file >> intermarks[i];
        file >> finalAggregate[i];
        file.ignore();
    }
    file.close();
    cout << "\n*** Previous Data Loaded Successfully ***\n";
}