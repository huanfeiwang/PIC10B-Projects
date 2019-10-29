//
//  hmw_4.cpp
//
//  Created by Rui Yan on 2019/2/15.
//  Copyright © 2019 Rui Yan. All rights reserved.
//
// Problem 10.6

#include <iostream>
using namespace std;

int find(const string& s, const string& t, int idx)
{
    if(s.length() < t.length())
        return -1;
    else if(s.substr(0, t.length()) == t)
        return idx;

    return find(s.substr(1),t, idx+1);
}

int main() {
    bool ctnue = true;
    string ctnuestr;
    string s;
    string t;
    int result;
    
    while (ctnue) {
        cout << "Enter a string: ";
        getline(cin, s);
        cout << "Enter a string to search for: ";
        getline(cin, t);
        
        result = find(s, t, 0);
        if (result == -1) {
            cout << "Not found!";
        } else {
            cout << "The position = " << result;
        }
        
        // ask if continue
        cout << endl;
        cout << "Continue <y/n>? ";
        cin >> ctnuestr;
        cin.ignore(256, '\n');
        cout << endl;
        if(ctnuestr == "n") ctnue = false;
    }
}

