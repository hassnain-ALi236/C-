#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Global Variables
int totalStudents = 0;
string studentName[100], guardianName[100], nationalID[100];
int studentAge[100], regNumber[100], sscMarks[100], hscMarks[100];
double percentageScore[100];
char studentSection[100];
string currentUser = "";

// Admin Credentials
const string SYSTEM_ADMIN = "huzaifa";
const string SYSTEM_KEY = "123";

// Function Prototypes
void displayBanner();
void showAdminOptions();
void showUserOptions();
void registerStudent();
void displayStudents();
void modifyStudent();
void removeStudent();
bool authenticateUser();
void createAccount();
void saveDatabaseToFile();
void loadDatabaseFromFile();
bool userAlreadyExists(string uname);
void storeUserCredentials(string uname, string upass);
bool validateUserLogin(string uname, string upass);

int main() {
    int userChoice = 0;
    loadDatabaseFromFile();
    bool isAuthenticated = false;
    
    while (userChoice != -1) {
        if (!isAuthenticated) {
            cout << "\n========================================\n";
            cout << "  UNIVERSITY ADMISSION SYSTEM\n";
            cout << "========================================\n";
            cout << "1. Login to System\n";
            cout << "2. Create New Account\n";
            cout << "-1. Exit Application\n";
            cout << "========================================\n";
            cout << "Select Option: ";
            cin >> userChoice;
            
            if (userChoice == 1) {
                isAuthenticated = authenticateUser();
            }
            else if (userChoice == 2) {
                createAccount();
            }
            else if (userChoice == -1) {
                cout << "\nExiting System... Goodbye!\n";
                break;
            }
            else {
                cout << "\nInvalid Option! Try Again.\n";
            }
            continue;
        }
        
        if (currentUser == "administrator") {
            showAdminOptions();
        } else {
            showUserOptions();
        }
        cin >> userChoice;
        
        if (currentUser == "administrator") {
            switch(userChoice) {
                case 1:
                    displayBanner();
                    break;
                case 2:
                    registerStudent();
                    saveDatabaseToFile();
                    break;
                case 3:
                    displayStudents();
                    break;
                case 4:
                    modifyStudent();
                    saveDatabaseToFile();
                    break;
                case 5:
                    removeStudent();
                    saveDatabaseToFile();
                    break;
                case 6:
                    isAuthenticated = false;
                    currentUser = "";
                    cout << "\n*** Logout Successful ***\n";
                    break;
                case -1:
                    cout << "\nExiting System... Goodbye!\n";
                    break;
                default:
                    cout << "\nInvalid Option Selected!\n";
            }
        }
        else if (currentUser == "regularuser") {
            switch(userChoice) {
                case 1:
                    displayBanner();
                    break;
                case 2:
                    registerStudent();
                    saveDatabaseToFile();
                    break;
                case 3:
                    displayStudents();
                    break;
                case 4:
                    isAuthenticated = false;
                    currentUser = "";
                    cout << "\n*** Logout Successful ***\n";
                    break;
                case -1:
                    cout << "\nExiting System... Goodbye!\n";
                    break;
                default:
                    cout << "\nInvalid Option Selected!\n";
            }
        }
    }
    return 0;
}

void displayBanner() {
    cout << "\n    =========================================" << endl;
    cout << "    ||                                     ||" << endl;
    cout << "    ||   U   U   AAA   M   M   SSSS       ||" << endl;
    cout << "    ||   U   U  A   A  MM MM  S            ||" << endl;
    cout << "    ||   U   U  AAAAA  M M M   SSS         ||" << endl;
    cout << "    ||   U   U  A   A  M   M      S        ||" << endl;
    cout << "    ||    UUU   A   A  M   M  SSSS         ||" << endl;
    cout << "    ||                                     ||" << endl;
    cout << "    =========================================" << endl;
}

