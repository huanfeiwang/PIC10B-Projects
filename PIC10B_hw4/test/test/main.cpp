//
//  main.cpp
//  test
//
//  Created by Rui Yan on 2019/2/17.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void RecSubsets(string soFar, string rest) {
    // First print out "a" or wherever we are up to
    // This ensures we correctly get "ab" and "ac" without trailing characters etc
    // Now print out the other combinations that begin with soFar
    // This part of your algorithm was already correct :)
    for (int i = 0; i < rest.length(); i++) {
        // cout << "i is " << i << endl;
        string next = soFar + rest[i];
        string remaining = rest.substr(i+1);
        // cout << "next is " << next << endl;
        // cout << "remaining is " << remaining << endl;
        
        RecSubsets(next, remaining);
    }
    if( soFar.size() > 0 ) cout << soFar << endl;
}


void CanMakeSum(string set)
{
    RecSubsets("", set);
    // Don't call it a second time here
}

void subString(string str, int n)
{
    // Pick starting point
    for (int len = 1; len <= n; len++)
    {
        // Pick ending point
        for (int i = 0; i <= n - len; i++)
        {
            // Print characters from current
            // starting point to current ending
            // point.
            string sub = "";
            int j = i + len - 1;
            for (int k = i; k <= j; k++)
                sub = sub + str[k];
            
            cout << sub << endl;
        }
    }
}


vector<string> generate_permutations(string word)
{
    vector<string> result;
    
    //special cases
    
    if (word.length() <= 1)
    {    result.push_back(word);
        return result;    }
    
    //general case
    for (int i = 0; i < word.length(); i++)
    {
        string shorter_word = word.substr(0, i)    + word.substr(i + 1);
        cout << "shorter_word = " << shorter_word << endl;
        
        vector<string> shorter_permutations = generate_permutations(shorter_word);
        
        for (int j = 0; j < shorter_permutations.size(); j++)
        {
            string longer_word = word[i] + shorter_permutations[j];
            result.push_back(longer_word);
        }
        
    }
    return result;
}


int main() {
    string str = "1234";

    vector<string> result = generate_permutations(str);
    for(int i = 0; i < result.size() ; i++) {
        cout << "\"" << result[i] << "\"" << endl;
    }
    //CanMakeSum(str);
    
}
