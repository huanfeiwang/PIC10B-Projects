//
//  hmw_5_2.cpp
//
//  Created by Rui Yan on 2019/2/25.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Employee
{
public:
    Employee(string e_name, double e_salary)
    : name(e_name), salary(e_salary) { }
    string get_name() const { return name; }
    double get_salary() const { return salary; }
    virtual void print() const {
        std::cout << name << ", $" << salary << endl;
    }
    virtual ~Employee() { }
protected:
    string name;
    double salary;
};

void merge(vector<int>& a, int from, int mid, int to) {
    int n = to - from + 1; // Size of the range to be merged
    // Merge both halves into a temporary vector b
    vector<int> b(n);

    int i1 = from;
    // Next element to consider in the first half
    int i2 = mid + 1;
    // Next element to consider in the second half
    int j = 0; // Next open position in b

    // As long as neither i1 nor i2 is past the end, move the smaller
    // element into b
    while (i1 <= mid && i2 <= to) {
        if (a[i1] < a[i2]) {
            b[j] = a[i1];
            i1++;
        } else {
            b[j] = a[i2];
            i2++;
            }
        j++;
    }

    // Note that only one of the two while loops below is executed

    // Copy any remaining entries of the first half
    while (i1 <= mid) {
    b[j] = a[i1];
    i1++;
    j++;
    }
// Copy any remaining entries of the second half
    while (i2 <= to) {
    b[j] = a[i2];
    i2++;
    j++;
    }

    // Copy back from the temporary vector
    for (j = 0; j < n; j++) a[from + j] = b[j];
}

void merge_sort(vector<int>& a, int from, int to) {
    if (from == to) return;
    int mid = (from + to) / 2;
    // Sort the first and the second half
    merge_sort(a, from, mid);
    merge_sort(a, mid + 1, to);
    merge(a, from, mid, to);
	}

// overload operator < for Employee class
bool operator<(const Employee& a, const Employee& b)
{
	return a.get_salary() < b.get_salary();
}

int main() {
    ifstream infile ("data2.txt");
    vector<Employee> employees;
    string line;

    while(getline(infile, line)) {
        int j = 0;
        string info;
        string name;
        double salary;
        stringstream ss(line);

        while(getline(ss, info, '|')) {
            if (j == 0) {
                name = info;
            } else if (j == 1){
                istringstream(info) >> salary;
            }
            j++;
        }
        employees.push_back(Employee(name, salary));
    }

    cout << endl << "Employees, before sorting:\n";
    for (int i = 0; i < employees.size(); i++){
        employees[i].print();
    }

    sort(employees.begin(), employees.end());

    cout << endl << "Employees, after sorting:\n";
    for (int i = 0; i < employees.size(); i++){
		employees[i].print();
	}

    cout << endl;
    return 0;
}
