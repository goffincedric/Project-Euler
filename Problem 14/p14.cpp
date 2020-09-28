//
// Created by Cédric Goffin on 2020-09-28.
//

#include <iostream>
#include <map>
#include <unordered_map>

/*
 * Problem 14:
 *
 * The following iterative sequence is defined for the set of positive integers:
 *      n → n/2 (n is even)
 *      n → 3n + 1 (n is odd)
 * Using the rule above and starting with 13, we generate the following sequence:
 *      13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
 * It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
 *
 * Which starting number, under one million, produces the longest chain?
 * NOTE: Once the chain starts the terms are allowed to go above one million.
 */

int main() {
    // Start benchmark
    auto start = std::chrono::system_clock::now();

    // Initialize variables
    long largestChain = 0,
            largestNumber = 0,
            currentChain,
            currentBeginNumber,
            currentNumber;
    std::unordered_map<long, long> chainLengths;

    // Loop over all numbers under one million
    for (long i = 1; i < 1000000; ++i) {
        currentNumber = i;
        currentBeginNumber = i;
        currentChain = 1;

        // Follow chain of current number
        auto finder = chainLengths.find(currentNumber);
        while (currentNumber > 1 && finder == chainLengths.end()) {
            // Update currentNumber
            if (currentNumber % 2 == 0) {
                currentNumber /= 2;
            } else {
                currentNumber *= 3;
                currentNumber += 1;
            }

            // Increment currentChain
            ++currentChain;

            // Check if current number is already part of previously checked chain
            finder = chainLengths.find(currentNumber);
        }

        // Check if loop stopped because a previous chain was found
        if (finder != chainLengths.end()) {
            // Add length of found chain to current chain
            currentChain += finder->second;
        }

        // Check if current chain is largest found yet
        if (currentChain >= largestChain) {
            // Set largest chain variables
            largestNumber = currentBeginNumber;
            largestChain = currentChain;
        }

        // Add length of current chain to chain lengths map
        chainLengths.insert({currentBeginNumber, currentChain});
    }

    // Print solution
    std::printf("Solution problem 14: Number %ld produced the largest chain with %ld numbers\n", largestNumber,
                largestChain);


    // Print benchmark
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}