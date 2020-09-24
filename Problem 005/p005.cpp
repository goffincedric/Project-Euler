//
// Created by Cédric Goffin on 2020-09-24.
//

#include <iostream>

using namespace std;


/*
 * Problem 5:
 *
 * 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
 * What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
 */
int main() {
    int number = 0,
            largest = 0;

    for (int i = 20; number == 0; i += 20) {
        for (int j = 20; j != 1 && i % j == 0; --j) {
            largest = j;
        }
        if (largest == 2) {
            number = i;
        }
    }

    printf("Solution problem 5: %d", number);
}