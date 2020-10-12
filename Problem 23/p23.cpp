//
// Created by Cédric Goffin on 2020-10-11.
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <numeric>
#include "../utils/math.h"

/*
 * Problem 23:
 *
 * A perfect number is a number for which the sum of its proper divisors is exactly
 * equal to the number. For example, the sum of the proper divisors of 28 would be
 * 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
 *
 * A number n is called deficient if the sum of its proper divisors is less than n
 * and it is called abundant if this sum exceeds n.
 *
 * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number
 * that can be written as the sum of two abundant numbers is 24. By mathematical analysis,
 * it can be shown that all integers greater than 28123 can be written as the sum of
 * two abundant numbers. However, this upper limit cannot be reduced any further by
 * analysis even though it is known that the greatest number that cannot be expressed
 * as the sum of two abundant numbers is less than this limit.
 *
 * Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
 */


bool isAbundant(int number) {
    // Initialize Variables
    std::vector<int> equalDivisors = getEqualDivisors(number);

    // Check if sum of divisors is greater than number
    return std::accumulate(equalDivisors.begin(), equalDivisors.end(), 0) > number;
}

int main() {
    // Start benchmark
    auto start = std::chrono::system_clock::now();

    // Initialize variables
    int max = 28123, smallestAbundant = 12;
    std::vector<int> abundantNumbers = {smallestAbundant}; // Add smallest abundant number
    std::unordered_map<int, bool> sumNumbers;

    // Populate sumNumbers [1, max] with false
    for (int i = 1; i <= max; ++i) {
        sumNumbers.emplace(i, false);
    }

    // Calculate all abundant numbers smaller than max - smallest abundant number
    for (int i = 12 + 1; i <= max - smallestAbundant; ++i) {
        // If number is abundant, add to abundantNumbers vector
        if (isAbundant(i)) abundantNumbers.push_back(i);
    }

    // Set entries in sumNumbers that are sum of 2 abundant numbers to true
    for (int i = 0; i < abundantNumbers.size(); ++i)
        for (int j = i; j < abundantNumbers.size() && abundantNumbers[i] + abundantNumbers[j] <= max; ++j)
            sumNumbers.find(abundantNumbers[i] + abundantNumbers[j])->second = true;

    // Calculate sum of keys in sumNumbers that have a value of false
    int sum = std::accumulate(std::begin(sumNumbers), std::end(sumNumbers), 0,
                              [sumNumbers](int acc, std::pair<int, bool> pair) {
                                  return acc + ((!pair.second) ? pair.first : 0);
                              });

    // Print solution
    printf("Solution problem 23: %d", sum);

    // Print benchmark
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "\n\nelapsed time: " << elapsed_seconds.count() << "s\n";
}