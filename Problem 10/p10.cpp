//
// Created by Cédric Goffin on 2020-09-25.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include "../utils/math.h"

using namespace std;

/*
 * Problem 10:
 *
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 * Find the sum of all the primes below two million.
 */

long sum(vector<long> &numbers) {
    long sum = 0;
    for (long &number : numbers) {
        sum += number;
    }
    return sum;
}

int main() {
    // Initialize variables
    long max = 2000000;
    vector<long> primes;

    // Find primes
    primes = findPrimes(max);

    // Print solution
    printf("Solution problem 10: %ld", sum(primes));
}