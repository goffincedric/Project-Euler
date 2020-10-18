//
// Created by Cédric Goffin on 2020-10-18.
//

#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>
#include <numeric>
#include <sstream>
#include "../utils/math.h"

/*
 * Problem 27:
 *
 * Euler discovered the remarkable quadratic formula:
 *
 *              n^2 + n + 41
 *
 * It turns out that the formula will produce 40 primes for the consecutive integer values 0 ≤ n ≤ 41.
 * However, when n = 40, 40^2 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when
 * n = 41, 41^2 + 41 + 41 is clearly divisible by 41.
 *
 * The incredible formula n^2 + -79n + 1601 was discovered, which produces 80 primes for the consecutive
 * values 0 ≤ n ≤ 79. The product of the coefficients, −79 and 1601, is −126479.
 *
 * Considering quadratics of the form:
 *
 *              n^2 + an + b, where |a| < 1000 and |b| ≤ 1000
 *
 *              where |n| is the modulus/absolute value of n
 *              e.g. |11| = 11 and |-4| = 4
 *
 * Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum
 * number of primes for consecutive values of n, starting with n = 0.
 */

int main() {
    // Initialize variables
    int a, b, n, largestN = 0;
    std::vector<long> primes, consecutivePrimes, largestConsecutivePrimes;
    std::pair<long, long> largestPrimePair;

    // Calculate primes
    primes = findPrimes(1000);

    // Loop over all primes
    for (long &primeB: primes) {
        // Set b equal to current primeB
        b = primeB;
        for (long &primeA: primes) {
            // Set a equal to current primeA
            a = primeA;

            // Loop over positive and negative a
            for (int i = 0; i < 2; ++i) {
                // Loop over positive and negative b
                for (int j = 0; j < 2; ++j) {
                    // Reset state
                    n = 0;
                    consecutivePrimes.clear();

                    // Check if equation with current n is a prime
                    while (isPrime((long) pow(n, 2) + a * n + b)) {
                        if (a == -61 && b == 971) std::cout << (long) pow(n, 2) + a * n + b << " ";
                        consecutivePrimes.push_back((long) pow(n, 2) + a * n + b); // Add prime to consecutivePrimes
                        ++n; // Increment n by one
                    }
                    if (a == -61 && b == 971) std::cout << "\n\n";

                    // Check if n is larger than previous consecutive primes
                    if (n > largestN) {
                        largestPrimePair = std::make_pair(a, b);
                        largestN = n;
                        largestConsecutivePrimes = consecutivePrimes;
                    }

                    // Switch a from - => + or + -> -
                    a *= -1;
                }
                // Switch b from - => + or + -> -
                b *= -1;
            }
        }
    }

    // Print solution
    std::stringstream primesString;
    for (long largestConsecutivePrime : largestConsecutivePrimes){
        if (primesString.str().size() % 100 > 95) primesString << "\n\t";
        primesString << largestConsecutivePrime << " ";
    }
    printf("Solution problem 27: %ld\n\n"
           "The equation f(n) = n² + a * n + b, where a = %ld, b = %ld, produces %d primes for the consecutive values 0 ≤ n ≤ %d:\n"
           "\n\t%s\n",
           largestPrimePair.first * largestPrimePair.second,
           largestPrimePair.first, largestPrimePair.second,
           largestN, largestN - 1,
           primesString.str().c_str()
    );
}