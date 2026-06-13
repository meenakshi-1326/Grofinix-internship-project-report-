#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
class Student {
private:
    int rollNo;
    string name;
    float marks1, marks2, marks3;
    float percentage;
    char grade;
public:
    void input() {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        do {
            cout << "Enter Marks in Subject 1 (0-100): ";
            cin >> marks1;
        } while(marks1 < 0 || marks1 > 100);
        do {
            cout << "Enter Marks in Subject 2 (0-100): ";
            cin >> marks2;
        } while(marks2 < 0 || marks2 > 100);
        do {
            cout << "Enter Marks in Subject 3 (0-100): ";
            cin >> marks3;
        } while(marks3 < 0 || marks3 > 100);
        calculateResult();
    }
    void calculateResult() {
        percentage = (marks1 + marks2 + marks3) / 3;
        if(percentage >= 80)
            grade = 'A';
        else if(percentage >= 60)
            grade = 'B';
        else if(percentage >= 40)
            grade = 'C';
        else
            grade = 'F';
    }
    void display() {
        cout << "\n====================================================";
        cout << "\nRoll No\tName\t\tPercentage\tGrade";
        cout << "\n====================================================";
        cout << "\n" << rollNo
             << "\t" << name
             << "\t\t" << fixed << setprecision(2)
             << percentage
             << "%\t\t" << grade << endl;
    }
    float getPercentage() {
        return percentage;
    }
    char getGrade() {
        return grade;
    }
    int getRollNo() {
        return rollNo;
    }
    void update() {
        cout << "\nEnter New Marks for Subject 1: ";
        cin >> marks1;
        cout << "Enter New Marks for Subject 2: ";
        cin >> marks2;
        cout << "Enter New Marks for Subject 3: ";
        cin >> marks3;
        calculateResult();
        cout << "\nRecord Updated Successfully!\n";
    }
    void saveReport() {
        ofstream file("report_card.txt", ios::app);
        file << "\n====================================";
        file << "\nStudent Report Card";
        file << "\n====================================";
        file << "\nRoll Number : " << rollNo;
        file << "\nName        : " << name;
        file << "\nPercentage  : " << percentage << "%";
        file << "\nGrade       : " << grade;
        if(grade == 'F')
            file << "\nResult      : FAIL";
        else
            file << "\nResult      : PASS";
        file << "\n====================================\n";
        file.close();
    }
};
int main() {
    Student students[100];
    int count = 0;
    int choice;
    int searchRoll;
    float total = 0;
    float highest = 0;
    int topperIndex = 0;
    do {
        cout << "\n========= STUDENT GRADING SYSTEM =========";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Update Student";
        cout << "\n4. Search Student";
        cout << "\n5. Class Average";
        cout << "\n6. Highest Scoring Student";
        cout << "\n7. Pass/Fail Summary";
        cout << "\n8. Export Report Cards";
        cout << "\n9. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                students[count].input();
                count++;
                cout << "\nStudent Record Added Successfully!\n";
                break;
            case 2:
                for(int i = 0; i < count; i++) {
                    students[i].display();
                }
                break;
            case 3:
                cout << "\nEnter Roll Number to Update: ";
                cin >> searchRoll;
                for(int i = 0; i < count; i++) {
                    if(students[i].getRollNo() == searchRoll) {
                        students[i].update();
                        break;
                    }
                }
                break;
            case 4:
                cout << "\nEnter Roll Number to Search: ";
                cin >> searchRoll;
                for(int i = 0; i < count; i++) {
                    if(students[i].getRollNo() == searchRoll) {
                        students[i].display();
                        break;
                    }
                }
                break;
            case 5:
                total = 0;
                for(int i = 0; i < count; i++) {
                    total += students[i].getPercentage();
                }
                if(count > 0) {
                    cout << "\nClass Average = "
                         << fixed << setprecision(2)
                         << total / count << "%\n";
                }
                break;
            case 6:
                highest = students[0].getPercentage();
                for(int i = 1; i < count; i++) {
                    if(students[i].getPercentage() > highest) {
                        highest = students[i].getPercentage();
                        topperIndex = i;
                    }
                }
                cout << "\nHighest Scoring Student:\n";
                students[topperIndex].display();
                break;
            case 7: {
                int pass = 0, fail = 0;
                for(int i = 0; i < count; i++) {
                    if(students[i].getGrade() == 'F')
                        fail++;
                    else
                        pass++;
                }
                cout << "\nPass Students : " << pass;
                cout << "\nFail Students : " << fail << endl;
                break;
            }
            case 8:
                for(int i = 0; i < count; i++) {
                    students[i].saveReport();
                }
                cout << "\nReport Cards Exported to report_card.txt\n";
                break;
            case 9:
                cout << "\nThank You! Exiting Program...\n";
                break;
            default:
                cout << "\nInvalid Choice! Please Try Again.\n";
        }
    } while(choice != 9);
    return 0;
}