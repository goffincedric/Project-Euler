//
// Created by Cédric Goffin on 2020-09-23.
//

#include <list>
#include <iostream>

using namespace std;

/*
 * Problem 3:
 *
 * The prime factors of 13195 are 5, 7, 13 and 29.
 * What is the largest prime factor of the number 600851475143?
 */

bool isPrime(long number) {
    if (number == 2) {
        return true;
    }

    long denominator = 3L;
    while (number % denominator > 0 && denominator < number){
        denominator += 2;
    }
    return denominator == number;
}

int main() {
    long result = 600851475143L;
    long currentResult = result;
    long largestPrime = 0L;

    for (long i = 2L; currentResult > 1; ++i) {
        if (isPrime(i)) {
            if (currentResult % i == 0) {
                cout << "Prime: " << i << "\n";
                largestPrime = i;
                currentResult /= i;
            }
        }
    }

    cout << "Solution problem 3: " << largestPrime;
}
