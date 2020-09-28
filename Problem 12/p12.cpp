//
// Created by Cédric Goffin on 2020-09-28.
//

#include <iostream>
#include <cmath>

using namespace std;

/*
 * Problem 12:
 *
 * The sequence of triangle numbers is generated by adding the natural numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:
 *      1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 * Let us list the factors of the first seven triangle numbers:
 *       1: 1
 *       3: 1,3
 *       6: 1,2,3,6
 *      10: 1,2,5,10
 *      15: 1,3,5,15
 *      21: 1,3,7,21
 *      28: 1,2,4,7,14,28
 * We can see that 28 is the first triangle number to have over five divisors.
 *
 * What is the value of the first triangle number to have over five hundred divisors?
 */

int checkDivisors(int number) {
    // Get middle divisor
    int square = ceil(sqrt(number));
    int divisors = 0;

    // Check all numbers for divisor
    for (int i = 1; i <= square; ++i) {
        if (number % i == 0) {
            divisors++;
        }
    }

    return divisors;
}

int main() {
    int index = 0,
            divisors,
            triangleNumber;

    do {
        triangleNumber = 0;
        index++;
        for (int i = 1; i < index + 1; ++i)
            triangleNumber += i;
        divisors = checkDivisors(triangleNumber) * 2;
    } while (divisors < 500);

    // Print solution
    printf("Solution problem 12: %d with %d divisors", triangleNumber, divisors);
}