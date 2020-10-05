//
// Created by Cédric Goffin on 2020-10-01.
//

#include <iostream>
#include <deque>
#include <numeric>

using namespace std;

/*
 * Problem 16:
 *
 * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 * What is the sum of the digits of the number 2^1000?
 */

void printSteps(int base, int exponent, int exponentDivider) {
    // Print amount of multiplications
    printf("%d^%d in %d multiplications\n", base, exponent, exponentDivider);

    // Print multiplication of smaller powers
    string calculation = " = ";
    for (int j = 0; j < exponentDivider; ++j) {
        calculation += "2^" + to_string(exponent / exponentDivider) + " * ";
    }
    calculation.erase(calculation.cend() - 3, calculation.cend());
    cout << calculation << endl;

    // Print multiplication of calculated powers
    long power = (long) pow(base, exponent / exponentDivider);
    printf(" = %ld * %ld * %ld * ... * %ld * %ld\n", power, power, power, power, power);

    // Print result according to pow function
    printf(" (according to built-in c++ pow function)\n = %s\n", to_string(pow(base, exponent)).c_str());
}

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
    while (numbers[index - offset] > 9) {
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
    }
}

long multiplySmall(long number, int times) {
    long product = 1;
    for (int i = 0; i < times; ++i) {
        product *= number;
    }
    return product;
}

int main() {
    // 2^1000 = 2*2*2*2*2*2*......*2
    // Of binary operator (1000* bitwise left <<)
    // Initialize variables
    int base = 2,
            exponent = 1000,
            exponentDivider = 1;
    deque<long> numbers = {1};

    // Check for result smallest exponent with no remainder
    while ((long) pow(base, exponent / exponentDivider) < 0 || exponent % exponentDivider != 0) {
        exponentDivider += 1;
    }

    // Print steps of multiplication
    printSteps(base, exponent, exponentDivider);

    // Calculate the power
    long factor;
    for (int i = 0; i < exponentDivider; ++i) {
        factor = multiplySmall(base, exponent / exponentDivider);
        multiplyLarge(numbers, factor);
    }

    // Print own solution
    printf("\nOwn product of %d^%d\n = ", base, exponent);
    for (auto &num: numbers)
        cout << num;
    cout << endl << endl;

    // Calculate sum of numbers
    long sum = accumulate(numbers.begin(), numbers.end(), 0, [](long i, long j) {
        return i + j;
    });

    // Print solution
    printf("Solution problem 16: %ld\n", sum);
}