void showAdminOptions() {
    cout << "\n+---------------------------------------+\n";
    cout << "|       ADMINISTRATOR CONTROL PANEL     |\n";
    cout << "+---------------------------------------+\n";
    cout << "| 1. Display System Banner              |\n";
    cout << "| 2. Register New Student               |\n";
    cout << "| 3. View All Students                  |\n";
    cout << "| 4. Modify Student Record              |\n";
    cout << "| 5. Remove Student Record              |\n";
    cout << "| 6. Logout from System                 |\n";
    cout << "| -1. Exit Application                  |\n";
    cout << "+---------------------------------------+\n";
    cout << "Enter Your Choice: ";
}

void showUserOptions() {
    cout << "\n+---------------------------------------+\n";
    cout << "|          USER CONTROL PANEL           |\n";
    cout << "+---------------------------------------+\n";
    cout << "| 1. Display System Banner              |\n";
    cout << "| 2. Register New Student               |\n";
    cout << "| 3. View All Students                  |\n";
    cout << "| 4. Logout from System                 |\n";
    cout << "| -1. Exit Application                  |\n";
    cout << "+---------------------------------------+\n";
    cout << "Enter Your Choice: ";
}

bool userAlreadyExists(string uname) {
    ifstream dataFile("university_records.txt");
    string fileLine, existingUser;
    
    if (dataFile.is_open()) {
        while (getline(dataFile, fileLine)) {
            int separatorPos = fileLine.find(',');
            if (separatorPos != string::npos) {
                existingUser = fileLine.substr(0, separatorPos);
                if (existingUser == uname) {
                    dataFile.close();
                    return true;
                }
            }
        }
        dataFile.close();
    }
    return false;
}

void storeUserCredentials(string uname, string upass) {
    ofstream dataFile("university_records.txt", ios::app);
    if (dataFile.is_open()) {
        dataFile << uname << "," << upass << endl;
        dataFile.close();
    }
}

bool validateUserLogin(string uname, string upass) {
    ifstream dataFile("university_records.txt");
    string fileLine, fileUsername, filePassword;
    
    if (dataFile.is_open()) {
        while (getline(dataFile, fileLine)) {
            int separatorPos = fileLine.find(',');
            if (separatorPos != string::npos) {
                fileUsername = fileLine.substr(0, separatorPos);
                filePassword = fileLine.substr(separatorPos + 1);
                if (fileUsername == uname && filePassword == upass) {
                    dataFile.close();
                    return true;
                }
            }
        }
        dataFile.close();
    }
    return false;
}

bool authenticateUser() {
    string inputUsername, inputPassword;
    int accessLevel;
    
    cout << "\n--- User Authentication ---\n";    
    cout << "Choose Access Level:\n";
    cout << "1. Administrator Access\n";
    cout << "2. Regular User Access\n";
    cout << "Selection: ";
    cin >> accessLevel;
    cin.ignore();
    
    cout << "Enter Username: ";
    getline(cin, inputUsername);
    cout << "Enter Password: ";
    cin >> inputPassword;
    
    if (accessLevel == 1) {
        if (inputUsername == SYSTEM_ADMIN && inputPassword == SYSTEM_KEY) {
            currentUser = "administrator";
            cout << "\n*** Administrator Login Success ***\n";
            return true;
        } else {
            cout << "\n*** Invalid Administrator Credentials ***\n";
            return false;
        }
    }
    else if (accessLevel == 2) {
        if (validateUserLogin(inputUsername, inputPassword)) {
            currentUser = "regularuser";
            cout << "\n*** User Login Success ***\n";
            return true;
        } else {
            cout << "\n*** Invalid User Credentials ***\n";
            return false;
        }
    }
    
    cout << "\n*** Invalid Access Level ***\n";
    return false;
}

