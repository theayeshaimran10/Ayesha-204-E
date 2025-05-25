
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Date {
public:
    int day, month, year;
};

class ExpenseNode {
public:
    int id;
    string name;
    double price;
    Date date;
    ExpenseNode* next;

    ExpenseNode(int i, string n, double p, Date d) {
        id = i;
        name = n;
        price = p;
        date = d;
        next = nullptr;
    }
};

class ExpenseList {
public:
    ExpenseNode* head;

    ExpenseList() {
        head = nullptr;
    }

    void addExpense(int id, string name, double price, Date date) {
        ExpenseNode* newNode = new ExpenseNode(id, name, price, date);
        if (!head)
            head = newNode;
        else {
            ExpenseNode* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    void viewExpenses() {
        ExpenseNode* temp = head;
        if (!temp) {
            cout << "No expenses to display.";
            return;
        }
        while (temp) {
            cout << "ID: " << temp->id << ", Name: " << temp->name
                 << ", Price: " << temp->price << ", Date: "
                 << temp->date.day << "/" << temp->date.month << "/" << temp->date.year << endl;
            temp = temp->next;
        }
    }

    void editExpense(int id) {
        ExpenseNode* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Enter new name: ";
                cin >> temp->name;
                cout << "Enter new price: ";
                cin >> temp->price;
                cout << "Enter new date (DD MM YYYY): ";
                cin >> temp->date.day >> temp->date.month >> temp->date.year;
                cout << "Expense updated.";
                return;
            }
            temp = temp->next;
        }
        cout << "Expense not found.";
    }

    void deleteExpense(int id) {
        ExpenseNode* temp = head;
        ExpenseNode* prev = nullptr;
        while (temp) {
            if (temp->id == id) {
                if (!prev)
                    head = temp->next;
                else
                    prev->next = temp->next;
                delete temp;
                cout << "Expense deleted.";
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Expense not found.";
    }

    void monthlyReport(int month) {
        ExpenseNode* temp = head;
        double total = 0;
        cout << "Expenses for month: " << month << endl;
        while (temp) {
            if (temp->date.month == month) {
                cout << "ID: " << temp->id << ", Name: " << temp->name
                     << ", Price: " << temp->price << ", Date: "
                     << temp->date.day << "/" << temp->date.month << "/" << temp->date.year << endl;
                total += temp->price;
            }
            temp = temp->next;
        }
        cout << "Total: " << total << endl;
    }
};

class MasterList {
public:
    vector<ExpenseList> sessions;

    void addSession(ExpenseList list) {
        sessions.push_back(list);
    }

    ExpenseList& getCurrentSession() {
        return sessions.back();
    }

    void newSession() {
        ExpenseList newList;
        sessions.push_back(newList);
    }

    void displayAllSessions() {
        if (sessions.empty()) {
            cout << "No sessions available.";
            return;
        }

        for (int i = 0; i < sessions.size(); i++) {
            cout << "\n--- Session " << i + 1 << " ---\n";
            sessions[i].viewExpenses();
        }
    }
};

int main() {
    MasterList master;
    master.newSession();

    int choice;
    do {
        cout << "\n1. Add New Expense\n2. View All Expenses\n3. Edit Expense\n4. Delete Expense\n";
        cout << "5. Monthly Report\n6. New Session\n7. View All Sessions\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name;
                double price;
                Date date;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter date (DD MM YYYY): ";
                cin >> date.day >> date.month >> date.year;
                master.getCurrentSession().addExpense(id, name, price, date);
                break;
            }
            case 2:
                master.getCurrentSession().viewExpenses();
                break;
            case 3: {
                int id;
                cout << "Enter ID to edit: ";
                cin >> id;
                master.getCurrentSession().editExpense(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                master.getCurrentSession().deleteExpense(id);
                break;
            }
            case 5: {
                int month;
                cout << "Enter month (1-12): ";
                cin >> month;
                master.getCurrentSession().monthlyReport(month);
                break;
            }
            case 6:
                master.newSession();
                cout << "New session created.";
                break;
            case 7:
                master.displayAllSessions();
                break;
            case 0:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice.";
        }
    } while (choice != 0);

    return 0;
}
