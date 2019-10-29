//
//  hmw_1_1.cpp
//
//  Created by Rui Yan on 2019/1/15.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

// based onProblem P7.1
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Person
{
public:
    // default constructor
    Person(string nm);
    
    // get the name of person
    string get_name() const;
    
    // get the popularity counter of person
    int get_popularity() const;
    
    // get the best friend of person
    Person* get_bestfriend() const;
    
    // set the best friend of person
    void set_bestfriend(Person* bfriend);
    
    // update the popularity counter of person
    void add_popularity();
    
private:
    string name;
    Person* bestfriend;
    int popularity_counter;
};

Person::Person(string nm) {
        name = nm;
        popularity_counter = 0;
        bestfriend = NULL;
}

string Person::get_name() const {
    return name;
}

int Person::get_popularity() const {
    return popularity_counter;
}

Person* Person::get_bestfriend() const {
    return bestfriend;
}

void Person::set_bestfriend(Person* bfriend) {
    bestfriend = bfriend;
}

void Person::add_popularity() {
    popularity_counter += 1;
}


int main() {
    vector<Person*> personvec; // vector to store person
    bool ctnue = true;         // boolean to determine whether continue
    string ctnuestr;           // input string to determine whether continue
    string person_name;        // input string to set person's name
    string bfriend_name;       // input string to set best friend's name
    
    // take input about each person
    while (ctnue){
        cout << "Name: ";
        cin >> person_name;
        cout << endl;
        
        // store each person into person vector
        Person* p = new Person(person_name);
        personvec.push_back(p);
        
        cout << "Continue (y/n)? ";
        cin >> ctnuestr;
        cout << endl;
        if (ctnuestr == "n") ctnue = false;
    }
    
    // take input about the best friend of each person
    cout << "\nEnter the names of best friends: \n" << endl;
    
    for (int i = 0; i < personvec.size(); i++) {
        cout << "Best friend of " << personvec[i]->get_name() << ": ";
        cin >> bfriend_name;
        // update the information of best friend
        for (int j = 0; j < personvec.size(); j++) {
            if (personvec[j]->get_name() == bfriend_name){
                personvec[i]->set_bestfriend(personvec[j]);
                personvec[j]->add_popularity();
            }
        }
    }
    
    // output information about each person, including best friend and popularity
    cout << "\nInformation: \n";
    for (int i = 0; i< personvec.size(); i++) {
        // check if has best friend
        if (personvec[i]->get_bestfriend() != NULL){
            cout << personvec[i]->get_name() << " | " << personvec[i]->get_bestfriend()->get_name() << \
            " | " << personvec[i]->get_popularity() << endl;
        } else {
            cout << personvec[i]->get_name() << " | NONE | " << personvec[i]->get_popularity() << endl;
        }
    }
}





