#include <stdio.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "student_checkin.h"
// #include "checkin.h"
using namespace std;

class hostel;
class student_hostel;
class staff;
class HJB;
class CVR;
class VVS;
class SBR;

class staff {
   public:
    staff() {}
    void create_r();
    void delete_r();
    void modify_r();
    staff(string hostel_name) {
        int count = 4;
        while (count) {
            system("cls");
            cout << "\033[1;32mPlease Input Password to enter the STAFF PORTAL\033[0m"
                 << endl;
            string pass;
            cin >> pass;
            if (pass == password_mgr(hostel_name)) {
                break;
            } else {
                --count;
                cout << "\033[1;32mWrong Password, Attempts Remaining---> \n\033[0m"
                     << count << endl;
                system("pause");
            }
        }
        if (count == 0) {
            cout << "\033[1;31mMaximum Attempts of wrong password Input reached. Exiting "
                    "to Main Menu\n\033[0m"
                 << endl;
            system("pause");
            return;
        }
        system("cls");
        cout << "\033[1;33mACCESS GRANTED\n" << endl;
        int choice;
        cout << "Please Enter a choice.\n\033[0m\n" << endl;
        cout << "\033[1;32m1. Create a New Record.\n" << endl;
        cout << "2. Delete an Existing Record.\n" << endl;
        cout << "3. Modify Existig Record.\n" << endl;
        cout << "4. Change Password.\n" << endl;
        cout << "\n5. Return to Main Menu.\033[0m" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                create_r();
                break;
            case 2:
                delete_r();
                break;
            case 3:
                modify_r();
                break;
            case 4:
                change_pass(hostel_name);
                break;
            case 5:
                break;
        }
    }
    string password_mgr(string hostel_name) {
        fstream fin;
        fin.open("password.txt", ios::in);
        while (!fin.eof()) {
            vector<string> prev_data;
            string line, word;
            prev_data.clear();
            getline(fin, line);
            stringstream str(line);
            while (getline(str, word, ' ')) {
                prev_data.push_back(word);
            }
            if (prev_data[0] == hostel_name) {
                return prev_data[1];
            }
        }
        return "";
    }
    void change_pass(string hostel_name) {
        fstream fin, fout;
        string line, word;
        vector<string> prev_data;
        fin.open("password.txt", ios::in);
        fout.open("newpassword.txt", ios::app);
        while (!fin.eof()) {
            prev_data.clear();
            getline(fin, line);
            stringstream str(line);
            while (getline(str, word, ' ')) {
                prev_data.push_back(word);
            }
            if (prev_data[0] == hostel_name) {
                string new_pass;
                cout << "Please Enter New Password---> " << endl;
                cin >> new_pass;
                prev_data[1] = new_pass;
            }
            if (!fin.eof()) {
                for (int i = 0; i < prev_data.size() - 1; i++) {
                    fout << prev_data[i] << " ";
                }
                fout << prev_data[prev_data.size() - 1] << endl;
            }
        }
        fin.close();
        fout.close();
        remove("password.txt");
        rename("newpassword.txt", "password.txt");
    }
};

