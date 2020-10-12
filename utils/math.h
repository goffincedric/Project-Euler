//
// Created by Cédric Goffin on 2020-10-08.
//

#include <deque>


#ifndef PROJECT_EULER_MATH_H
#define PROJECT_EULER_MATH_H

int factorial(int number);

std::vector<int> getEqualDivisors(int number);

void multiplyLarge(std::deque<long> &numbers, long factor);

#endif //PROJECT_EULER_MATH_H
