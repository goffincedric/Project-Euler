//
// Created by Cédric Goffin on 2020-09-23.
//


#include <iostream>

/*
 * Problem 2:
 *
 * Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms will be:
 *      1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
 * By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
 */
int main() {
    int max = 4000000,
            a = 0,
            b = 1,
            solution = 0,
            temp = 0;

    while (b < max) {
        temp = a + b;
        if (temp % 2 == 0) {
            solution += temp;
        }
        a = b;
        b = temp;
    }

    std::cout << "Solution problem 2: " << solution;
}