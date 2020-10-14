//
// Created by Cédric Goffin on 2020-10-08.
//

#include <deque>
#include <climits>


#ifndef PROJECT_EULER_MATH_H
#define PROJECT_EULER_MATH_H

const long MAX_ADDITION_NUMBER = LONG_MAX - 9l;
const long MAX_MULTIPLICATION_NUMBER = LONG_MAX / 10l;

int factorial(int number);

std::vector<int> getEqualDivisors(int number);

void addLarge(std::deque<long> &number, long addend);
void addLarge(std::deque<long> &number, std::deque<long> &addend);

void multiplyLarge(std::deque<long> &number, long factor);

#endif //PROJECT_EULER_MATH_H
