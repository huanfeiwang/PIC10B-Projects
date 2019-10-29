//
//  hmw_3_1.cpp
//
//  Created by Rui Yan on 2019/2/3.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

/**
 Ask a file name and displays the number of characters,
 words, and lines in that file.
 */

// count the number of characters
long Nchars(ifstream& fs)
{
    long char_count = 0;
    if(fs) {
        fs.seekg(0, ios::end);
        char_count += fs.tellg();
        fs.seekg(0, ios::beg);
    }
    return char_count;
}

// count the number of words
long Nwords(ifstream& fs)
{
    long word_count = 0;
    string word;
    string line;
    while(std::getline(fs, line)) {
        stringstream ss(line);
        while (ss >> word) {
            ++word_count;
        }
    }
    fs.clear();
    fs.seekg(0, ios::beg);
    return word_count;
}

// count the number of lines
long Nlines(ifstream& fs)
{
    long line_count = 0;
    string line;

    while(std::getline(fs, line)) {
        ++line_count;
    }
    fs.clear();
    fs.seekg(0, ios::beg);
    return line_count;
}

// main function
int main()
{
    string filename;
    ifstream fs;
    
    cout << "Enter a file name: ";
    std::getline(cin, filename);
    fs.open(filename.c_str());
    
    if (fs.fail()) // if not exist, print error
    {
        cout << "File " << filename << " does not exist! Exit.\n" << endl;
        return(1);
    }
    
    // display the number of chars, words and lines
    long char_count = Nchars(fs);
    cout << "Number of characters = " << char_count << endl;
    
    long word_count = Nwords(fs);
    cout << "Number of words      = " << word_count << endl;
 
    long line_count = Nlines(fs);
    cout << "Number of lines      = " << line_count << endl;

    fs.close();
}

