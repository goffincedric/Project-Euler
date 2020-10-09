//
// Created by Cédric Goffin on 2020-10-08.
//

#include "math.h"

#include <deque>

using namespace std;


// Function used to multiply large numbers
void multiplyLarge(deque<long> &numbers, long factor) {
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
