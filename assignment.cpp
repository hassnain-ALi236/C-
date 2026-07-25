#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int studentcount = 0;
string reg_username, reg_password;
string name[100], fathername[100], cnic[100];
int age[100], rollno[100], matricmarks[100], intermarks[100];
double meritcalculation[100], aggregate[100];
char a[100];
string loggedInRole = "";

const string ADMIN_USERNAME = "developer";
const string ADMIN_PASSWORD = "Hassnain";

void header();
void menu();
void update_student();
void deletestudent();
void addstudent();
void viewstudent();
bool login();
void sign_up();                                  //function declaration
void meritcal();
void loadfromfile();
void saveToFile();
void adminMenu();
void userMenu();
bool checkUserExists(string username);
void saveUserToFile(string username, string password);
bool verifyUserCredentials(string username, string password);

int main() {
    int choice = 0;
    loadfromfile();
    bool loggedIn = false;
    
    while (choice != -1) {
        if (!loggedIn) {
            cout << "1. Login\n";
            cout << "2. Signup\n";
            cout << "-1. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            if (choice == 1) {
                loggedIn = login();
            }
            else if (choice == 2) {
                sign_up();
            }
            else if (choice == -1) {
                break;
            }
            continue;
        }
        
        if (loggedInRole == "admin") {
            adminMenu();
        } else {
            userMenu();
        }
        cin >> choice;
        
        if (loggedInRole == "admin") {
            if (choice == 1) {
                header();
            }
            else if (choice == 2) {
                addstudent();
                saveToFile();
            }
            else if (choice == 3) {
                viewstudent();
            }
            else if (choice == 4) {
                update_student();
                saveToFile();
            }
            else if (choice == 5) {
                deletestudent();
                saveToFile();
            }
            else if (choice == 6) {
                loggedIn = false;
                loggedInRole = "";
                cout << "Logged out successfully!\n";
            }
            else if (choice == -1) {
                break;
            }
            else {
                cout << "Invalid Choice\n";
            }
        }
        else if (loggedInRole == "user") {
            if (choice == 1) {
                header();
            }
            else if (choice == 2) {
                addstudent();
                saveToFile();
            }
            else if (choice == 3) {
                viewstudent();
            }
            else if (choice == 4) {
                meritcal();
            }
            else if (choice == 5) {
                loggedIn = false;
                loggedInRole = "";
                cout << "Logged out successfully!\n";
            }
            else if (choice == -1) {
                break;
            }
            else {
                cout << "Invalid Choice\n";
            }
        }
    }
    return 0;
}

void header() {                                             //header defination
    cout << "    ************************************** " << endl;
    cout << "    *   U    U   AAAAA  M     M   SSSSS  * " << endl;
    cout << "    *   U    U   A   A  MM   MM   S      * " << endl;
    cout << "    *   U    U   AAAAA  M  M  M   SSSSS  * " << endl;
    cout << "    *   U    U   A   A  M     M       S  * " << endl;
    cout << "    *     UUU    A   A  M     M   SSSSS  * " << endl;
    cout << "    ************************************** " << endl;
}

void adminMenu() {
    cout << "\n========= ADMIN MENU =========\n";                    //menuadmin defination
    cout << "1. Header\n";
    cout << "2. Add Student\n";
    cout << "3. View Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Logout\n";
    cout << "-1. Exit\n";
    cout << "Enter your choice: ";
}

void userMenu() {                                                  //menuuser defination
    cout << "\n========= USER MENU =========\n";
    cout << "1. Header\n";
    cout << "2. Add Student\n";
    cout << "3. View Student\n";
    cout << "4. Merit Calculate\n";
    cout << "5. Logout\n";
    cout << "-1. Exit\n";
    cout << "Enter your choice: ";
}

