//
// Created by Cédric Goffin on 2020-10-15.
//

#include <iostream>
#include <vector>
#include "../utils/math.h"

/*
 * Problem 26:
 *
 * A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:
 *
 *           1/2	= 	0.5
 *           1/3	= 	0.(3)
 *           1/4	= 	0.25
 *           1/5	= 	0.2
 *           1/6	= 	0.1(6)
 *           1/7	= 	0.(142857)
 *           1/8	= 	0.125
 *           1/9	= 	0.(1)
 *           1/10	= 	0.1
 *
 * Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.
 *
 * Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
 */

/*
 * Explanation:
 *
 * Find largest prime p. Check if prime has p-1 repeating digits in decimal fraction part.
 * If not, find second largest prime p, continue...
 */

int checkRepeatingDigitGroups(std::vector<long> fractionalPart) {
    // Initialize variables
    int length = 0, groupSize = 0, groupOffset;
    bool isRepeating = false;
    std::vector<long> first, second;

    // Check for repeating digits in fraction part
    while (!isRepeating && groupSize <= fractionalPart.size() / 2) {
        // Increment groupSize by one
        ++groupSize;

        if (groupSize == 166) {

        }

        // Set first and second part of fractional part
        first = std::vector<long>(fractionalPart.begin(), fractionalPart.begin() + groupSize);
        second = std::vector<long>(fractionalPart.begin() + groupSize, fractionalPart.begin() + groupSize * 2);

        // Set isRepeating to equality check
        isRepeating = first == second;

        // Check if keeps repeating
        groupOffset = 2;
        while (isRepeating && groupSize * groupOffset <= fractionalPart.size() / 2) {
            // Set first and second part of fractional part with new group offset
            first = std::vector<long>(fractionalPart.begin() + groupSize * (groupOffset - 2),
                                      fractionalPart.begin() + groupSize * (groupOffset - 1));
            second = std::vector<long>(fractionalPart.begin() + groupSize * (groupOffset - 1),
                                       fractionalPart.begin() + groupSize * groupOffset);

            // Set isRepeating to equality check
            isRepeating = first == second;

            // Increment groupOffset by one
            groupOffset++;
        }
    }

    // Check if isRepeating
    if (isRepeating)
        length = groupSize; // Set new length

    return length;
}

int main() {
    // Initialize variables
    long max = 1000, largestPrime, largestUnitFraction = 0;
    std::vector<long> primes;
    int length = 0;

    // Find primes and reverse
    primes = findPrimes(max);
    std::reverse(primes.begin(), primes.end());

    // Set largest prime
    largestPrime = primes[0];

    // Loop over primes and check if prime length is largest
    std::pair<std::vector<long>, std::vector<long>> decimal;
    int groupSize;
    while (!primes.empty()) {
        // Calculate unit fraction of prime with double expected precision
        decimal = calculateFraction(1, primes[0], (primes[0] - 1) * 2);

        // Check for repeating digits in fraction part
        groupSize = checkRepeatingDigitGroups(decimal.second);

        // Check if groupSize > length
        if (length <= groupSize) {
            length = groupSize; // Set length to higher groupSize
            largestUnitFraction = primes[0]; // Set largestUnitFraction to current prime
        }
        // Remove first prime
        primes.erase(primes.begin());
    }


    // Check if unit fractions of numbers between largestPrime and max have higher repeating fraction parts
    for (int i = largestPrime + 1; i < max; ++i) {
        // Calculate unit fraction of prime with double expected precision
        decimal = calculateFraction(1, i, i * 2);

        // Check for repeating digits in fraction part
        groupSize = checkRepeatingDigitGroups(decimal.second);

        // Check if groupSize > length
        if (length <= groupSize) {
            // Set new length
            length = groupSize;

            // Set largestUnitFraction to current number
            largestUnitFraction = i;
        }
    }

    // Print solution
    printf("Problem solution 26: Unit fraction %d/%ld has decimal length of %d\n", 1, largestUnitFraction, length);
    printf("\t%d/%ld = ", 1, largestUnitFraction);
    decimal = calculateFraction(1, largestUnitFraction, length);
    for (long &digit: decimal.first) printf("%ld", digit);
    printf(",");
    for (long &digit: decimal.second) printf("%ld", digit);
}