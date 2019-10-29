//
//  main.cpp
//  test
//
//  Created by Rui Yan on 2019/3/14.
//  Copyright © 2019 Rui Yan. All rights reserved.
//
#include <iostream>
#include <vector>
#include <list>

using namespace std;

void modify(list<int> & lst)
{
    list<int>::iterator it = lst.begin();
    while(it != lst.end())
    {
        if ( (*it)%2 )
            it++;
        else
            it = lst.erase(it);
    }
}
int main()
{
    list<int> lst = { 1, -2, 3, -4, 5, -6, 6, 7 };
    modify(lst);
    for(list<int>::iterator it = lst.begin(); it != lst.end(); ++it )
        cout << *it;
}