void staff::create_r() {
    system("cls");
    fstream fin;
    fin.open("Hostel_SR.csv", ios::app);
    cout << "\033[1;33mCREATE AN ENTRY FOR NEW STUDENT IN HOSTEL "
            "DIRETORY(HOSTEL_SR)-->\033[0m\n\n"
         << endl;
    string name, branch, hostel;
    int roll_no, sem, room_no;
    cout << "\033[1;32mPlease enter name: ";
    cin >> name;
    cout << "Please enter Branch: ";
    cin >> branch;
    cout << "Please enter Hostel of the student: ";
    cin >> hostel;
    cout << "Please enter Roll No(for e.g. 123): ";
    cin >> roll_no;
    cout << "Please enter semester of the student: ";
    cin >> sem;
    cout << "Please enter allotted Room No: \033[0m";
    cin >> room_no;
    fin << name << "," << roll_no << "," << branch << "," << sem << ","
        << room_no << "," << hostel << endl;
    fin.close();
    cout << "\033[1;30m\nDETAILS UPDATED SUCCESSFULLY\033[0m" << endl;
    system("pause");
    return;
}
void staff::delete_r() {
    system("cls");
    int flag_for_if_present = 0;
    vector<string> prev_data;
    string line, word;
    fstream fin, fout;
    fin.open("Hostel_SR.csv", ios::in);
    fout.open("temp_file.csv", ios::app);
    int filled_empty = 0;

    // input details
    string branch;
    int roll_no;
    cout << "\033[1;33mDELETE ANY EXISTING ENTRY FROM RECORD(Hostel_SR)-->\033[0m\n\n" << endl;
    cout << "\n\033[1;32mEnter Branch of the student: \033[0m";
    cin >> branch;
    cout << "Enter Roll No. of the student: ";
    cin >> roll_no;
    while (!fin.eof()) {
        prev_data.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            prev_data.push_back(word);
        }
        // updating value here
        if (prev_data[2] == branch && stoi(prev_data[1]) == roll_no) {
            flag_for_if_present = 1;
            cout << "\033[1;34mEntry Found, Deleting Record......\033[0m"
                 << endl;
            cout << "\033[1;34m\nRECORD UPDATED SUCCESSFULLY\033[0m" << endl;
            filled_empty = 1;
            continue;
        }
        // filling current lines to csv
        if (!fin.eof()) {
            for (int i = 0; i < prev_data.size() - 1; i++) {
                fout << prev_data[i] << ",";
            }
            fout << prev_data[prev_data.size() - 1] << endl;
        }
    }
    fin.close();
    fout.close();
    remove("Hostel_SR.csv");
    rename("temp_file.csv", "Hostel_SR.csv");
    if (flag_for_if_present == 0) {
        cout << "\033[1;34mNO SUCH ENTRY FOUND IN RECORD\033[0m" << endl;
    }
    system("pause");
    return;
}

void staff::modify_r() {
    system("cls");
    cout << "\033[1;33mMODIFY ANY EXISTING ENTRY FROM RECORD(Hostel_SR)-->\033[0m\n\n" << endl;
    int flag_for_if_present = 0;
    vector<string> prev_data;
    string line, word;
    fstream fin, fout;
    fin.open("Hostel_SR.csv", ios::in);
    fout.open("temp_file.csv", ios::app);
    int filled_empty = 0;

    // reenter details to be modified
    string name, branch, hostel;
    string roll_no, sem, room_no;
    cout << "\033[1;33mPlease enter Branch: ";
    cin >> branch;
    cout << "Please enter Roll No(for e.g. 123): ";
    cin >> roll_no;

    while (!fin.eof()) {
        prev_data.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            prev_data.push_back(word);
        }
        // updating value here
        if (prev_data[2] == branch && prev_data[1] == roll_no) {
            flag_for_if_present = 1;
            cout << "Please enter name: ";
            cin >> name;
            cout << "Please enter Hostel of the student: ";
            cin >> hostel;
            cout << "Please enter semester of the student: ";
            cin >> sem;
            cout << "Please enter allotted Room No: \033[0m";
            cin >> room_no;
            cout << "\033[1;34mEntry Found, Modifying Record......\033[0m"
                 << endl;
            prev_data[0] = name;
            prev_data[3] = sem;
            prev_data[4] = room_no;
            prev_data[5] = hostel;
            cout << "\033[1;34m\nRECORD MODIFIED SUCCESSFULLY\033[0m" << endl;
            filled_empty = 1;
        }
        // filling current lines to csv
        if (!fin.eof()) {
            for (int i = 0; i < prev_data.size() - 1; i++) {
                fout << prev_data[i] << ",";
            }
            fout << prev_data[prev_data.size() - 1] << endl;
        }
    }
    fin.close();
    fout.close();
    remove("Hostel_SR.csv");
    rename("temp_file.csv", "Hostel_SR.csv");
    if (flag_for_if_present == 0) {
        cout << "\033[1;34m\n\nNO SUCH ENTRY FOUND IN RECORD\033[0m" << endl;
    }
    system("pause");
}

class HJB {
   public:
    // add this function to your code later on.
    HJB() {
        while (true) {
            system("cls");
            cout << "\033[1;33m=======.::Welcome to H.B.J Portal::.=======\n" << endl;
            string filename = "hjb.csv";
            int choice;
            cout << "Choose whether the operator is Student or Staff--->\033[0m\n"
                 << endl;
            cout << "\033[1;32m1. Student \033[0m\n" << endl;
            cout << "\033[1;32m2. Staff \033[0m\n" << endl;
            cout << "\033[1;32m3. To Select Hostel/Main Menu\033[0m\n" << endl;
            cin >> choice;
            if (choice == 3) {
                return;
            }
            switch (choice) {
                case 1:
                    student_call();
                    break;
                case 2:
                    staff s("HJB");
                    break;
            }
        }
    }
    friend class staff;
};

