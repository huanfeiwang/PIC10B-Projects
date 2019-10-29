//
//  hmw_7_2.cpp
//
//  Created by Rui Yan on 2019/3/14.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Matrix{
public:
    //nickname for the data type storing size of the vector
    typedef vector<double>::size_type size_type;
    
    //nickname for vector<double>
    typedef vector<double> Vector;
    
    // constructors
    Matrix() {} // empty matrix
    Matrix( const string fileName ); // n x m matrix
    Matrix( size_type n, size_type m, double val = 0.0 ); // n x m matrix
    Matrix( const Vector & v ); // matrix n x 1 derived from Vector
    
    //operator() for getting Matrix (i,j) value
    double operator()(size_type i, size_type j) const;
    
    //operator() for setting Matrix (i,j) value
    double & operator()(size_type i, size_type j);

    //operator*:
    Matrix operator*(double c) const; // Matrix*constant
    vector<double> operator*(const vector<double> &v); // Matrix*Vector
    Matrix operator*(const Matrix & B) const; //Matrix*Matrix
    
    //operator+:
    Matrix operator+(const Matrix & B) const;//Matrix+Matrix
    Matrix operator-(const Matrix & B) const;//Matrix-Matrix
    Matrix operator-() const;// -Matrix
    
    //matrix size getters (2 alternatives):
    pair< size_type, size_type > size() const; // returns std::pair
    // void size( size_type & n, size_type & m ) const; //size is set in n, m
    
    //printing the matrix as a table:
    //Here width and prec are formatting parameters used for the input.
    //width is used in cout << setw(bw)
    //prec is used in cout << fixed << setprecision(prec)
    //width=6 and prec = 2 are default values
    void print(unsigned short width = 6, unsigned short prec = 2) const;
    
    //returns true if the matrix is empty
    bool empty() const;
    
    //resizing matrix to n x m
    void resize(size_type n, size_type m );
    
    //needed for overloading << operator which uses print()
    friend ostream & operator<<( ostream& os, const Matrix & A );
    
private:
    size_type nrow;
    size_type ncol;
    vector< vector<double> > values; //2-d array storage of the matrix
};

// matrix from specified file
Matrix::Matrix( const string fileName ){
    
    ifstream fs(fileName); // input file stream to open the file
    
    // find the number of rows and columns
    size_type n = 0;
    size_type m = 0;
    
    string line;
    double element;
    
    while(getline(fs, line)) {
        stringstream ss(line);
        m = 0;
        while(ss >> element) {
            ++m;
        }
        ++n;
    }
    fs.clear();
    fs.seekg(0, ios::beg);
    
    // set the number of rows and columns
    nrow = n;
    ncol = m;
    resize(nrow, ncol);
    
    for (size_type i = 0; i < n; i++) {
        for (size_type j = 0; j < m; j++) {
            fs >> values[i][j];
        }
    }
}

// n x m matrix
Matrix::Matrix( size_type n, size_type m, double val ){
    nrow = n;
    ncol = m;
    resize(nrow, ncol);
    for (size_type i = 0; i < nrow; i++) {
        for (size_type j = 0; j < ncol; j++) {
            values[i][j] = val;
        }
    }
}

// matrix n x 1 derived from Vector
Matrix::Matrix( const Vector & v ) {
    nrow = v.size();
    ncol = 1;
    resize(nrow, ncol);
    for (size_type i = 0; i < nrow; i++) {
        values[i][0] = v[i];
    }
}

//operator() for getting Matrix (i,j) value
double Matrix::operator()(size_type i, size_type j) const { // we must have a getter with a constant
    return values[i][j]; // getter just returns copy; we cannot write it on the left side of assignment
}

//operator() for setting Matrix (i,j) value
double & Matrix::operator()(size_type i, size_type j) {
    return values[i][j]; // setter returns a reference to the object; we can use it for assignment operator
}

//operator*:
// Matrix*constant
Matrix Matrix::operator*(double c) const{
    Matrix result(ncol, nrow, 0.0);
    for(size_type i = 0; i < nrow; i++) {
        for(size_type j = 0; j < ncol; j++) {
            result(i,j) = values[i][j] * c;
        }
    }
    return result;
}

// Matrix*Vector
vector<double> Matrix::operator*(const vector<double> &v) {
    vector<double> result(nrow);
    for(size_type i = 0; i < nrow; i++) {
        for(size_type j = 0; j < ncol; j++) {
            result[i] += values[i][j] * v[j];
        }
    }
    return result;
}

//Matrix*Matrix
Matrix Matrix::operator*(const Matrix & B) const{
    Matrix result(nrow, B.size().second, 0.0);
    if(ncol == B.size().first){
        double temp = 0.0;
        for(size_type i = 0; i < nrow; i++) {
            for(size_type j = 0; j < B.size().second; j++) {
                temp = 0.0;
                for(size_type k = 0; k < ncol; k++) {
                    temp += values[i][k] * B(k, j);
                }
                result(i,j) = temp;
            }
        }
    }
    return result;
}

