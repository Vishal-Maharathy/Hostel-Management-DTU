#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Time;
class time_spent;
class student;
class visitant;

bool search_dir(string, int);
void update_csv(string, string, int, string);
void add_row(string, string, int, string);
void cal_time(string, string, int);
visitant r_visitant(string, int);

class Time {
   public:
    int hour, min;
    // usage-> "r_time(Time &object);"
};

// time spent in hostel room
class time_spent {
   public:
    int hour_current;
    int min_current;
};
// will save if checkout and visitant's name
class visitant {
   public:
    string visitant;
    bool check_out;
};

void r_time(Time& value) {
    time_t t = time(0);
    tm* tm = localtime(&t);
    value.hour = tm->tm_hour;
    value.min = tm->tm_min;
    return;
}

class student {
   public:
    string name;
    string branch;
    string visitant;  // new entry
    int roll_no;
    Time time_in;
    Time time_out;
    bool present;

    student(string nm, string bnch, int roll, string vis) {
        name = nm;
        branch = bnch;
        roll_no = roll;
        visitant = vis;
        present = search_dir(branch, roll);
        // if present then look for the value in data and fill with check out
        // time
        if (present) {
            cout << "\033[1;34mThis Entry is already Present\033[0m" << endl;
            update_csv(name, branch, roll_no, visitant);
        }
        // check for value with no checkout then change that value- make a
        // [update value] function
        else {
            add_row(name, branch, roll_no, vis);
        }
    }
    void check_in() { r_time(time_in); }
    void check_out() { r_time(time_out); }
    void display() {
        cout << "\033[1;34mName: \033[0m" << name << endl;
        cout << "\033[1;34mCheck In: \033[0m" << time_in.hour << ":"
             << time_in.min << endl;
        cout << "\033[1;34mCheck Out: \033[0m" << time_out.hour << ":"
             << time_out.min << endl;
    }
    bool if_present() { return present; }
    void friend update_csv(string, string, int);
};

// searches for a given entry in the database.
bool search_dir(string branch, int roll) {
    fstream fin;
    fin.open("data.csv", ios::in);
    vector<string> prev_data;
    while (!fin.eof()) {
        string line, word;
        prev_data.clear();
        getline(fin, line);
        stringstream s(line);
        int flag = 0;
        while (getline(s, word, ',')) {
            if (branch == word && flag == 0) {
                flag = 1;
                continue;
            } else if (flag == 1) {
                flag = 0;
                int temp = stoi(word);
                if (temp == roll) {
                    return true;
                }
            }
        }
    }
    return false;
}

// if no checkout time then update with checkouttime;
// default null value for checkoutime is 111:111
void update_csv(string name, string branch, int roll, string visitant) {
    vector<string> prev_data;
    string line, word;
    fstream fin, fout;
    fin.open("data.csv", ios::in | ios::app);
    fout.open("reportcardnew.csv", ios::app);
    int filled_empty = 0;
    while (!fin.eof()) {
        prev_data.clear();

        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            prev_data.push_back(word);
        }
        // updating value here
        if (prev_data[1] == branch && stoi(prev_data[2]) == roll &&
            prev_data[4] == "-----") {
            // filled_empty will ensure that there was an empty check out. else
            // this if this remains 0, this means after exiting the loop, we
            // have to make a new entry in the csv.

            cout << "\033[1;34mEntry Found, You are checking out\033[0m"
                 << endl;
            cout << "\033[1;34m\nVALUE UPDATED SUCCESSFULLY\033[0m" << endl;
            filled_empty = 1;
            Time curr_time;
            r_time(curr_time);
            string timeOutH = to_string(curr_time.hour);
            timeOutH = timeOutH + ":" + to_string(curr_time.min);
            prev_data[4] = timeOutH;
            // cout << prev_data[4] << endl;
        }
        // filling current line to csv
        if (!fin.eof()) {
            for (int i = 0; i < prev_data.size() - 1; i++) {
                fout << prev_data[i] << ",";
            }
            fout << prev_data[prev_data.size() - 1] << endl;
        }
    }
    fin.close();
    fout.close();
    remove("data.csv");
    rename("reportcardnew.csv", "data.csv");
    if (filled_empty == 0) {
        // make new row at the last of the csv
        cout << "\033[1;34mYou just CheckedIn, adding Entry to CSV\033[0m"
             << endl;
        add_row(name, branch, roll, visitant);
    }
}

