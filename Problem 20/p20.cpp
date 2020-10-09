//
// Created by Cédric Goffin on 2020-10-08.
//

#include "../utils/math.h"
#include <iostream>
#include <deque>
#include <sstream>

using namespace std;

/*
 * Problem 20:
 *
 * n! means n × (n − 1) × ... × 3 × 2 × 1
 *
 * For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
 * and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
 *
 * Find the sum of the digits in the number 100!
 */

int main() {
    // Initialize variables
    int factorial = 100, sum = 0;
    deque<long> result = {1};

    // Calculate factorial
    for (int i = factorial; i > 0; --i)
        multiplyLarge(result, i);

    // Add numbers of result together
    ostringstream oss;
    for (long &num : result) {
        sum += num;
        oss << num;
    }

    // Print solution
    printf("Solution problem 20:\n Sum of digits in number %s\n = %d", oss.str().c_str(), sum);
}