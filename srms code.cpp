#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class Student {
public:
    int roll;
    string name;
    float cgpa;
    int marks;
    string remarks;

    void input() {
        cout << "\nEnter Roll Number: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter CGPA: ";
        cin >> cgpa;
        cout << "Enter Marks: ";
        cin >> marks;
        cin.ignore();
        cout << "Enter Remarks (ex: Active in sports): ";
        getline(cin, remarks);
    }

    void display() {
        cout << "\n-------------------------------------------";
        cout << "\nRoll No: " << roll;
        cout << "\nName: " << name;
        cout << "\nCGPA: " << cgpa;
        cout << "\nMarks: " << marks;
        cout << "\nRemarks: " << remarks;
        cout << "\n-------------------------------------------\n";
    }
};
class Ticket {
public:
    int roll;
    string issue;

    void raiseTicket() {
        cout << "\nEnter your Roll Number: ";
        cin >> roll;
        cin.ignore();
        cout << "Describe the issue (ex: CGPA wrong, remarks wrong): ";
        getline(cin, issue);
    }

    void display() {
        cout << "\n--- Ticket Raised ---";
        cout << "\nRoll: " << roll;
        cout << "\nIssue: " << issue << "\n";
    }
};
void saveStudent(Student s) {
    ofstream out("students.dat", ios::binary | ios::app);
    out.write((char*)&s, sizeof(s));
    out.close();
}

void viewAllStudents() {
    ifstream in("students.dat", ios::binary);
    Student s;
    while (in.read((char*)&s, sizeof(s))) {
        s.display();
    }
    in.close();
}

void updateStudent(int rollNo) {
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    Student s;
    int found = 0;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.roll == rollNo) {
            found = 1;
            cout << "\nExisting Record: ";
            s.display();

            cout << "\nEnter new details:\n";
            s.input();

            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "\nRecord Updated Successfully!\n";
            break;
        }
    }
    if (!found) cout << "\nRecord Not Found!\n";
    file.close();
}
void saveTicket(Ticket t) {
    ofstream out("tickets.dat", ios::binary | ios::app);
    out.write((char*)&t, sizeof(t));
    out.close();
}

void viewTickets() {
    ifstream in("tickets.dat", ios::binary);
    Ticket t;
    while (in.read((char*)&t, sizeof(t))) {
        t.display();
    }
    in.close();
}
void adminMenu();
void hodMenu();
void professorMenu();
void studentTicketMenu();
void login() {
    int choice;
    do {
        cout << "\n===== LOGIN PORTAL =====";
        cout << "\n1. Admin";
        cout << "\n2. HOD";
        cout << "\n3. Professor";
        cout << "\n4. Student (Raise Ticket)";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: adminMenu(); break;
            case 2: hodMenu(); break;
            case 3: professorMenu(); break;
            case 4: studentTicketMenu(); break;
            case 5: cout << "\nExiting...\n"; break;
            default: cout << "\nInvalid Choice!\n";
        }
    } while (choice != 5);
}
void adminMenu() {
    int choice;
    do {
        cout << "\n===== ADMIN MENU =====";
        cout << "\n1. Add Student";
        cout << "\n2. View All Students";
        cout << "\n3. Update Student";
        cout << "\n4. View Tickets";
        cout << "\n5. Back";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            Student s; 
            s.input();
            saveStudent(s);
        }
        else if (choice == 2) viewAllStudents();
        else if (choice == 3) {
            int r; cout << "Enter Roll to Update: "; cin >> r;
            updateStudent(r);
        }
        else if (choice == 4) viewTickets();
    } while (choice != 5);
}
void hodMenu() {
    int choice;
    do {
        cout << "\n===== HOD MENU =====";
        cout << "\n1. View All Students";
        cout << "\n2. View Tickets";
        cout << "\n3. Back";
        cout << "\nEnter: ";
        cin >> choice;

        if (choice == 1) viewAllStudents();
        else if (choice == 2) viewTickets();
    } while (choice != 3);
}

void professorMenu() {
    int choice;
    do {
        cout << "\n===== PROFESSOR MENU =====";
        cout << "\n1. View Students";
        cout << "\n2. Update Student Report/Remarks";
        cout << "\n3. Back";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) viewAllStudents();
        else if (choice == 2) {
            int r; 
            cout << "Enter Roll to Update: "; 
            cin >> r;
            updateStudent(r);
        }
    } while (choice != 3);
}
void studentTicketMenu() {
    Ticket t;
    t.raiseTicket();
    saveTicket(t);
    cout << "\nTicket Raised Successfully!\n";
}
int main() {
    login();
    return 0;
}
