//
//  hmw_6_3.cpp
//
//  Created by Rui Yan on 2019/3/9.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <string>
#include <iostream>
#include <stack>

using namespace std;

// function to check if paranthesis are balanced
int is_nested(string S)
{
    stack<char> s;
    char x;

    // Traversing the Session
    for (int i=0; i<S.length(); i++)
    {
        if (S[i]=='('||S[i]=='['||S[i]=='{')
        {
            // Push the element in the stack
            s.push(S[i]);
            continue;
        }

        // IF current current character is not opening
        // bracket, then it must be closing. So stack
        // cannot be empty at this point.
        if (s.empty())
            return 0;

        switch (S[i])
        {
            case ')':

                // Store the top element in a
                x = s.top();
                s.pop();
                if (x=='{' || x=='[')
                    return 0;
                break;

            case '}':

                // Store the top element in b
                x = s.top();
                s.pop();
                if (x=='(' || x=='[')
                    return 0;
                break;

            case ']':

                // Store the top element in c
                x = s.top();
                s.pop();
                if (x =='(' || x == '{')
                    return 0;
                break;
        }
    }

    // Check Empty Stack
    return (s.empty());
}

// Driver program to test above function
int main()
{
    bool ctnue = true;           // boolean to determine whether continue
    string ctnuestr;             // input string to determine whether continue
    while (ctnue) {
        string S;                // store input string S

        cout << "Enter a string: ";
        getline(cin, S);
        if(is_nested(S) == 1){
            cout << "String " << S << "is properly nested." << endl;
        }else{
            cout << "String " << S << "is NOT properly nested." << endl;
        }

        // ask for continue or not
        cout << "\nContinue y/n? ";
        cin >> ctnuestr;
        cin.ignore(1000, '\n');
        cout << endl;

        if (ctnuestr == "n")    ctnue = false;
    }
    system("pause");
    return 0;
}
