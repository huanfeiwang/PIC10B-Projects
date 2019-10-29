//
//  hmw_5_4.cpp
//
//  Created by Rui Yan on 2019/2/26.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 Prints all elements in a vector.
 @param a the vector to print
 */
void print(vector<int> a);

/**
 Prints all elements in a vector.
 @param a the vector to print
 */
void print(vector<int> a)
{
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << " ";
    cout << "\n";
}

vector<size_t> remove_duplicates( vector<int>& v ) {
    vector<int> v2;
    vector<size_t> Nocctimes;
    
    // sort vector v
    sort(v.begin(), v.end());
    
    int p = v[0];
    int occtime = 1;

    for (int i = 1; i < v.size(); i++) {
        if(v[i] == p) occtime++;
        else {
            v2.push_back(p);
            Nocctimes.push_back(occtime);
            occtime = 1;
            p = v[i];
        }    
        if(i == v.size()-1) {
            if(v[i] == p) {
                v2.push_back(p);
                Nocctimes.push_back(occtime);
            }
        }
    }
    v = v2;
    return Nocctimes;
}
    
/** main function */
int main() {
    ifstream infile ("data4.txt");
    string line;
    vector<int> a;
    vector<size_t> Nduplicates;
    
    while(std::getline(infile, line)){
        int n;
        istringstream(line) >> n;
        a.push_back(n);
    }

    cout << "Array:";
    print(a);
    
    Nduplicates = remove_duplicates(a);
    
    for(int i = 0; i < Nduplicates.size(); i++) {
        cout << a[i] << " (" << Nduplicates[i] << " times)" << endl;
    }
    
}