bool checkUserExists(string username) {
    ifstream file("first.txt");
    string line, fileUser;
    if (file.is_open()) {
        while (getline(file, line)) {
            int commaPos = line.find(',');
            if (commaPos != string::npos) {
                fileUser = line.substr(0, commaPos);
                if (fileUser == username) {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
    }
    return false;
}

void saveUserToFile(string username, string password) {
    ofstream file("first.txt", ios::app);
    if (file.is_open()) {
        file << username << "," << password << endl;
        file.close();
    }
}

bool verifyUserCredentials(string username, string password) {
    ifstream file("first.txt");
    string line, fileUser, filePass;
    if (file.is_open()) {
        while (getline(file, line)) {
            int commaPos = line.find(',');
            if (commaPos != string::npos) {
                fileUser = line.substr(0, commaPos);
                filePass = line.substr(commaPos + 1);
                if (fileUser == username && filePass == password) {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
    }
    return false;
}

bool login() {                                         //login defination
    string username, pass;
    int roleChoice;
    cout << "Select Role:\n";    
    cout << "1. Admin\n";
    cout << "2. User\n";
    cout << "Enter choice: ";
    cin >> roleChoice;
    cin.ignore();
    cout << "Enter your Username: ";
    getline(cin, username);
    cout << "Enter your Password: ";
    cin >> pass;
    
    if (roleChoice == 1) {
        if (username == ADMIN_USERNAME && pass == ADMIN_PASSWORD) {
            loggedInRole = "admin";
            cout << "Admin Login Successful\n";
            return true;
        } else {
            cout << "Invalid admin credentials\n";
            return false;
        }
    }
    else if (roleChoice == 2) {
        if (verifyUserCredentials(username, pass)) {
            loggedInRole = "user";
            cout << "User Login Successful\n";
            return true;
        } else {
            cout << "Invalid credentials\n";
            return false;
        }
    }
    return false;
}

void sign_up() {
    cout << "SIGN UP\n";
    string first_name, last_name, user_name, password;
    cout << "Enter your First name: ";
    cin >> first_name;
    cout << "Enter your Last name: ";
    cin >> last_name;
    cin.ignore();
    cout << "Username: ";
    getline(cin, user_name);
    
    if (checkUserExists(user_name)) {
        cout << "Username already exists!\n";                 //checkuser
        return;
    }
    
    cout << "Choose your Password: ";
    cin >> password;
    saveUserToFile(user_name, password);
    cout << "SIGN UP SUCCESSFULL\n";
}

void addstudent() {
    cout << "Enter your name: ";
    cin >> name[studentcount];
    cout << "Enter your Father name: ";
    cin >> fathername[studentcount];
    cin.ignore();
    cout << "Enter your Roll No: ";
    cin >> rollno[studentcount];             //entering data
    cout << "Enter your Section: ";
    cin >> a[studentcount];
    cout << "Enter your CNIC: ";
    cin >> cnic[studentcount];
    cout << "Enter your Age: ";
    cin >> age[studentcount];
    cout << "Enter your Matric Marks: ";
    cin >> matricmarks[studentcount];
    cout << "Enter your Inter Marks: ";
    cin >> intermarks[studentcount];
    studentcount++;
    cout << "===============================================" << endl;
    cout << "        STUDENT ADDED SUCCESSFULLY" << endl;
    cout << "===============================================" << endl;
}

void meritcal() {
    if (studentcount == 0) {
        cout << "NO STUDENT FOUND! FIRST ADD STUDENT\n";          //meritcalculation
        return;
    }
    for (int i = 0; i < studentcount; i++) {
        meritcalculation[i] = ((matricmarks[i] / 1100.0) * 30) +
                              ((intermarks[i] / 1200.0) * 70);
        aggregate[i] = meritcalculation[i];
        cout << "\nStudent " << i + 1 << " (" << name[i] << ")" << endl;
        cout << "Aggregate: " << aggregate[i] << "%" << endl;
    }
}

void viewstudent() {
    if (studentcount == 0) {
        cout << "No Student Found\n";
        return;
    }
    for (int i = 0; i < studentcount; i++) {
        cout << "*****************************" << endl;
        cout << "Student Number " << i + 1 << endl;
        cout << "*****************************" << endl;
        cout << "Name: " << name[i] << endl;
        cout << "Father Name: " << fathername[i] << endl;
        cout << "Roll No: " << rollno[i] << endl;         //viewstd
        cout << "Section: " << a[i] << endl;
        cout << "CNIC: " << cnic[i] << endl;
        cout << "Age: " << age[i] << endl;
        cout << "Matric Marks: " << matricmarks[i] << endl;
        cout << "Intermediate Marks: " << intermarks[i] << endl;
        cout << "Aggregate: " << aggregate[i] << endl;
    }
}

void update_student() {
    if (studentcount == 0) {
        cout << "No Student Found\n";
        return;
    }
    int searchRollNo;
    cout << "Enter Roll No. to update data: ";
    cin >> searchRollNo;
    int index = -1;
    for (int i = 0; i < studentcount; i++) {
        if (rollno[i] == searchRollNo) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "No Student Found\n";
        return;
    }
    cout << "CURRENT DETAILS\n";
    viewstudent();
    cout << "\n UPDATE DETAILS \n";
    cout << "Name: " << name[index] << endl;
    cin >> name[index];
    cout << "Father Name: " << fathername[index] << endl;
    cin >> fathername[index];
    cout << "Roll No: " << rollno[index] << endl;
    cin >> rollno[index];
    cout << "Section: " << a[index] << endl;       //update and save std//
    cin >> a[index];
    cin.ignore();
    cout << "CNIC: " << cnic[index] << endl;
    cin >> cnic[index];
    cout << "Age: " << age[index] << endl;
    cin >> age[index];
    cout << "Matric Marks: " << matricmarks[index] << endl;
    cin >> matricmarks[index];
    cout << "Intermediate Marks: " << intermarks[index] << endl;
    cin >> intermarks[index];
    meritcalculation[index] = ((matricmarks[index] / 1100.0) * 30) +
                              ((intermarks[index] / 1200.0) * 70);
    aggregate[index] = meritcalculation[index];
    cout << "Aggregate: " << aggregate[index] << endl;
    cout << " =============================================== " << endl;
    cout << "    STUDENT DETAILS UPDATED SUCCESSFULLY " << endl;
    cout << " =============================================== " << endl;
}

void deletestudent() {
    int dellrollno, index = -1;
    cout << "Enter Roll No to delete student: ";
    cin >> dellrollno;
    for (int i = 0; i < studentcount; i++) {
        if (rollno[i] == dellrollno) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "No Student Found\n";     //for no std
        return;
    }
    for (int i = index; i < studentcount - 1; i++) {
        name[i] = name[i + 1];
        fathername[i] = fathername[i + 1];
        cnic[i] = cnic[i + 1];
        age[i] = age[i + 1];
        rollno[i] = rollno[i + 1];
        a[i] = a[i + 1];
        matricmarks[i] = matricmarks[i + 1];
        intermarks[i] = intermarks[i + 1];
        aggregate[i] = aggregate[i + 1];
    }
    studentcount--;
    cout << " *******************************************" << endl;
    cout << " STUDENT DELETED SUCCESSFULLY" << endl;
    cout << " *******************************************" << endl;
}
   //file handling
void saveToFile() {
    ofstream file("first.txt");
    if (!file) {
        cout << "File error!\n";
        return;
    }
    file << studentcount << endl;
    for (int i = 0; i < studentcount; i++) {
        file << name[i] << endl;
        file << fathername[i] << endl;
        file << rollno[i] << endl;
        file << a[i] << endl;
        file << cnic[i] << endl;
        file << age[i] << endl;
        file << matricmarks[i] << endl;
        file << intermarks[i] << endl;
        file << aggregate[i] << endl;
    }
    file.close();
    cout << "Data saved successfully!\n";
}

void loadfromfile() {
    ifstream file("first.txt", ios::in);
    if (!file) {
        cout << "No previous data found.\n";
        return;
    }
    file >> studentcount;
    file.ignore();
    for (int i = 0; i < studentcount; i++) {
        getline(file, name[i]);
        getline(file, fathername[i]);
        file >> rollno[i];
        file >> a[i];
        file.ignore();
        getline(file, cnic[i]);
        file >> age[i];
        file >> matricmarks[i];
        file >> intermarks[i];
        file >> aggregate[i];
        file.ignore();
    }
    file.close();
    cout << "Data loaded successfully!\n";
}