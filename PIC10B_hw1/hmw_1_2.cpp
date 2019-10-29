//
//  hmw_1_2.cpp
//
//  Created by Rui Yan on 2019/1/17.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

// based on Problem P7.6
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

// function maximum to find the pointer to the maximum number in array
double* maximum (double* a, int a_size) {
    assert(a_size > 0);
    double* max = a;
    for (int i = 0; i < a_size; i++) {
        if (*max < *(a+i)) {
            max = a+i;
        }
    }
    return max;
}

// ask for the input arrays and find maximum
int main() {
    bool ctnue = true;           // boolean to determine whether continue
    string ctnuestr;             // input string to determine whether continue
    
    while (ctnue) {
        string s;                // store input string of numbers
        vector<string> nums_str; // store each seperated strings of numbers
        int a_size = 0;          // store the number of input numbers
        int j = 0;               // help to allocate the first index of each number
        
        cout << "Enter a list of numbers: ";
        getline(cin, s);
        
        // find the number of input values and separate each value
        for(int i = 0; i < s.length(); i++) {
            if(s[i] == ' ') {
                a_size += 1;
                nums_str.push_back(s.substr(j, i-j));
                j = i+1;
            } else if (i == s.length()-1) {
                a_size += 1;
                nums_str.push_back(s.substr(j, i+1-j));
            }
        }
        
        double* a = new double[a_size]; // dynamic array that stores the input values

        // convert numbers in string to double
        for(int i = 0; i < a_size; i++) {
            a[i] = stod(nums_str[i]);
        }
        
        // output
        double* result = maximum(a, a_size);
        cout << "maximal element: " << *result << endl;
        cout << "index of the maximal element: " << result - a << endl;
        
        // ask for continue or not
        cout << "\nContinue <y/n>? ";
        cin >> ctnuestr;
        cin.ignore(1000, '\n');
        cout << endl;
        
        // delete the array
        delete [] a;
        
        if (ctnuestr == "n") {
            ctnue = false;
        } else if (ctnuestr != "y" && ctnuestr != "n") {
            cout << "Please enter y or n." << endl;
        }
    }
}


