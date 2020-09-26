//
// Created by Cédric Goffin on 2020-09-25.
//

#include <iostream>
#include <cmath>

using namespace std;

/*
 * Problem 9:
 *
 * A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
 *          a^2 + b^2 = c^2
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 52.
 * There exists exactly one Pythagorean triplet for which a + b + c = 1000.
 * Find the product abc.
 */

int main() {
    int a = 0, b = 0, c = 0;
    bool isComplete = false;

    for (int i = 3; !isComplete && i < 1000; ++i) {
        for (int j = 2; j < i && !isComplete; ++j) {
            for (int k = 1; k < j && !isComplete; ++k) {
                isComplete = k + j + i == 1000 &&
                             pow(k, 2) + pow(j, 2) == pow(i, 2);
                if (isComplete) {
                    a = k;
                    b = j;
                    c = i;
                }
            }
        }
    }

    if (a == 0 && b == 0 && c == 0) {
        cout << "No solution found";
        return 1;
    }

    printf("Solution problem 9: %d\n%d^2 + %d^2 = %d^2\n%d + %d + %d = 1000", a * b * c, a, b, c, a, b, c);
}