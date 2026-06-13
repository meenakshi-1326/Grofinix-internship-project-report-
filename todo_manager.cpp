#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
class Task {
private:
    string title;
    string description;
    string date;
    string status;
    string priority;
public:
    void addTask() {
        cin.ignore();
        cout << "\nEnter Task Title: ";
        getline(cin, title);
        cout << "Enter Description: ";
        getline(cin, description);
        cout << "Enter Due Date (DD/MM/YYYY): ";
        getline(cin, date);
        cout << "Enter Priority (Low/Medium/High): ";
        getline(cin, priority);
        status = "Pending";
        cout << "\nTask Added Successfully!\n";
    }
    void displayTask(int index) {
        cout << "\n==============================================================";
        cout << "\nNo\tTitle\t\tDate\t\tPriority\tStatus";
        cout << "\n==============================================================";
        cout << "\n" << index + 1
             << "\t" << title
             << "\t\t" << date
             << "\t" << priority
             << "\t\t";
        if(status == "Done")
            cout << "[✔] Done";
        else
            cout << "[ ] Pending";
        cout << endl;
    }
    void editTask() {
        cin.ignore();
        cout << "\nEnter New Title: ";
        getline(cin, title);
        cout << "Enter New Description: ";
        getline(cin, description);
        cout << "Enter New Date: ";
        getline(cin, date);
        cout << "Enter New Priority: ";
        getline(cin, priority);
        cout << "\nTask Updated Successfully!\n";
    }
    void markDone() {
        status = "Done";
        cout << "\nTask Marked as Completed!\n";
    }
    void saveToFile(ofstream &file) {
        file << title << endl;
        file << description << endl;
        file << date << endl;
        file << priority << endl;
        file << status << endl;
    }
    void loadFromFile(ifstream &file) {
        getline(file, title);
        getline(file, description);
        getline(file, date);
        getline(file, priority);
        getline(file, status);
    }
    string getStatus() {
        return status;
    }
    string getDate() {
        return date;
    }
};
int main() {
    vector<Task> tasks;
    int choice;
    int taskNumber;
    ifstream infile("tasks.txt");
    if(infile) {
        Task temp;
        while(!infile.eof()) {
            temp.loadFromFile(infile);
            if(infile)
                tasks.push_back(temp);
        }
        infile.close();
    }
    do {
        cout << "\n=========== TO-DO TASK MANAGER ===========";
        cout << "\n1. Add Task";
        cout << "\n2. View Tasks";
        cout << "\n3. Edit Task";
        cout << "\n4. Delete Task";
        cout << "\n5. Mark Task as Done";
        cout << "\n6. Filter Pending Tasks";
        cout << "\n7. Save Tasks";
        cout << "\n8. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;
        switch(choice) {
            case 1: {
                Task t;
                t.addTask();
                tasks.push_back(t);
                break;
            }
            case 2: {
                if(tasks.empty()) {
                    cout << "\nNo Tasks Available!\n";
                }
                else {
                    for(int i = 0; i < tasks.size(); i++) {

                        tasks[i].displayTask(i);
                    }
                }
                break;
            }
            case 3: {
                cout << "\nEnter Task Number to Edit: ";
                cin >> taskNumber;
                if(taskNumber > 0 && taskNumber <= tasks.size()) {
                    tasks[taskNumber - 1].editTask();
                }
                else {
                    cout << "\nInvalid Task Number!\n";
                }
                break;
            }
            case 4: {
                cout << "\nEnter Task Number to Delete: ";
                cin >> taskNumber;
                if(taskNumber > 0 && taskNumber <= tasks.size()) {
                    tasks.erase(tasks.begin() + taskNumber - 1);
                    cout << "\nTask Deleted Successfully!\n";
                }
                else {
                    cout << "\nInvalid Task Number!\n";
                }
                break;
            }
            case 5: {
                cout << "\nEnter Task Number to Mark Done: ";
                cin >> taskNumber;
                if(taskNumber > 0 && taskNumber <= tasks.size()) {
                    tasks[taskNumber - 1].markDone();
                }
                else {
                    cout << "\nInvalid Task Number!\n";
                }
                break;
            }
            case 6: {
                cout << "\n========== PENDING TASKS ==========\n";
                for(int i = 0; i < tasks.size(); i++) {
                    if(tasks[i].getStatus() == "Pending") {

                        tasks[i].displayTask(i);
                    }
                }
                break;
            }
            case 7: {
                ofstream outfile("tasks.txt");
                for(int i = 0; i < tasks.size(); i++) {
                    tasks[i].saveToFile(outfile);
                }
                outfile.close();
                cout << "\nTasks Saved Successfully!\n";
                break;
            }
            case 8: {
                ofstream outfile("tasks.txt");
                for(int i = 0; i < tasks.size(); i++) {
                    tasks[i].saveToFile(outfile);
                }
                outfile.close();
                cout << "\nThank You! Exiting Program...\n";
                break;
            }
            default:
                cout << "\nInvalid Choice! Please Try Again.\n";
        }
    } 
    while(choice != 8);
    return 0;
}