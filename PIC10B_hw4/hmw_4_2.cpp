//
//  hmw_4_2.cpp
//
//  Created by Rui Yan on 2019/2/16.
//  Copyright © 2019 Rui Yan. All rights reserved.
//
//  Problem 10.10

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> generate_substrings(string s) {
    vector<string> result;
    
    //special cases
    if (s.length() <= 1) {
        result.push_back(s);
        return result;
    }
    
    //general case
    for(int i = 1; i < s.length() + 1; i++) {
        result.push_back(s.substr(0,i));
    }
    // call itself recursively
    vector<string> str_vec = generate_substrings(s.substr(1));
    result.insert(result.end(), str_vec.begin(), str_vec.end());
        
    return result;
}

int main() {
    bool ctnue = true;
    string ctnuestr;
    string s;
    vector<string> result;
    
    while (ctnue) {
        // ask for input
        cout << "Enter a string: ";
        getline(cin, s);
        
        // call function and print
        result = generate_substrings(s);
        for(int i=0; i < result.size(); i++) {
            cout << "\"" << result[i] << "\"" << endl;
        }
        
        // ask if continue
        cout << "Continue <y/n>? ";
        cin >> ctnuestr;
        cin.ignore(256, '\n');
        cout << endl;
        if(ctnuestr == "n") ctnue = false;
    }
}

