#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Class to represent a student
class Student {
public:
    string name;
    int rollNumber;
    string department;
    float cgpa;
    string contact;

    void input() {
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cin.ignore();
        cout << "Enter Department: ";
        getline(cin, department);
        cout << "Enter CGPA: ";
        cin >> cgpa;
        cin.ignore();
        cout << "Enter Contact Number: ";
        getline(cin, contact);
    }

    void display() const {
        cout << left << setw(15) << name
             << setw(10) << rollNumber
             << setw(15) << department
             << setw(6) << cgpa
             << setw(15) << contact << endl;
    }
};

// Function prototypes
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;
    do {
        cout << "\n===== STUDENT RECORD MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 6);

    return 0;
}

// Function to add a student
void addStudent() {
    Student s;
    s.input();
    ofstream outFile("students.txt", ios::app);
    if(outFile.is_open()) {
        outFile << s.name << "\n"
                << s.rollNumber << "\n"
                << s.department << "\n"
                << s.cgpa << "\n"
                << s.contact << "\n";
        outFile.close();
        cout << "Student record added successfully!\n";
    } else {
        cout << "Error opening file!\n";
    }
}

// Function to display all students
void displayAllStudents() {
    ifstream inFile("students.txt");
    if(inFile.is_open()) {
        string name, department, contact;
        int roll;
        float cgpa;

        cout << left << setw(15) << "Name" 
             << setw(10) << "RollNo" 
             << setw(15) << "Department" 
             << setw(6) << "CGPA" 
             << setw(15) << "Contact" << endl;
        cout << string(61, '-') << endl;

        while(getline(inFile, name)) {
            inFile >> roll;
            inFile.ignore();
            getline(inFile, department);
            inFile >> cgpa;
            inFile.ignore();
            getline(inFile, contact);

            Student s;
            s.name = name;
            s.rollNumber = roll;
            s.department = department;
            s.cgpa = cgpa;
            s.contact = contact;
            s.display();
        }
        inFile.close();
    } else {
        cout << "No records found.\n";
    }
}

// Function to search for a student by roll number
void searchStudent() {
    int rollNo;
    cout << "Enter Roll Number to search: ";
    cin >> rollNo;

    ifstream inFile("students.txt");
    bool found = false;
    if(inFile.is_open()) {
        string name, department, contact;
        int roll;
        float cgpa;

        while(getline(inFile, name)) {
            inFile >> roll;
            inFile.ignore();
            getline(inFile, department);
            inFile >> cgpa;
            inFile.ignore();
            getline(inFile, contact);

            if(roll == rollNo) {
                cout << "Record Found:\n";
                Student s;
                s.name = name;
                s.rollNumber = roll;
                s.department = department;
                s.cgpa = cgpa;
                s.contact = contact;
                s.display();
                found = true;
                break;
            }
        }
        inFile.close();
        if(!found) cout << "Student with Roll Number " << rollNo << " not found.\n";
    } else {
        cout << "No records found.\n";
    }
}

// Function to update a student record
void updateStudent() {
    int rollNo;
    cout << "Enter Roll Number to update: ";
    cin >> rollNo;

    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");
    bool found = false;

    if(inFile.is_open() && tempFile.is_open()) {
        string name, department, contact;
        int roll;
        float cgpa;

        while(getline(inFile, name)) {
            inFile >> roll;
            inFile.ignore();
            getline(inFile, department);
            inFile >> cgpa;
            inFile.ignore();
            getline(inFile, contact);

            if(roll == rollNo) {
                cout << "Enter new details:\n";
                Student s;
                s.input();
                tempFile << s.name << "\n"
                         << s.rollNumber << "\n"
                         << s.department << "\n"
                         << s.cgpa << "\n"
                         << s.contact << "\n";
                found = true;
            } else {
                tempFile << name << "\n"
                         << roll << "\n"
                         << department << "\n"
                         << cgpa << "\n"
                         << contact << "\n";
            }
        }
        inFile.close();
        tempFile.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if(found) cout << "Record updated successfully!\n";
        else cout << "Record not found.\n";
    } else {
        cout << "Error opening file!\n";
    }
}

// Function to delete a student record
void deleteStudent() {
    int rollNo;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNo;

    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");
    bool found = false;

    if(inFile.is_open() && tempFile.is_open()) {
        string name, department, contact;
        int roll;
        float cgpa;

        while(getline(inFile, name)) {
            inFile >> roll;
            inFile.ignore();
            getline(inFile, department);
            inFile >> cgpa;
            inFile.ignore();
            getline(inFile, contact);

            if(roll == rollNo) {
                found = true;
                continue; // Skip writing this record to delete it
            } else {
                tempFile << name << "\n"
                         << roll << "\n"
                         << department << "\n"
                         << cgpa << "\n"
                         << contact << "\n";
            }
        }
        inFile.close();
        tempFile.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if(found) cout << "Record deleted successfully!\n";
        else cout << "Record not found.\n";
    } else {
        cout << "Error opening file!\n";
    }
}
