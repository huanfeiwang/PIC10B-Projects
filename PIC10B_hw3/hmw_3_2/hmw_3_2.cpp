//
//  hmw_3_2.cpp
//
//  Created by Rui Yan on 2019/2/3.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    string line;
    ifstream infile1 ("database.txt"); // read database
    ifstream infile2 ("template.txt"); // read template
    vector<string> data;
    
    if(infile1.is_open() && infile2.is_open()) {
        infile1.seekg(0, ios::end);
        // if empty, print message
        if(infile1.tellg() == 0) {
            cout << "The database database.txt is empty. Exit!" << endl;
        } else { 
            // set infile1 pointing back to the beginning 
            infile1.clear();
            infile1.seekg(0);

            // display database content and store each line into a vector
            cout << "Database content: " << endl;
            while(std::getline(infile1, line)){
                data.push_back(line);
                cout << line << endl;
            }

            infile1.close();

            // display template content
            cout << endl;
            cout << "Template content: " << endl;
            while(std::getline(infile2, line)) cout << line << endl;
            infile2.clear();
            infile2.seekg(0);
        }
    }

    cout << endl;
    // loop over each line and print out corresponding junk letters
    for(int i=0; i<data.size(); i++) {
        vector<string> pieces;
        stringstream ss(data[i]);
        string field_val;
        while(getline(ss, field_val, '|')) pieces.push_back(field_val);
        
        // print out each junk letter
        cout << "Junk letter for Record " << i << endl;
        
        // loop over each line in infile2 and replace by each piece of info
        while(getline(infile2, line)) {
            for (int i=0; i < pieces.size(); i++) {
                string index = to_string(i+1);
                int k = line.find('|'+index+'|');
                if(k <= line.length()) line.replace(k, 2+index.length(), pieces[i]);
            }
            cout << line << endl;
        }
        cout << endl;
        infile2.clear();
        infile2.seekg(0);
    }
    infile2.close();
}