void createAccount() {
    cout << "\n--- CREATE NEW ACCOUNT ---\n";
    string firstName, lastName, username, password;
    
    cout << "First Name: ";
    cin >> firstName;
    cout << "Last Name: ";
    cin >> lastName;
    cin.ignore();
    
    cout << "Create Username: ";
    getline(cin, username);
    
    if (userAlreadyExists(username)) {
        cout << "\n*** Username Already Taken! ***\n";
        return;
    }
    
    cout << "Create Password: ";
    cin >> password;
    
    storeUserCredentials(username, password);
    cout << "\n*** ACCOUNT CREATED SUCCESSFULLY ***\n";
}

void registerStudent() {
    cout << "\n--- STUDENT REGISTRATION ---\n";
    cout << "Student Full Name: ";
    cin >> studentName[totalStudents];
    cout << "Guardian/Father Name: ";
    cin >> guardianName[totalStudents];
    cin.ignore();
    cout << "Registration Number: ";
    cin >> regNumber[totalStudents];
    cout << "Class Section: ";
    cin >> studentSection[totalStudents];
    cout << "National ID (CNIC): ";
    cin >> nationalID[totalStudents];
    cout << "Student Age: ";
    cin >> studentAge[totalStudents];
    cout << "SSC Total Marks: ";
    cin >> sscMarks[totalStudents];
    cout << "HSC Total Marks: ";
    cin >> hscMarks[totalStudents];
    
    // Calculate percentage
    percentageScore[totalStudents] = ((sscMarks[totalStudents] / 1100.0) * 30) + 
                                     ((hscMarks[totalStudents] / 1200.0) * 70);
    
    totalStudents++;
    cout << "\n===============================================" << endl;
    cout << "     STUDENT REGISTERED SUCCESSFULLY" << endl;
    cout << "===============================================" << endl;
}

void displayStudents() {
    if (totalStudents == 0) {
        cout << "\n*** No Student Records Found ***\n";
        return;
    }
    
    int index = 0;
    while (index < totalStudents) {
        cout << "\n=====================================" << endl;
        cout << "       Student Record #" << (index + 1) << endl;
        cout << "=====================================" << endl;
        cout << "Name: " << studentName[index] << endl;
        cout << "Guardian Name: " << guardianName[index] << endl;
        cout << "Registration No: " << regNumber[index] << endl;
        cout << "Section: " << studentSection[index] << endl;
        cout << "National ID: " << nationalID[index] << endl;
        cout << "Age: " << studentAge[index] << endl;
        cout << "SSC Marks: " << sscMarks[index] << endl;
        cout << "HSC Marks: " << hscMarks[index] << endl;
        cout << "Percentage: " << percentageScore[index] << "%" << endl;
        index++;
    }
}

void modifyStudent() {
    if (totalStudents == 0) {
        cout << "\n*** No Student Records Available ***\n";
        return;
    }
    
    int searchRegNo, foundIndex = -1;
    cout << "\nEnter Registration Number to Modify: ";
    cin >> searchRegNo;
    
    int i = 0;
    do {
        if (regNumber[i] == searchRegNo) {
            foundIndex = i;
            break;
        }
        i++;
    } while (i < totalStudents);
    
    if (foundIndex == -1) {
        cout << "\n*** Student Record Not Found ***\n";
        return;
    }
    
    cout << "\n--- CURRENT INFORMATION ---\n";
    cout << "Name: " << studentName[foundIndex] << endl;
    cout << "Guardian: " << guardianName[foundIndex] << endl;
    cout << "Reg No: " << regNumber[foundIndex] << endl;
    cout << "Section: " << studentSection[foundIndex] << endl;
    cout << "CNIC: " << nationalID[foundIndex] << endl;
    cout << "Age: " << studentAge[foundIndex] << endl;
    cout << "SSC Marks: " << sscMarks[foundIndex] << endl;
    cout << "HSC Marks: " << hscMarks[foundIndex] << endl;
    
    cout << "\n--- ENTER NEW INFORMATION ---\n";
    cout << "New Name: ";
    cin >> studentName[foundIndex];
    cout << "New Guardian Name: ";
    cin >> guardianName[foundIndex];
    cout << "New Registration Number: ";
    cin >> regNumber[foundIndex];
    cout << "New Section: ";
    cin >> studentSection[foundIndex];
    cin.ignore();
    cout << "New CNIC: ";
    cin >> nationalID[foundIndex];
    cout << "New Age: ";
    cin >> studentAge[foundIndex];
    cout << "New SSC Marks: ";
    cin >> sscMarks[foundIndex];
    cout << "New HSC Marks: ";
    cin >> hscMarks[foundIndex];
    
    percentageScore[foundIndex] = ((sscMarks[foundIndex] / 1100.0) * 30) + 
                                  ((hscMarks[foundIndex] / 1200.0) * 70);
    
    cout << "Updated Percentage: " << percentageScore[foundIndex] << "%" << endl;
    cout << "\n===============================================" << endl;
    cout << "     RECORD UPDATED SUCCESSFULLY" << endl;
    cout << "===============================================" << endl;
}

