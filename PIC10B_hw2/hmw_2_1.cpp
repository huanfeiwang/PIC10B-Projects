//
//  hmw_2_1.cpp
//
//  Created by Rui Yan on 2019/1/28.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

// parent class Person
class Person {
public:
    Person(string name, string birthday);
    string get_name() const { return name; }
    string get_birthday() const { return birthday; }
    void print() const;
private:
    string name;
    string birthday;
};

// derived class Instructor
class Instructor : public Person {
public:
    Instructor(string _name, string _birthday, double _salary);
    void print() const;
private:
    double salary;
};

// derived class Student
class Student : public Person {
public:
    Student(string _name, string _birthday, string _major);
    void print() const;
private:
    string major;
};

// Person class constructor
Person::Person(string name, string birthday) {
    this->name = name;
    this->birthday = birthday;
};

// Instructor class constructor
Instructor::Instructor(string _name, string _birthday, double _salary)
:Person(_name, _birthday){
    salary = _salary;
};

// Student class constructor
Student::Student(string _name, string _birthday, string _major)
:Person(_name, _birthday){
    major = _major;
};

// Person class member function print
void Person::print() const {
    cout << "Name:     " << get_name() << endl;
    cout << "Birthday: " << get_birthday() << endl;
}

// Instructor class member function print
void Instructor::print() const {
    Person::print();
    cout << "Salary:   " << salary << endl;
}

// Student class member function print
void Student::print() const {
    Person::print();
    cout << "Major:    " << major << endl;
}

// Ask for input and print information
int main() {
    string person_name;
    string person_birthday;
    
    string instructor_name;
    string instructor_birthday;
    double instructor_salary;
    
    string student_name;
    string student_birthday;
    string student_major;

    // create a person using given informaiton
    cout << "Person's full name: ";
    getline(cin,person_name);
    cout << "Persons' birthday <mm/dd/yyyy>: ";
    getline(cin,person_birthday);
    cout << endl;
    Person p(person_name,person_birthday);
    
    // create a instructor using given informaiton
    cout << "Instructor's full name: ";
    getline(cin,instructor_name);
    cout << "Instructor's birthday <mm/dd/yyyy>: ";
    getline(cin,instructor_birthday);
    cout << "Instructor's salary: ";
    cin >> instructor_salary;
    cin.ignore(256, '\n');
    cout << endl;
    Instructor i(instructor_name,instructor_birthday,instructor_salary);
    
    // create a student using given informaiton
    cout << "Student's full name: ";
    getline(cin,student_name);
    cout << "Student's birthday <mm/dd/yyyy>: ";
    getline(cin,student_birthday);
    cout << "Student's major: ";
    getline(cin,student_major);
    cout << endl;
    Student s(student_name,student_birthday,student_major);
    
    // print information
    cout << "Person's Information:" << endl;
    p.print();
    cout << endl;
    
    cout << "Instructor's Information:" << endl;
    i.print();
    cout << endl;
    
    cout << "Student's Information:" << endl;
    s.print();
}
