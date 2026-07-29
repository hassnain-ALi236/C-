#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 500;

/* ---------- COLORS ---------- */
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

/* ---------- STUDENT DATA ---------- */
int totalStudents = 0;
string name[MAX], father[MAX], roll[MAX], cnic[MAX], age[MAX], email[MAX];
double fee[MAX];
string feeStatus[MAX]; // "Paid" / "Unpaid"

/* ---------- USER DATA ---------- */
string usernames[100];
string passwords[100];
int totalUsers = 0;

/* ---------- LOGIN ---------- */
string currentUser;

/* ---------- BASIC UI ---------- */
void line() {
    cout << YELLOW << "----------------------------------------\n" << RESET;
}

/* ---------- FILE HANDLING ---------- */
void loadFromFile() {
    ifstream fin("students.txt");
    if (!fin) return;

    totalStudents = 0;
    while (fin >> name[totalStudents]) {
        fin >> father[totalStudents] 
            >> roll[totalStudents]
            >> cnic[totalStudents]
            >> age[totalStudents] 
            >> email[totalStudents] 
            >> fee[totalStudents] 
            >> feeStatus[totalStudents];
        totalStudents++;
    }
    fin.close();
}

void saveToFile() {
    ofstream fout("students.txt");
    for (int i = 0; i < totalStudents; i++) {
        fout << name[i] << " " << father[i] << " " << roll[i] << " " << cnic[i] << " "
            << age[i] << " " << email[i] << " " << fee[i] << " " << feeStatus[i] << endl;
    }
    fout.close();
}

/* ---------- ADMIN FUNCTIONS ---------- */
void addStudent() {
    line();
    cout << CYAN << "ADD STUDENT\n" << RESET;
    line();

    cout << "Name: ";
    cin >> name[totalStudents];
    cout << "Father Name: ";
    cin >> father[totalStudents];
    cout << "Roll No: "; 
    cin >> roll[totalStudents];
    cout << "CNIC: "; 
    cin >> cnic[totalStudents];

    while (true) {
        cout << "Age: ";
        string a; cin >> a;
        bool valid = true;
        for (int i = 0; i < a.length(); i++)
            if (a[i] < '0' || a[i] > '9') valid = false;
        if (valid && a != "") { age[totalStudents] = a; break; }
        else cout << RED << "Invalid input! Enter numbers only.\n" << RESET;
    }

    cout << "Email: "; cin >> email[totalStudents];

    char cat;
    while (true) {
        cout << "Category (A/B): "; cin >> cat;
        if (cat == 'A') { fee[totalStudents] = 110000; break; }
        else if (cat == 'B') { fee[totalStudents] = 147000; break; }
        else cout << RED << "Invalid category! Enter A or B.\n" << RESET;
    }

    feeStatus[totalStudents] = "Unpaid";
    totalStudents++;
    saveToFile();
    cout << GREEN << "Student Added Successfully!\n" << RESET;
}

void viewAllStudents() {
    line();
    cout << CYAN << "ALL STUDENTS\n" << RESET;
    line();
    if (totalStudents == 0) cout << RED << "No Record Found\n" << RESET;
    else {
        for (int i = 0; i < totalStudents; i++) {
            cout << MAGENTA << "Name: " << RESET << name[i] << endl;
            cout << MAGENTA << "Roll: " << RESET << roll[i] << endl;
            cout << MAGENTA << "Fee: " << RESET << fee[i] << endl;
            cout << MAGENTA << "Fee Status: " << RESET << feeStatus[i] << endl;
            line();
        }
    }
}

void updateStudent() {
    string r; cout << "Enter Roll No to Update: "; cin >> r;
    bool found = false;
    for (int i = 0; i < totalStudents; i++) {
        if (roll[i] == r) {
            found = true;
            cout << "New Name: "; cin >> name[i];
            cout << "New Father: "; cin >> father[i];
            cout << "New Email: "; cin >> email[i];
            char cat;
            while (true) {
                cout << "Category (A/B): "; cin >> cat;
                if (cat == 'A') { fee[i] = 110000; break; }
                else if (cat == 'B') { fee[i] = 147000; break; }
                else cout << RED << "Invalid category! Enter A or B.\n" << RESET;
            }
            saveToFile();
            cout << GREEN << "Record Updated!\n" << RESET;
        }
    }
    if (!found) cout << RED << "Student Not Found\n" << RESET;
}

