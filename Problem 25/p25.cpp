//
// Created by Cédric Goffin on 2020-10-12.
//

#include <iostream>
#include <deque>
#include "../utils/math.h"

/*
 * Problem 25:
 *
 * The Fibonacci sequence is defined by the recurrence relation:
 *
 *      Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
 *
 * Hence the first 12 terms will be:
 *
 *      F1 = 1
 *      F2 = 1
 *      F3 = 2
 *      F4 = 3
 *      F5 = 5
 *      F6 = 8
 *      F7 = 13
 *      F8 = 21
 *      F9 = 34
 *      F10 = 55
 *      F11 = 89
 *      F12 = 144
 *
 * The 12th term, F12, is the first term to contain three digits.
 *
 * What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
 */

int main() {
    // Start benchmark
    auto start = std::chrono::system_clock::now();

    // Initialize variables
    std::deque<long> currentFib = {1}, previousFib = {1}, temp;
    int index = 2;

    // Loop until currentFib reaches size of 1000
    while (currentFib.size() < 1000) {
        // Copy currentFib to temp
        temp = currentFib;

        // Add previousFib to currentFib
        addLarge(currentFib, previousFib);

        // Copy temp to previousFib
        previousFib = temp;

        // Increment index by one
        index++;
    }

    // Print solution
    printf("Solution problem 25: \n\tIndex %d,\n\tNumber: ", index);
    for (long num: currentFib) printf("%ld", num);
    printf("\n");

    // Print benchmark
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "\n\nelapsed time: " << elapsed_seconds.count() << "s\n";
}