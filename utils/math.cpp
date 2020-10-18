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

// Function checks if the argument is a prime
bool isPrime(long number) {
    if (number <= 1) return false;
    if (number == 2 || number == 3) return true;
    if (number % 2 == 0) {
        return false;
    }

    int max = (int) ceil(sqrt(number));
    if (max < 3) max = 3;

    for (int i = 3; i <= max; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

// Function that finds primes using Sieve of Eratosthenes
std::vector<long> findPrimes(int max) {
    // Initialize variables
    std::vector<bool> sieve(max, true);
    std::vector<long> primes;
    sieve[0] = false; // Set 1 as false (not a prime)

    // Sieve of Eratosthenes
    int prime;
    for (long i = 1; i < sieve.size(); ++i) {
        if (!sieve[i]) {
            continue;
        }

        // Calculate number and add to primes
        prime = i + 1;
        primes.push_back(prime);

        // Set all multiplications of prime in sieve to false
        for (long j = (long) pow(prime, 2) - 1; j < sieve.size(); j += prime) {
            sieve[j] = false;
        }
    }

    // Return primes
    return primes;
}

// Calculates all equal divisors of given number
std::vector<long> getEqualDivisors(long number) {
    // Initialize Variables
    std::vector<long> equalDivisors = {1}; // 1 is always equal divisor
    long max = ceil(number / 2);

    // Loop over all numbers => ]1, max]
    for (long i = 2; i <= max; ++i) {
        // Check if is equal divisor
        if (number % i == 0)
            equalDivisors.push_back(i);
    }

    // Return found equal divisors
    return equalDivisors;
}

// Calculate a fraction with defined decimal fraction precision
std::pair<std::vector<long>, std::vector<long>> calculateFraction(long numerator, long denominator, long precision) {
    // Initialize variables
    long currentPrecision = 0;
    std::vector<long> integralPart, fractionPart;

    // Convert numerator to vector of numbers
    std::vector<long> numeratorDigits;
    for (auto &digit :  std::to_string(numerator)) numeratorDigits.push_back(digit - '0');

    // Loop over digits in numerator
    long wholeNumber, currentNumerator = 0;
    currentPrecision = -numeratorDigits.size();
    for (int i = 0; i < numeratorDigits.size(); ++i) {
        // Set currentNumerator
        currentNumerator = currentNumerator * 10 + numeratorDigits[i];

        // Calculate integral/fraction part
        wholeNumber = currentNumerator / denominator;
        if (currentPrecision >= 0) fractionPart.push_back(wholeNumber);
        else integralPart.push_back(wholeNumber);

        // Calculate next currentNumerator
        wholeNumber *= denominator;
        currentNumerator -= wholeNumber;

        // Increment currentPrecision by one
        ++currentPrecision;

        // Precision check
        if (currentPrecision == precision) break;
        // Check if zero needs to be added to back of numeratorDigits
        if (currentPrecision >= 0) numeratorDigits.push_back(0);
    }

    // Remove leading zeroes in integralPart
    while (integralPart[0] == 0 && integralPart.size() > 1) integralPart.erase(integralPart.begin());

    // Return integral and fraction parts of decimal in pair
    return std::make_pair(integralPart, fractionPart);
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