// add row. will get called after there is no entry for the current search
void add_row(string name, string branch, int roll, string visitant) {
    fstream myFile;
    myFile.open("data.csv", ios::in | ios::app);
    if (!myFile.is_open()) {
        cout << "Error Opening data.csv" << endl;
    }
    Time curr_time;
    r_time(curr_time);
    string timeInH = to_string(curr_time.hour);
    timeInH = timeInH + ":" + to_string(curr_time.min);
    string timeOutH = "-----";
    myFile << name << "," << branch << "," << roll << "," << timeInH << ","
           << timeOutH << "," << visitant << endl;
    myFile.close();
}

Time string_time(string s) {
    Time t;
    string hour, min;
    for (int i = 0; i < s.size(); i++) {
        while (s[i] != ':') {
            hour.push_back(s[i++]);
        }
        if (s[i] == ':') {
            i++;
        }
        while (s[i] != '\0') {
            min.push_back(s[i++]);
        }
    }
    t.hour = stoi(hour);
    t.min = stoi(min);
    return t;
}

// calculate time spent by person in hostel room
void cal_time(string branch, int roll) {
    int time_hour = 0;
    int time_min = 0;

    if (!search_dir(branch, roll)) {
        cout << "\033[1;34mNo Such Student is in the Hostel\033[0m" << endl;
        return;
    }
    fstream fin;
    fin.open("data.csv", ios::in);
    int i = 0;  // existence explained further
    while (!fin.eof()) {
        vector<string> line_data;
        string line, word;
        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            line_data.push_back(word);
        }
        // to skip first line of csv as it has headings.
        if (i == 0 || !line[1]) {
            i = 1;
            continue;
        }
        if (line_data[4] == "-----" && line_data[1] == branch &&
            stoi(line_data[2]) == roll) {
            Time time_spent_checkin = string_time(line_data[3]);
            Time time_current;
            r_time(time_current);
            int hour = time_current.hour - time_spent_checkin.hour;
            int min = abs(time_current.min - time_spent_checkin.min);
            time_hour += hour;
            time_min += min;
            cout
                << "\033[1;34mThe elapsed since visitied student is in hostel: "
                << hour << " hours and " << min << "minutes\033[0m" << endl;
        } else if (line_data[4] != "-----" && line_data[1] == branch &&
                   stoi(line_data[2]) == roll) {
            Time time_spent_checkin = string_time(line_data[3]);
            Time time_spent_checkout = string_time(line_data[4]);
            int hour = abs(time_spent_checkout.hour - time_spent_checkin.hour);
            int min = abs(time_spent_checkout.min - time_spent_checkin.min);
            time_hour += hour;
            time_min += min;
        }
    }
    cout << "\033[1;34mTotal Time spent by the visitor in hostel: " << time_hour
         << " hours and " << time_min << " minutes\033[0m" << endl;
}

void s_inHostel() {
    fstream fin;
    fin.open("data.csv", ios::in);
    int i = 0;
    int flag = 0;
    while (!fin.eof()) {
        vector<string> line_data;
        string line, word;
        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            line_data.push_back(word);
        }
        // to skip first line of csv as it has headings.
        if (i == 0 || !line[1]) {
            i = 1;
            continue;
        }
        if (line_data[4] == "-----") {
            flag = 1;
            Time time_spent_checkin = string_time(line_data[3]);
            Time time_current;
            r_time(time_current);
            int hour = time_current.hour - time_spent_checkin.hour;
            int min = abs(time_current.min - time_spent_checkin.min);
            cout << "\033[1;34mName of the Student:                         "
                    "\033[0m"
                 << line_data[0] << endl;
            cout << "\033[1;34mBranch of the Student:                       "
                    "\033[0m"
                 << line_data[1] << endl;
            cout << "\033[1;34mRoll No:                                     "
                    "\033[0m"
                 << line_data[2] << endl;
            cout << "\033[1;34mTime since the visitor is still in hostel:   "
                    "\033[0m"
                 << hour << " hours and " << min << " minutes\n\033[0m" << endl;
            cout << "\033[1;34m=====================\033[0m" << endl;
        }
    }
    if (flag == 0) {
        cout << "\033[1;34mNo Visitors are currently in Hostel\033[0m" << endl;
        cout << "\033[1;34m=====\033[0m" << endl;
    }
}

visitant r_visitant(string branch, int roll) {
    visitant temp;
    fstream fin;
    fin.open("data.csv", ios::in);
    while (!fin.eof()) {
        vector<string> line_data;
        string line, word;
        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            line_data.push_back(word);
        }
        if (line_data[1] == branch && stoi(line_data[2]) == roll) {
            if (line_data[4] == "-----") {
                temp.check_out = false;
            } else {
                temp.check_out = true;
            }
            temp.visitant = line_data[5];
            return temp;
        }
    }
    return temp;
}