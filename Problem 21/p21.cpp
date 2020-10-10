//
// Created by Cédric Goffin on 2020-10-09.
//

#include <iostream>
#include <vector>
#include <numeric>

/*
 * Problem 21:
 *
 * Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide
 * evenly into n). If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair
 * and each of a and b are called amicable numbers.
 *
 * For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110;
 * therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
 *
 * Evaluate the sum of all the amicable numbers under 10000.
 */

int sumOfDivisors(int number) {
    // Initialize sum variable with 1 (1 is always an even divisor)
    int sum = 1, max = std::ceil(number / 2);

    // Loop over all numbers smaller than sqrt of number
    for (int i = 2; i <= max; ++i) {
        // If i is even divisor of number, add to sum
        if (number % i == 0) {
            sum += i;
        }
    }

    // Return sum
    return sum;
}

int main() {
    // Initialize vector with numbers from 1 to 10000
    std::vector<int> numbers(10000), amicableNumbers;
    std::iota(numbers.begin(), numbers.end(), 1);
    int sum = 0;

    // Loop over all numbers
    int amicable;
    for (int &num : numbers) {
        // Get sum of even divisors of num
        amicable = sumOfDivisors(num);

        // Check if num && found amicable are different and amicable of amicable is same as num
        if (num != amicable && sumOfDivisors(amicable) == num) {
            // Delete amicable numbers from numbers and add to amicableNumbers
            amicableNumbers.push_back(num);
            amicableNumbers.push_back(amicable);
            numbers.erase(std::find(numbers.begin(), numbers.end(), amicable));

            // Print amicable numbers
            printf("Amicable numbers found: %d & %d\n", num, amicable);
        }
    }

    // Calculate sum of all amicable numbers
    sum = std::accumulate(amicableNumbers.begin(), amicableNumbers.end(), 0);

    // Print solution
    printf("\nSolution problem 21: %d", sum);
}