void removeStudent() {
    int deleteRegNo, deleteIndex = -1;
    cout << "\nEnter Registration Number to Delete: ";
    cin >> deleteRegNo;
    
    for (int i = 0; i < totalStudents; i++) {
        if (regNumber[i] == deleteRegNo) {
            deleteIndex = i;
            break;
        }
    }
    
    if (deleteIndex == -1) {
        cout << "\n*** Student Record Not Found ***\n";
        return;
    }
    
    int j = deleteIndex;
    while (j < totalStudents - 1) {
        studentName[j] = studentName[j + 1];
        guardianName[j] = guardianName[j + 1];
        nationalID[j] = nationalID[j + 1];
        studentAge[j] = studentAge[j + 1];
        regNumber[j] = regNumber[j + 1];
        studentSection[j] = studentSection[j + 1];
        sscMarks[j] = sscMarks[j + 1];
        hscMarks[j] = hscMarks[j + 1];
        percentageScore[j] = percentageScore[j + 1];
        j++;
    }
    
    totalStudents--;
    cout << "\n===========================================" << endl;
    cout << "    STUDENT RECORD DELETED SUCCESSFULLY" << endl;
    cout << "===========================================" << endl;
}

void saveDatabaseToFile() {
    ofstream dataFile("university_records.txt");
    if (!dataFile) {
        cout << "\n*** File Error Occurred! ***\n";
        return;
    }
    
    dataFile << totalStudents << endl;
    int i = 0;
    do {
        dataFile << studentName[i] << endl;
        dataFile << guardianName[i] << endl;
        dataFile << regNumber[i] << endl;
        dataFile << studentSection[i] << endl;
        dataFile << nationalID[i] << endl;
        dataFile << studentAge[i] << endl;
        dataFile << sscMarks[i] << endl;
        dataFile << hscMarks[i] << endl;
        dataFile << percentageScore[i] << endl;
        i++;
    } while (i < totalStudents);
    
    dataFile.close();
    cout << "\n*** Data Saved Successfully! ***\n";
}

void loadDatabaseFromFile() {
    ifstream dataFile("university_records.txt", ios::in);
    if (!dataFile) {
        cout << "\n*** No Previous Database Found ***\n";
        return;
    }
    
    dataFile >> totalStudents;
    dataFile.ignore();
    
    int i = 0;
    while (i < totalStudents) {
        getline(dataFile, studentName[i]);
        getline(dataFile, guardianName[i]);
        dataFile >> regNumber[i];
        dataFile >> studentSection[i];
        dataFile.ignore();
        getline(dataFile, nationalID[i]);
        dataFile >> studentAge[i];
        dataFile >> sscMarks[i];
        dataFile >> hscMarks[i];
        dataFile >> percentageScore[i];
        dataFile.ignore();
        i++;
    }
    
    dataFile.close();
    cout << "\n*** Database Loaded Successfully! ***\n";
}