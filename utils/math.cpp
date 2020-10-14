//
// Created by Cédric Goffin on 2020-10-08.
//

#include "math.h"
#include <deque>
#include <vector>
#include <iostream>
#include <stack>

// Private function
void checkCarry(std::deque<long> &number) {
    // Check if numbers need to be carried
    int index = number.size() - 1,
            offset = 0,
            carryOffset;
    std::stack<long> carry;;
    while (index - offset >= 0) {
        if (number[index - offset] > 9) {
            // Check if number needs to be added to front of number queue
            if (index - offset - 1 < 0) {
                number.push_front(0);
                index++;
            }

            // Set carry stack
            for (auto &digit : std::to_string(number[index - offset] / 10))
                carry.push(digit - '0');

            // Set current number
            number[index - offset] = number[index - offset] % 10;

            // increment offset by one
            offset++;

            // Carry numbers to next digits in number
            carryOffset = 0;
            while (!carry.empty()) {
                // Check if number needs to be added to front of number queue
                if (index - offset - carryOffset < 0) {
                    number.push_front(0);
                    index++;
                }
                // Add carry to current double offset number
                number[index - offset - (carryOffset++)] += carry.top();

                // Remove carry number from stack
                carry.pop();
            }
        } else {
            // Increment offset by one
            offset++;
        }
    }
}

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

// Function used to add together large numbers
void addLarge(std::deque<long> &number, long addend) {
    // Check if addend is larger than allowed limit
    if (addend >= MAX_ADDITION_NUMBER) {
        // Split addend up in two parts
        addLarge(number, addend - MAX_ADDITION_NUMBER);

        // Set addend to max allowed number
        addend = MAX_ADDITION_NUMBER;
    }

    // Add addend to last number in number vector
    number[number.size() - 1] += addend;

    // Check if number need to be carried
    checkCarry(number);
}

void addLarge(std::deque<long> &number, std::deque<long> &addend) {
    // Check if number is smaller than addend and at 0 to front until they are same size
    while (number.size() < addend.size())
        number.push_front(0);

    // Add digits of addend to digits of number
    for (int i = 0; i < addend.size(); ++i)
        number[number.size() - 1 - i] += addend[addend.size() - 1 - i];

    // Check if number need to be carried
    checkCarry(number);
}

// Function used to multiply large numbers
void multiplyLarge(std::deque<long> &number, long factor) {
    // Check if factor is larger than allowed limit
    if (factor > MAX_MULTIPLICATION_NUMBER) {
        // Split factor into smaller factor, times and remainder
        long times = LONG_MAX / MAX_MULTIPLICATION_NUMBER,
                newFactor = factor / times,
                remainder = factor % MAX_MULTIPLICATION_NUMBER;

        // Store original number
        std::deque<long> originalNumber = number;

        // Multiply number by newFactor, by times
        multiplyLarge(number, newFactor);
        multiplyLarge(number, times);

        // Multiply originalNumber by remainder
        multiplyLarge(originalNumber, remainder);

        // Add number and originalNumber together
        addLarge(number, originalNumber);
    } else {
        // Multiply each number by the factor and carry extra to next number
        for (auto &num: number) {
            // Multiply number by factor
            num *= factor;
        }
    }

    // Check if number need to be carried
    checkCarry(number);
}