class SBR {
   public:
    // add this function to your code later on.
    SBR() {
        while (true) {
            system("cls");
            cout << "\033[1;33m=======.::Welcome to H.B.J Portal::.=======\n" << endl;
            string filename = "hjb.csv";
            int choice;
            cout << "Choose whether the operator is Student or Staff--->\033[0m\n"
                 << endl;
            cout << "\033[1;32m1. Student \033[0m\n" << endl;
            cout << "\033[1;32m2. Staff \033[0m\n" << endl;
            cout << "\033[1;32m3. To Select Hostel/Main Menu\033[0m\n" << endl;
            cin >> choice;
            if (choice == 3) {
                return;
            }
            switch (choice) {
                case 1:
                    student_call();
                    break;
                case 2:
                    staff s("SBR");
                    break;
            }
        }
    }
    friend class staff;
};

class CVR {
   public:
    //add this function to your code later on.
    CVR() {
        while (true) {
            system("cls");
            cout << "\033[1;33m=======.::Welcome to H.B.J Portal::.=======\n" << endl;
            int choice;
            cout << "Choose whether the operator is Student or Staff--->\033[0m\n"
                 << endl;
            cout << "\033[1;32m1. Student \033[0m\n" << endl;
            cout << "\033[1;32m2. Staff \033[0m\n" << endl;
            cout << "\033[1;32m3. To Select Hostel/Main Menu\033[0m\n" << endl;
            cin >> choice;
            if (choice == 3) {
                return;
            }
            switch (choice) {
                case 1:
                    student_call();
                    break;
                case 2:
                    staff s("CVR");
                    break;
            }
        }
    }
    friend class staff;
};

class VVS {
   public:
    // add this function to your code later on.
    VVS() {
        while (true) {
            system("cls");
            cout << "\033[1;33m=======.::Welcome to H.B.J Portal::.=======\n" << endl;
            int choice;
            cout << "Choose whether the operator is Student or Staff--->\033[0m\n"
                 << endl;
            cout << "\033[1;32m1. Student \033[0m\n" << endl;
            cout << "\033[1;32m2. Staff \033[0m\n" << endl;
            cout << "\033[1;32m3. To Select Hostel/Main Menu\033[0m\n" << endl;
            cin >> choice;
            if (choice == 3) {
                return;
            }
            switch (choice) {
                case 1:
                    student_call();
                    break;
                case 2:
                    staff s("VVS");
                    break;
            }
        }
    }
    friend class staff;
};

class hostel {
   public:
    hostel() {
        while (true) {
            system("cls");
            cout << "\033[1;32m=========.::WELCOME TO HOSTEL MANEGEMENT "
                    "PROGRAM::.=========\033[0m\n"
                 << endl;
                 cout << "\033[1;32m============.::DELHI TECHNOLOGICAL UNIVERSITY::.============\033[0m\n"
                 << endl;
                 cout << "\033[1;32m============.::DATA STRUCTRES AND ALGO PROJECT::.============\033[0m\n"
                 << endl;
                  cout << "\033[1;32m============.::SUBMITTED TO: PROF. JASRAJ MEENA::.============\033[0m\n"
                 << endl;
            int choice;
            cout << "\033[1;33mPlease select the hostel you are in right now.\n" << endl;
            cout << "1. H.J.B\n" << endl;
            cout << "2. V.V.S\n" << endl;
            cout << "3. S.B.R\n" << endl;
            cout << "4. C.V.R\033[0m\n" << endl;
            cout << "\033[1;30mInput -1 to EXIT\033[0m\n" << endl;
            cout << ">  ";
            cin >> choice;
            if (choice == -1) {
                system("cls");
                cout<<"\033[1;32m===.::THANK YOU FOR USING THE PROGRAM::.===\n"<<endl;
                system("pause");
                break;
            } // \033[1;30m  \033[0m
            switch (choice) {
                case 1:
                    HJB();
                    break;
                case 2:
                    VVS();
                    break;
                case 3:
                    SBR();
                    break;
                case 4:
                    CVR();
                    break;
                case -1:
                    break;
            }
        }
    }
};