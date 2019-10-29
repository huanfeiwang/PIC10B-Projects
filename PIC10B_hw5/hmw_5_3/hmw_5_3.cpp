//
//  hmw_5_3.cpp
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

// finds the smallest element in the vector that is larger than the value
int find (vector<int>& v, int value, bool found) {
    int start = 0, end = v.size()-1;

    // if value were not found, return v.size() if value is the largest
    if(!found && (v[end] < value)) return v.size();

    while(start < end) {
        int mid = (start+end)/2;
        if(v[mid] <= value) start = mid+1;
        else end = mid;
    }

    // if value found, return the index of match value
    if (found) {
        if (v[end] == value) return end;
        else return end-1;
    }
    // if value not found, return the next larger value
    else return end;
}

/**
 Consider the binary search function in Section 11.7. If no match is found,
 the function returns –1. Modify the function so that it returns a bool value
 indicating whether a match was found. Add a reference parameter m, which
 is set to the location of the match if the search was successful. If a
 was not found, set m to the index of the next larger value instead, or
 to a.size() if a is larger than all the elements of the vector.
 */

bool binary_search(vector<int>& v, int value, int& m) {
    // if v is not sorted, then return flase and set m=-1
    if (!is_sorted(v.begin(), v.end())) {
        m = -1;
        return false;
    } else {
        int result = binary_search(v.begin(), v.end(), value);
        m = find(v, value, result);
        // if v is sorted and a match is found, return true
        if (result) return true;
        // if v is sorted and value not found
        else return false;
    }
}


/** main function */
int main() {
    bool ctnue = true;         // boolean to determine whether continue
    string ctnuestr;           // input string to determine whether continue
    
    ifstream infile ("data3.txt");
    string line;
    vector<int> a;
    
    while(std::getline(infile, line)){
        int n;
        istringstream(line) >> n;
        a.push_back(n);
    }
    
    cout << "Before sorting:\n";
    print(a);
    
    sort(a.begin(), a.end());
    
    cout << "After sorting:\n";
    print(a);
    
    while (ctnue){
        int m;
        int value;
        bool found;

        cout << endl << "Enter a value: ";
        cin >> value;
        cin.ignore(1000, '\n');

        found = binary_search(a, value, m);
        if (found) {
            cout << "Found. m=" << m << endl;
        } else {
            cout << "Not found. m=" << m << endl;
        }
        
        cout << endl << "Continue <y/n>? ";
        cin >> ctnuestr;
        cin.ignore(1000, '\n');

        if (ctnuestr == "n") ctnue = false;
    }
}
