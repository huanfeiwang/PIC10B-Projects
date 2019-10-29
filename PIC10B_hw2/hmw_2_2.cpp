//
//  hmw_2_2.cpp
//
//  Created by Rui Yan on 2019/1/28.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// The following codes help compute the relative number of days given a date
const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int Ndays(int m, int d, int y) {
    int Nleapyrs;
    
    // calculate the number of leap years
    if (m > 2) {
        Nleapyrs = y/4 - y/100 + y/400;
    } else {
        Nleapyrs = (y-1)/4 - (y-1)/100 + (y-1)/400;
    }
    
    // initialize count using years and day
    int n = y*365 + d;
    
    // add days for months in given date
    for (int i=0; i<m - 1; i++)
        n += monthDays[i];
    // add a day for every leap year
    n += Nleapyrs;
    
    return n;
}

// base class Appointment (abstract class)
class Appointment {
public:
    Appointment(string desc,string date,string time);
    string get_desc() const { return _desc; } // get the description of appointment
    string get_time() const { return _time; } // get the time of appointment
    
    virtual bool occurs_on(int year, int month, int day) = 0; // abstract function
protected:
    string _desc;
    string _time;
    string _date;
};

// derived class Onetime
class Onetime : public Appointment {
public:
    Onetime(string desc,string date,string time):Appointment(desc,date,time) { };
    // implement details in abstract function
    virtual bool occurs_on(int year, int month, int day) {
        int m = stoi(_date.substr(0,2));
        int d = stoi(_date.substr(3,2));
        int y = stoi(_date.substr(6,4));
        // check if the input date is the same as appointment starting date
        if(year==y && month==m && day==d) {
            return true;
        } else {
            return false;
        }
    }
};

// derived class Daily
class Daily : public Appointment {
public:
    Daily(string desc,string date,string time):Appointment(desc,date,time) { };
    // implement details in abstract function
    virtual bool occurs_on(int year, int month, int day) {
        int m = stoi(_date.substr(0,2));
        int d = stoi(_date.substr(3,2));
        int y = stoi(_date.substr(6,4));
        // check if the input date is later than appointment starting date
        int diff = Ndays(month,day,year) - Ndays(m,d,y);
        if(diff >= 0) {
            return true;
        } else {
            return false;
        }
    }
};

// derived class Weekly
class Weekly : public Appointment {
public:
    Weekly(string desc,string date,string time):Appointment(desc,date,time) { };
    // implement details in abstract function
    virtual bool occurs_on(int year, int month, int day) {
        int m = stoi(_date.substr(0,2));
        int d = stoi(_date.substr(3,2));
        int y = stoi(_date.substr(6,4));
        // check if the input date is later than appointment starting date
        // check if the number of days between two dates are multiple of 7
        int diff = Ndays(month,day,year) - Ndays(m,d,y);
        if(diff>=0 && diff%7==0) {
            return true;
        } else {
            return false;
        }
    }
};

// derived class Monthly
class Monthly : public Appointment {
public:
    Monthly(string desc,string date,string time):Appointment(desc,date,time) { };
    // implement details in abstract function
    virtual bool occurs_on(int year, int month, int day) {
        int m = stoi(_date.substr(0,2));
        int d = stoi(_date.substr(3,2));
        int y = stoi(_date.substr(6,4));
        // check if the input date is later than appointment starting date
        // check if the day of input date is same as the day of appointment starting date
        if(year>y && day==d) {
            return true;
        } else if (year==y && month>=m && day==d) {
            return true;
        } else {
            return false;
        }
    }
};

// constructor of base class Appointment
Appointment::Appointment(string desc,string date,string time) {
    this->_desc = desc;
    this->_date = date;
    this->_time = time;
}

// ask for input and print the appointment information at a given date
int main() {
    vector<Appointment*> appointments = ;
    bool ctnue = true;
    string ctnuestr;
    string check_date;
    
    cout << "Enter the list of appointments." << endl;
    cout << endl;
    
    while(ctnue) {
        string description;
        string type;
        string date;
        string time;
        
        cout << "Appointment's description: ";
        getline(cin, description);
        
        cout << "Appointment's type: ";
        getline(cin, type);
        
        cout << "Appointment's starting date: ";
        getline(cin, date);
        
        cout << "Appointment's time: ";
        getline(cin, time);
        
        // create appointment objects using given information
        // let pointers in appointments point to those objects
        if (type == "Onetime") {
            appointments.push_back(new Onetime(description,date,time));
        } else if (type == "Daily") {
            appointments.push_back(new Daily(description,date,time));
        } else if (type == "Weekly") {
            appointments.push_back(new Weekly(description,date,time));
        } else if (type == "Monthly") {
            appointments.push_back(new Monthly(description,date,time));
        }
        
        // ask if continue
        cout << endl;
        cout << "Another appointment <y/n>? ";
        cin >> ctnuestr;
        cin.ignore(256, '\n');
        cout << endl;
        if(ctnuestr == "n") ctnue = false;
    }
    // ask for check_date
    cout << "________________________" << endl;
    cout << "Enter a date: ";
    getline(cin, check_date);
    cout << endl;
    
    // print appointment information at check_date
    cout << "The list of appointments that happen on " << check_date << ":" << endl;
    cout << endl;
    
    int month = stoi(check_date.substr(0,2));
    int day = stoi(check_date.substr(3,2));
    int year = stoi(check_date.substr(6,4));
    for(int i=0, j=0; i < appointments.size(); i++) {
        if(appointments[i]->occurs_on(year, month, day)) {
            cout << j << " " << appointments[i]->get_desc() << ", " << appointments[i]->get_time() << endl;
            j++;
        }
    }
}
