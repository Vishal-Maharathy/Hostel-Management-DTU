#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "checkin.h"
using namespace std;

void check_time() {
    string branch;
    int roll;
    cout << "\033[1;33mPlease enter your Branch: \033[0m";
    cin >> branch;
    cout << "\033[1;33mPlease enter your Roll Number in the format->[123] : "
            "\033[0m";
    cin >> roll;
    cal_time(branch, roll);
    return;
}

void set_details() {
    string name, branch, visitant_name;
    int roll;
    cout << "\033[1;33mPlease enter your First Name                       : "
            "\033[0m";
    cin >> name;
    cout << "\033[1;33mPlease enter your Branch:                          : "
            "\033[0m";
    cin >> branch;
    cout << "\033[1;33mPlease enter your Roll Number in the format->[123] "
            ":\033[0m";
    cin >> roll;
    if (search_dir(branch, roll)) {
        visitant temp = r_visitant(branch, roll);
        if (!temp.check_out) {
            student s(name, branch, roll, temp.visitant);
            return;
        }
    }
    cout << "\033[1;33mPlease enter Name, Roll No, and Branch of the visitant "
            "in the "
            "format 'Name/Branch/RollNo': \033[0m";
    cin >> visitant_name;
    student s(name, branch, roll, visitant_name);
    return;
}
void initialise() {
    fstream fin;
    fin.open("data.csv", ios::in);
    if (fin.is_open()) {
        return;
    }
    fin.open("data.csv", ios::app);
    fin << "Visitor"
        << ","
        << "Branch"
        << ","
        << "Roll No."
        << ","
        << "Check In"
        << ","
        << "Check Out"
        << ","
        << "Visitant" << endl;
    return;
}
void student_call() {
    while (true) {
        system("cls");
        cout << "\033[1;32m=========.::WELCOME TO HOSTEL MANAGEMENT PROGRAM::.========\n\033[0m"<< endl;
        cout << "\033[1;32m============.::DELHI TECHNOLOGICAL UNIVERSITY::.===========\n\033[0m"<< endl;
        cout << "\033[1;32mCreated By: Vishal Maharathy\n\033[0m"<< endl;

        int choice;
        cout << "\033[1;33m\nPlease choose one option\033[0m" << endl;
        cout << "\033[1;33m\n1. To Enter/Return from Hostel.\033[0m" << endl;
        cout << "\033[1;33m\n2. To Check Time spent in hostel room by "
                "visitor.\033[0m"
             << endl;
        cout << "\033[1;33m\n3. To Check visitors still in Hostel.\033[0m"
             << endl;
        cout << "\033[1;33m\n4. To Exit.\n\n\033[0m" << endl;
        cout << "\033[1;33m--> \033[0m";
        cin >> choice;
        if (choice == 4) {
            system("cls");
            break;
        }
        if (choice == -1) {
            break;
        }
        switch (choice) {
            case 1:
                while (true) {
                    system("cls");
                    set_details();
                    cout
                        << "\033[1;35m\n\nEnter 1 To Return To Main Menu\033[0m"
                        << endl;
                    cout << "\033[1;35mEnter 2 To Fill Another Entry\033[0m"
                         << endl;
                    int temp;
                    cin >> temp;
                    if (temp == 2) {
                        continue;
                    }
                    if (temp == 1) {
                        break;
                    }
                }
                break;
            case 2:
                while (true) {
                    system("cls");
                    check_time();
                    cout
                        << "\033[1;35m\n\nEnter 1 To Return To Main Menu\033[0m"
                        << endl;
                    cout << "\033[1;35mEnter 2 To Check Another Entry\033[0m"
                         << endl;
                    int temp;
                    cin >> temp;
                    if (temp == 2) {
                        continue;
                    }
                    if (temp == 1) {
                        break;
                    }
                }
                break;
            case 3:
                while (true) {
                    system("cls");
                    s_inHostel();
                    cout
                        << "\033[1;35m\n\nEnter 1 To Return To Main Menu\033[0m"
                        << endl;
                    cout << "\033[1;35mEnter 2 To Check Another Entry\033[0m"
                         << endl;
                    int temp;
                    cin >> temp;
                    if (temp == 2) {
                        continue;
                    }
                    if (temp == 1) {
                        break;
                    }
                }
            default:
                break;
        }
    }
}