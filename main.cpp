#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// --- Employee Class ---
class Employee {
private:
    int empID;
    string name;
    double basicPay;
    double otHours;
    const double OT_RATE = 25.0;

public:
    Employee(int id, string n, double bp, double ot) 
        : empID(id), name(n), basicPay(bp), otHours(ot) {}

    // Calculation Methods
    double calculateGross() const {
        return basicPay + (otHours * OT_RATE);
    }

    double calculateTax() const {
        double gross = calculateGross();
        if (gross <= 2000) return 0;
        if (gross <= 5000) return (gross - 2000) * 0.10;
        return (3000 * 0.10) + (gross - 5000) * 0.20;
    }

    double calculateNetPay() const {
        return calculateGross() - calculateTax();
    }

    // Getters & Setters
    int getID() const { return empID; }
    string getName() const { return name; }
    void setOT(double hours) { otHours = hours; }
    
    void displaySlip() const {
        cout << "\n---------- PAYSLIP ----------" << endl;
        cout << "ID: " << empID << " | Name: " << name << endl;
        cout << "Basic Pay:  $" << fixed << setprecision(2) << basicPay << endl;
        cout << "OT Hours:   " << otHours << " (Rate: $" << OT_RATE << ")" << endl;
        cout << "Gross Pay:  $" << calculateGross() << endl;
        cout << "Tax Ded.:   $" << calculateTax() << endl;
        cout << "Net Pay:    $" << calculateNetPay() << endl;
        cout << "-----------------------------" << endl;
    }
};

// --- Payroll System Class ---
class PayrollSystem {
private:
    vector<Employee> employees;

public:
    void addEmployee() {
        int id;
        string name;
        double bp, ot;

        cout << "Enter ID: "; cin >> id;
        
        // Validation: Unique ID
        for (const auto& e : employees) {
            if (e.getID() == id) {
                cout << "Error: ID already exists!\n";
                return;
            }
        }

        cout << "Enter Name: "; cin.ignore(); getline(cin, name);
        cout << "Enter Basic Pay: "; cin >> bp;
        cout << "Enter OT Hours: "; cin >> ot;

        if (bp < 0 || ot < 0) {
            cout << "Error: Pay/Hours cannot be negative.\n";
        } else {
            employees.emplace_back(id, name, bp, ot);
            cout << "Employee added successfully.\n";
        }
    }

    void updateOT() {
        int id;
        double hours;
        cout << "Enter EmpID to update OT: "; cin >> id;
        for (auto& e : employees) {
            if (e.getID() == id) {
                cout << "Enter new OT Hours: "; cin >> hours;
                if (hours >= 0) {
                    e.setOT(hours);
                    cout << "OT Updated.\n";
                } else cout << "Invalid hours.\n";
                return;
            }
        }
        cout << "Employee not found.\n";
    }

    void generatePayslip() {
        int id;
        cout << "Enter EmpID: "; cin >> id;
        for (const auto& e : employees) {
            if (e.getID() == id) {
                e.displaySlip();
                return;
            }
        }
        cout << "Employee not found.\n";
    }

    void showReports() {
        if (employees.empty()) return;

        double totalPayout = 0;
        Employee* highest = &employees[0];

        for (auto& e : employees) {
            double net = e.calculateNetPay();
            totalPayout += net;
            if (net > highest->calculateNetPay()) {
                highest = &e;
            }
        }

        cout << "\n===== MONTHLY REPORT =====" << endl;
        cout << "Total Monthly Payout: $" << totalPayout << endl;
        cout << "Highest Paid: " << highest->getName() << " ($" << highest->calculateNetPay() << ")" << endl;
    }
};

int main() {
    PayrollSystem ps;
    int choice;

    do {
        cout << "\n===== PAYROLL MENU =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Update OT\n";
        cout << "3. Generate Payslip\n";
        cout << "4. Show Report\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: ps.addEmployee(); break;
            case 2: ps.updateOT(); break;
            case 3: ps.generatePayslip(); break;
            case 4: ps.showReports(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}