//
// Created by Cédric Goffin on 2020-09-24.
//

#include <iostream>
#include<cmath>

using namespace std;

/*
 * Problem 6:
 *
 * The sum of the squares of the first ten natural numbers is,
 *          1^2 + 2^2 + 3^2 + ... + 10^2 = 385
 * The square of the sum of the first ten natural numbers is,
 *          (1+2+3+...+10)^2 = 55^2 = 3025
 * Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is
 *          3025 - 385 = 2640
 *
 * Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
 */

int sumOfSquares(int number) {
    int sum = 0;

    for (int i = 1; i <= number; ++i) {
        sum += (int) pow((double) i, (double) 2);
    }

    return sum;
}

int squareOfSum(int number) {
    int square = 0;

    for (int i = 1; i <= number; ++i) {
        square += i;
    }

    return (int) pow((double) square, (double) 2);
}

int main() {
    int difference = squareOfSum(100) - sumOfSquares(100);
    printf("Solution problem 6: %d", difference);
}