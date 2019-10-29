//
//  hmw_1_5.cpp
//
//  Created by Rui Yan on 2019/1/20.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

// based on Problem P7.17
#include <iostream>
#include <string>

using namespace std;

// define a pointer to a function
typedef int (*intFunPointer)(int);
int f(int x) { return x*x; }

// function fill_with_values to square each element in an array[1,2,3,...,size]
void fill_with_values(int a[], int size, intFunPointer f) {
    for (int i = 0; i < size; i++) {
        a[i] = f(i+1);
    }
}

// ask for the size of arrays and fill with values
int main() {
    bool ctnue = true;           // boolean to determine whether continue
    string ctnuestr;             // input string to determine whether continue
    
    while (ctnue) {
        int size;
        cout << "Enter the size of the array: ";
        cin >> size;

        // create a dynamic array and fill with values
        int* a = new int[size];
        fill_with_values(a, size, f);

        // output
        for(int i = 0; i < size - 1; i++) {
            cout << a[i] << ", ";
        }
        cout << a[size - 1] << endl;

        // ask for continue or not
        cout << "\nContinue <y/n>? ";
        cin >> ctnuestr;
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