void deleteStudent() {
    string r; cout << "Enter Roll No to Delete: "; cin >> r;
    bool found = false;
    for (int i = 0; i < totalStudents; i++) {
        if (roll[i] == r) {
            found = true;
            for (int j = i; j < totalStudents - 1; j++) {
                name[j] = name[j + 1]; 
                father[j] = father[j + 1];
                roll[j] = roll[j + 1]; 
                cnic[j] = cnic[j + 1];
                age[j] = age[j + 1]; 
                email[j] = email[j + 1];
                fee[j] = fee[j + 1]; 
                feeStatus[j] = feeStatus[j + 1];
            }
            totalStudents--;
            saveToFile();
            cout << GREEN << "Student Deleted!\n" << RESET;
        }
    }
    if (!found) cout << RED << "Student Not Found\n" << RESET;
}

void searchStudent() {
    string r; cout << "Enter Roll No: "; cin >> r;
    bool found = false;
    for (int i = 0; i < totalStudents; i++) {
        if (roll[i] == r) {
            found = true;
            cout << MAGENTA << "Name: " << RESET << name[i] << endl;
            cout << MAGENTA << "Fee: " << RESET << fee[i] << endl;
            cout << MAGENTA << "Fee Status: " << RESET << feeStatus[i] << endl;
        }
    }
    if (!found) cout << RED << "Student Not Found\n" << RESET;
}

void updateFeeStatus() {
    string r; cout << "Enter Roll No: "; cin >> r;
    bool found = false;
    for (int i = 0; i < totalStudents; i++) {
        if (roll[i] == r) {
            found = true;
            while (true) {
                string status; cout << "Enter Fee Status (Paid/Unpaid): "; cin >> status;
                if (status == "Paid" || status == "Unpaid") { feeStatus[i] = status; break; }
                else cout << RED << "Invalid input! Enter Paid or Unpaid.\n" << RESET;
            }
            cout << GREEN << "Fee Status Updated!\n" << RESET;
        }
    }
    if (!found) cout << RED << "Student Not Found\n" << RESET;
}

/* ---------- USER FUNCTIONS ---------- */
void viewMyInfo() 
{ 
    line(); 
    cout << CYAN << "USER INFO\n" << RESET; line(); 
    cout << "Logged in User: " << GREEN << currentUser << RESET << endl;
    line(); }
void viewFeeStructure() 
{ 
    line(); 
    cout << CYAN << "FEE STRUCTURE\n" << RESET; line(); 
    cout << "Category A Fee: " << GREEN << "110000\n" << RESET; 
    cout << "Category B Fee: " << GREEN << "147000\n" << RESET; 
    line();
}
void changePassword()
{
    string oldP, newP; 
    cout << "Old Password: "; 
    cin >> oldP; line(); 
    bool found = false; 
    for (int i = 0; i < totalUsers; i++) 
    { 
        if (usernames[i] == currentUser && passwords[i] == oldP) 
        { 
            found = true;
            cout << "New Password: ";
            cin >> newP; passwords[i] = newP;
            cout << GREEN << "Password Updated\n" << RESET; 
        } 
    } 
    if (!found) cout << RED << "Wrong Password\n" << RESET; 
    line(); 
}
void viewOwnRecord() 
{
    string r; 
    cout << "Enter Your Roll No: "; 
    cin >> r; line();
    bool found = false;
    for (int i = 0; i < totalStudents; i++) 
    { 
        if (roll[i] == r) 
        {
            found = true; cout << "Name: " << name[i] << endl << "Father: " << father[i] << endl << "Roll: " << roll[i] << endl << "CNIC: " << cnic[i] << endl << "Age: " << age[i] << endl << "Email: " << email[i] << endl << "Fee: " << fee[i] << endl << "Fee Status: " << feeStatus[i] << endl;
        } 
    } 
    line();
    if (!found) cout << RED << "Record Not Found\n" << RESET; 
}
void checkFeeStatus() 
{
    string r; 
    cout << "Enter Your Roll No: "; 
    cin >> r; 
    line();
    bool found = false;
    for (int i = 0; i < totalStudents; i++)
    { 
        if (roll[i] == r) 
        {
            found = true; 
            cout << "Fee Status for " << name[i] << ": " << feeStatus[i] << endl;
        } 
    } 
    if (!found) cout << RED << "Record Not Found\n" << RESET; 
    line(); 
}
void updateMyEmail() 
{
    string r;
    cout << "Enter Your Roll No: ";
    cin >> r; line();
    bool found = false; 
    for (int i = 0; i < totalStudents; i++)
    { 
        if (roll[i] == r)
        { found = true; cout << "Enter New Email: "; 
        cin >> email[i]; saveToFile(); 
        cout << GREEN << "Email Updated Successfully\n" << RESET; 
        } 
    }
    if (!found) cout << RED << "Record Not Found\n" << RESET; line();
}

