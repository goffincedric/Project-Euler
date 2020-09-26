//
// Created by Cédric Goffin on 2020-09-25.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

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
    vector<bool> sieve(2000000, true);
    sieve[0] = false; // Set 1 as false (not a prime)
    vector<long> primes;

    // Sieve of Eratosthenes
    for (long i = 1; i < sieve.size(); ++i) {
        if (!sieve[i]) {
            continue;
        }

        // Calculate number and add to primes
        int prime = i + 1;
        primes.push_back(prime);

        // Set all multiplications of prime in sieve to false
        for (long j = (long) pow(prime, 2) - 1; j < sieve.size(); j += prime) {
            sieve[j] = false;
        }
    }

    printf("Solution problem 10: %ld", sum(primes));
}