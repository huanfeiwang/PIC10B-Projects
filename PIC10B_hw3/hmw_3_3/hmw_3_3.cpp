//
//  hmw_3_3.cpp
//
//  Created by Rui Yan on 2019/2/6.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Function to reverse a char array
void reverse(char* str) {
    // swap character
    char*p = str;
    char*q = str;
    while(*q!='\0') q++;
    q = q-1;
    while(p<q) {
        char temp = *p;
        *p = *q;
        *q = temp;
        p++;
        q--;
    }
}

// main function
int main() {
    string line;
    string filename;
    ifstream ifs;
    ofstream ofs;
    int Nlines = 0;
    
    cout << "Enter the name of the file: ";
    cin >> filename;
    ifs.open(filename.c_str(), ifstream::in ); // read file
    ofs.open(filename.c_str(), ofstream::in | ofstream::out ); //write file
    
    if(ifs.fail()){ // if file not exist, display error
        cout << "Error opening file " << filename << "!\n" << endl;
        return(1);
    } else { 
        // display the orignal file 
        cout << "Original file " << filename << " content: " << endl;
        while(std::getline(ifs, line)){
            cout << line << endl;
            Nlines++;
        } 
        // display the reversed file
        cout << "\nReversed file " << filename << " content: " << endl;
        // set ifs pointing back to the beginning 
        ifs.clear();
        ifs.seekg(0);

        // an array to store reversed char ptr
        char* revlines[Nlines];
        int k = 0;
        // reverse and store each line into the array revlines
        while(std::getline(ifs, line)) {
            // find length of string
            int n = line.length();
            // create dynamic pointer char array
            char *rev = new char[n+1];
            // copy of string to ptr array
            strcpy(rev, line.c_str());
            // reverse ptr array
            reverse(rev);
            revlines[k] = rev;
            k++;
        }

        // write to the file
        for(int i = 0; i < Nlines; i++) {
            ofs << revlines[i] << '\n';
        }
        
        ifs.close(); // close ifs
        ofs.close(); // close ofs
        
        ifstream ifs2; // open a new ifs2 to read the reversed file
        ifs2.open(filename.c_str(), ifstream::in );
        while(std::getline(ifs2, line)) cout << line << endl;
    }
}
