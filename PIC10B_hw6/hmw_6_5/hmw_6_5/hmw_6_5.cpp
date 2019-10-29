//
//  hmw_6_5.cpp
//
//  Created by Rui Yan on 2019/3/9.
//  Copyright © 2019 Rui Yan. All rights reserved.
//

#include <iostream>
#include <set>
#include <ctime>
#include <math.h>
#include <time.h>

using namespace std;

// main function
int main() {
    int first;
    char check='y';
    while (check != 'n') {
        // ask input
        cout << "Enter any positive integer: ";
        cin >> first;
        set<int> numbers;
        set<int> root;

        for (int i = 1; i <= first; i++) {
            numbers.insert(i);
        }

        for (int i = 2; i <= sqrt(first); i++) {
            root.insert(i);
        }

        set<int>::iterator pos;
        set<int>::iterator post;
        int remove;

        for (pos=root.begin(); pos!=root.end(); pos++) {
            cout << "\nRemoving the elements divisible by " << *pos <<": "<< endl;
            for (remove=1; remove<=first; remove++)
                if (remove / *pos > 1 && remove % *pos == 0) {
                    numbers.erase(remove);
                }
            for (post = numbers.begin(); post != numbers.end(); post++)
                cout << *post << " ";
        }

        cout << "\nPrime numbers not exceeding " << first << ":" << endl;
        for (post = numbers.begin(); post != numbers.end(); post++)
            cout << *post << " ";

        cout << "\n\nContinue <y/n>? ";
        cin >> check;
        cout << endl;
    }

    // check the complexity of prime number computation algorithm.
    cout << "Complexity check for n = 10^4, 10^5, 10^6: " << endl;
	for (int f = 10000; f < 1000001; f *= 10) {
		clock_t tStart = clock();
		set<int> numbers;
		for (int i = 1; i <= f; i++) {
			numbers.insert(i);
		}
		for (int d=2; d<=sqrt(f); d++) {
			for (int i = 1; i <= f; i++)
				if (i > d && i%d == 0)
					numbers.erase(i);
		}
		double sec = (double)(clock() - tStart) / CLOCKS_PER_SEC;
		cout << "Time <sec> for computing primes not exceeding " << f << ": " << sec << endl;
    }
    system("pause");
    return 0;
}

