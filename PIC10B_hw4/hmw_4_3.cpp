//
//  hmw_4_3.cpp
//
//  Created by Rui Yan on 2019/2/17.
//  Copyright © 2019 Rui Yan. All rights reserved.
//
// Problem 10.11

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// function to help implement generate_subsets function
vector<string> subsets(string soFar, string rest) {
    vector<string> result;
    
    for (int i = 0; i < rest.length(); i++) {
        string next = soFar + rest[i];
        string remaining = rest.substr(i+1);
        vector<string> shorter_subset = subsets(next, remaining);
        result.insert(result.end(), shorter_subset.begin(), shorter_subset.end());
    }
    result.push_back(soFar);
    return(result);
}

vector<string> generate_subsets(string s) {
    return(subsets("", s));
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
        result = generate_subsets(s);
        
        cout << result.size() << " subsets" << endl;
        
        //for(int i = int(result.size()-1); i >= 0 ; i--) {
        //    cout << "\"" << result[i] << "\"" << endl;
        //}
        for(int i = 0; i < result.size() ; i++) {
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