/* ---------- AUTH ---------- */
void signUp() 
{ 
    cout << "Choose Username: "; 
    cin >> usernames[totalUsers]; 
    cout << "Choose Password: "; 
    cin >> passwords[totalUsers]; 
    totalUsers++;
    cout << GREEN << "Signup Successful\n" << RESET;
}
bool userLogin() 
{
    string u, p;
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p; 
    bool found = false;
    for (int i = 0; i < totalUsers; i++)
    {
        if (usernames[i] == u && passwords[i] == p)
        {
            currentUser = u; found = true; 
        }
    }
    if (!found) cout << RED << "Invalid Login(sign up first)\n" << RESET; 
    return found;
}
bool adminLogin() 
{ 
    string u, p;
    cout << "Admin Username: "; 
    cin >> u; cout << "Password: ";
    cin >> p; if (u == "developer" && p == "Hassnain") 
        return true; 
    cout << RED << "Invalid Admin Login\n" << RESET;
    return false; 
}

/* ---------- MENUS ---------- */
void adminMenu() {
    int ch;
    while (true) {
        line(); cout << CYAN << "ADMIN MENU\n" << RESET; line();
        cout << "1. Add Student\n2. Update Student\n3. Delete Student\n4. View Students\n5. Search Student\n6. Update Fee Status\n7. Logout\n";
        cout << "Choice: ";
        while (!(cin >> ch)) 
        {
            cin.clear(); 
            string garbage; 
            cin >> garbage; 
            cout << RED << "Invalid input! Enter number: " << RESET;
        }
        if (ch == 1)
            addStudent(); 
        else if (ch == 2) 
            updateStudent(); 
        else if (ch == 3) 
            deleteStudent();
        else if (ch == 4)
            viewAllStudents();
        else if (ch == 5) 
            searchStudent(); 
        else if (ch == 6)
            updateFeeStatus();
        else if (ch == 7)
            break; 
        else
            cout << RED << "Invalid Choice!\n" << RESET;
    }
}

void userMenu() {
    int ch;
    while (true) {
        line();
        cout << CYAN << "USER MENU\n" << RESET; 
        line();
        cout << "1. View Profile\n2. View Own Record\n3. Fee Structure\n4. Check Fee Status\n5. Update Email\n6. Change Password\n7. Logout\n";
        cout << "Choice: ";
        while (!(cin >> ch)) 
        {
            cin.clear();
            string garbage; 
            cin >> garbage;
            cout << RED << "Invalid input! Enter number: " << RESET; 
        }
        if (ch == 1) 
            viewMyInfo();
        else if (ch == 2) 
            viewOwnRecord();
        else if (ch == 3) 
            viewFeeStructure();
        else if (ch == 4) 
            checkFeeStatus(); 
        else if (ch == 5) 
            updateMyEmail(); 
        else if (ch == 6)
            changePassword();
        else if (ch == 7)
            break; 
        else 
            cout << RED << "Invalid Choice!\n" << RESET;
    }
}

/* ---------- MAIN ---------- */
int main() {
    loadFromFile();
    int choice;
    while (true) {
        line();
        cout << BLUE << "STUDENT MANAGEMENT SYSTEM\n" << RESET;
        line();
        cout << "Developer: " << GREEN << "Hussnain" << RESET << "\n";
        line();
        cout << "1. Admin Login\n2. User Login\n3. Sign Up\n4. Exit\n";
        cout << "Choice: ";
        while (!(cin >> choice)) 
        {
            cin.clear();
            string garbage;
            cin >> garbage;
            cout << RED << "Invalid input! Enter number: " << RESET;
        }
        if (choice == 1) 
        {
            if (adminLogin())
                adminMenu();
        }
        else if (choice == 2)
        {
            if (userLogin())
                userMenu(); 
        }
        else if (choice == 3) 
            signUp();
        else if (choice == 4) 
            break;
        else cout << RED << "Invalid Choice!\n" << RESET;
    }
    cout << BLUE << "Program Ended\n" << RESET;
    return 0;
}