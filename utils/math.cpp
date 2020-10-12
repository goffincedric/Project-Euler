//
// Created by Cédric Goffin on 2020-10-08.
//

#include "math.h"

#include <deque>
#include <vector>

// Calculate factorial
int factorial(int number) {
    int factorial = 1;
    for (int i = number; i > 1; --i)
        factorial *= i;

    return factorial;
}

// Calculates all equal divisors of given number
std::vector<int> getEqualDivisors(int number) {
    // Initialize Variables
    std::vector<int> equalDivisors = {1}; // 1 is always equal divisor
    int max = ceil(number / 2);

    // Loop over all numbers => ]1, max]
    for (int i = 2; i <= max; ++i) {
        // Check if is equal divisor
        if (number % i == 0)
            equalDivisors.push_back(i);
    }

    // Return found equal divisors
    return equalDivisors;
}

// Function used to multiply large numbers
void multiplyLarge(std::deque<long> &numbers, long factor) {
    // Multiply each number by the factor and carry extra to next number
    for (auto &num: numbers) {
        // Multiply number by factor
        num *= factor;
    }

    // Check if numbers need to be carried
    int index = numbers.size() - 1,
            offset = 0;
    long carry = 0;
    while (numbers[index - offset] > 9 || index - offset > 0) {
        if (numbers[index - offset] > 9) {
            // Check if number needs to be added to front of numbers queue
            if (index - offset - 1 < 0) {
                numbers.push_front(0);
                index++;
            }

            // Set carry int
            carry = (long) trunc(numbers[index - offset] / 10);

            // Set current number
            numbers[index - offset] = numbers[index - offset] % 10;

            // increment offset by one
            offset++;

            // Add carry to next number in list
            numbers[index - offset] += carry;
        } else {
            // increment offset by one
            offset++;
        }
    }
}