//operator+:
//Matrix+Matrix
Matrix Matrix::operator+(const Matrix & B) const {
    Matrix result(nrow, ncol, 0.0);
    for(size_type i = 0; i < nrow; i++) {
        for(size_type j = 0; j < ncol; j++) {
            result(i, j) = this->values[i][j] + B(i,j);
        }
    }
    return result;
}

//Matrix-Matrix
Matrix Matrix::operator-(const Matrix & B) const {
    Matrix result(nrow, ncol, 0.0);
    for(size_type i = 0; i < nrow; i++) {
        for(size_type j = 0; j < ncol; j++) {
            result(i, j) = this->values[i][j] - B(i,j);
        }
    }
    return result;
}

// -Matrix
Matrix Matrix::operator-() const {
    Matrix result(nrow, ncol, 0.0);
    for(size_type i = 0; i < nrow; i++) {
        for(size_type j = 0; j < ncol; j++) {
            result(i, j) = -this->values[i][j];
        }
    }
    return result;
}

//matrix size getters (2 alternatives):
// returns std::pair
pair< Matrix::size_type, Matrix::size_type > Matrix::size() const {
    pair< size_type, size_type > matrix_size = make_pair(this->nrow, this->ncol);
    return matrix_size;
}

//printing the matrix as a table:
//Here width and prec are formatting parameters used for the input.
//width is used in cout << setw(bw)
//prec is used in cout << fixed << setprecision(prec)
//width=6 and prec = 2 are default values
void Matrix::print( unsigned short width, unsigned short prec ) const {
    for(size_type i = 0; i < nrow; i++) {
        for(size_type j = 0; j < ncol; j++) {
            cout << setw(width) << fixed << setprecision(prec) << values[i][j];
        }
        cout << endl;
    }
}

//returns true if the matrix is empty
bool Matrix::empty() const {
    if(nrow == 0 && ncol == 0) return true;
    else return false;
}

//resizing matrix to n x m
void Matrix::resize( size_type n, size_type m ) {
    if(int(n) < 0 || int(m) < 0) {
        cout << "Invalid resize";
        return;
    }
    this->values.resize(n);
    for(unsigned i = 0; i < values.size(); i++) {
        this->values[i].resize(m);
    }
}

//needed for overloading << operator which uses print()
ostream & operator<<( ostream& os, const Matrix & A ) {
    A.print(8, 2);
    return os;
}


int main() {
    string ctnuestr;
    bool ctnue = true;
    string filename;
    string input_constants;
    
    while(ctnue) {
        cout << "Enter the file name containing matrix A values: ";
        getline(cin, filename);
        filename = "m1.txt";
        Matrix A(filename);

        cout << "Enter the file name containing matrix B values: ";
        getline(cin, filename);
        filename = "m2.txt";
        Matrix B(filename);

        cout << "\nPrinting A values:" << endl;
        cout << A << endl;

        cout << "Printing B values:" << endl;
        cout << B << endl;
        
        cout << "------------------------" << endl;
        cout << "Computation of S=A+B" << endl;
        cout << "------------------------" << endl;
        cout << "Printing S values:" << endl;
        Matrix S = A+B;
        cout << S << endl;

        cout << "------------------------" << endl;
        cout << "Computation of D=A-B" << endl;
        cout << "------------------------" << endl;
        cout << "Printing D values:" << endl;
        Matrix D = A-B;
        cout << D << endl;

        cout << "------------------------" << endl;
        cout << "Computation of P=A*B" << endl;
        cout << "------------------------" << endl;
        cout << "Printing P values:" << endl;
        Matrix P = A*B;
        cout << P << endl;

        cout << "------------------------" << endl;
        cout << "Computation of M=A*c+B*d" << endl;
        cout << "------------------------" << endl;
        cout << "\nEnter two floating point numbers c and d: ";
        double c;
        double d;
        getline(cin, input_constants);
        stringstream ss(input_constants);
        ss >> c >> d;
        cout << "\nPrinting M values:" << endl;
        Matrix M = A*c + B*d;
        cout << M << endl;

        cout << "------------------------" << endl;
        cout << "Computation of b=A*x" << endl;
        cout << "------------------------" << endl;
        cout << "\nEnter components of Vector x of length 3: ";
        double x1;
        double x2;
        double x3;
        getline(cin, input_constants);
        stringstream ss2(input_constants);
        ss2 >> x1 >> x2 >> x3;
        cout << "\nPrinting b values: " << endl;
        vector<double> x{x1, x2, x3};
        Matrix b = A*x;
        cout << b << endl;
        
        // ask if continue
        cout << "Continue? <y/n> ";
        cin >> ctnuestr;
        cin.ignore(256, '\n');
        cout << endl;
        if(ctnuestr == "n") ctnue = false;
    }
}
