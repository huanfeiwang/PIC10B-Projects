//
//  hmw_5_1.cpp
//
//  Created by Rui Yan on 2019/2/25.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Utilities description

/**
 Swaps two integers.
 @param x the first integer to swap
 @param y the second integer to swap
 */
void swap(int& x, int& y);

/**
 Prints all elements in a vector.
 @param a the vector to print
 */
void print(vector<int> a);

/**
 Swaps two integers.
 @param x the first integer to swap
 @param y the second integer to swap
 */
void swap(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

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



/**
 Gets the position of the smallest element in a vector range.
 @param a the vector
 @param from the beginning of the range
 @param to the end of the range
 @return the position of the smallest element in
 the range a[from]...a[to]
 */
int max_position(vector<int>& a, int from, int to)
{
    int max_pos = from;
    int i;
    for (i = from + 1; i <= to; i++)
        if (a[i] > a[max_pos]) max_pos = i;
    return max_pos;
}

/**
 Sorts a vector using the selection sort algorithm.
 @param a the vector to sort
 */
void selection_sort(vector<int>& a)
{
    int next; // The next position to be set to the minimum
    
    for (next = 0; next < a.size() - 1; next++)
    {
        // Find the position of the minimum
        int min_pos = max_position(a, next, a.size() - 1);
        if (min_pos != next)
            swap(a[min_pos], a[next]);
    }
}

int main()
{
    ifstream infile ("data1.txt");
    string line;
    vector<int> unsorted_v;
    
    while(std::getline(infile, line)){
        int n;
        istringstream(line) >> n;
        unsorted_v.push_back(n);
    }
    
    cout << "Before sorting:\n";
    print(unsorted_v);
    cout << "After sorting:\n";
    selection_sort(unsorted_v);
    print(unsorted_v);

    return 0;
}
