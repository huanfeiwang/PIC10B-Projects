#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

using namespace std;

template<typename Type>
void print(Type & v, const string & sep = " ")
{
    typename Type::iterator it;
    for (it = v.begin(); it != v.end(); ++it)
    {
        cout << *it;
        
        typename Type::iterator it_next = it;
        it_next++;
        
        if (it_next != v.end()) cout << sep;
    }
    cout << endl;
}

vector<int> merge(const vector<int> & a, const vector<int> & b)
{

    vector<int>::size_type i1 = 0, i2 = 0, k = 0;
    vector<int>::size_type size = a.size() + b.size();
    vector<int> result(size);
    
    while(i1 <= a.size()-1 && i2 <= b.size()-1) {
        if(a[i1] < b[i2]) {
            result[k] = a[i1];
            i1++;
        } else {
            result[k] = b[i2];
            i2++;
        }
        k++;
    }
    
    while(i1 <= a.size()-1) {
        result[k] = a[i1];
        i1++;
        k++;
    }
    
    while(i2 <= b.size()-1) {
        result[k] = b[i2];
        i2++;
        k++;
    }
    
    return result;
}

vector<int> merge_sort(vector<int> & a)
{
    if (a.size() == 1) return a;
    int mid = a.size() / 2;
    
    vector<int> left(a.begin(), a.begin() + mid);
    vector<int> right(a.begin() + mid, a.end());
    
    left = merge_sort(left);
    right = merge_sort(right);
    
    vector<int> r = merge(left, right);
    print(r);
    return r;
}

int main()
{
    vector<int> v = { 1,3,6,2,6,2,3,4,5,6,7 };
    vector<int> v1 = { 1,3,5 };
    vector<int> v2 = { 2,4,6 };
    vector<int> r = merge(v1, v2);
    print(r);
    v = merge_sort(v);
    print(v);
}
