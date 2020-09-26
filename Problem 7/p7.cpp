//
// Created by Cédric Goffin on 2020-09-24.
//
#include <iostream>
#include <cmath>

using namespace std;

/*
 * Problem 7:
 *
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
 * What is the 10 001st prime number?
 */

bool isPrime(long number) {
    if (number == 2 || number == 3) return true;
    if (number % 2 == 0) {
        return false;
    }

    int max = (int) ceil(sqrt(number));
    if (max < 3) max = 3;

    for (int i = 3; i <= max; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    long prime = 0;
    int primesFound = 0;
    bool numberIsPrime;
    for (long i = 2; primesFound < 10001; i++) {
        numberIsPrime = isPrime(i);
        if (numberIsPrime) {
            primesFound++;
            prime = i;
        }
    }

    printf("Solution problem 7: %ld", prime);
}