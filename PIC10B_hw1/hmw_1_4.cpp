//
//  hmw_1_4.cpp
//
//  Created by Rui Yan on 2019/1/19.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

// based on Problem P7.13
#include <iostream>
#include <string.h>

using namespace std;

// ask for the input lines and output those lines in the reversed order
int main() {
    bool ctnue = true;           // boolean to determine whether continue
    string ctnuestr;             // input string to determine whether continue
   
    char buffer[1001]; 
    int b = 0;         // count the number of characters stored in buffer
    char* lines[100];  // store the pointes pointing to the beginning of each line
    int l = 0;         // count the number of text lines

    lines[0] = &buffer[0]; // assign the beginning of the first line to buffer[0]
    string s;              // input string
    
    while (ctnue && b <= 1000) { // check whether to continue
        if (l < 100) { // check the number of lines
            cout << "Enter a line: ";
            getline(cin, s);             // get rid of "\n"
            b += int(s.length()) + 1;    // increment b
            
            if (b > 1000) { // check the number of characters in buffer
                cout << "\nBuffer is full! Stop.\n"; // stop if exceed 1000
                cout << endl;
                break;
            } else {
                // store each input string to buffer
                strcpy(lines[l], s.c_str()); // add "\0" at the end of line
                l++;
                lines[l] = &buffer[b]; // assign line to the next string

                // ask for continue or not
                cout << "\nContinue <y/n>? ";
                cin >> ctnuestr;
                cin.ignore(1000, '\n');
                cout << endl;
                
                if (ctnuestr == "n") {
                    ctnue = false;
                } else if (ctnuestr != "y" && ctnuestr != "n") {
                    cout << "Please enter y or n." << endl;
                }

            }
        }
    }
    // output 
    cout << "Lines in reversed order: " << endl;
    cout << endl;
    for (int i = l - 1; i >= 0; i--) { // print lines in reversed order
        cout << lines[i] << endl;
    }
}
