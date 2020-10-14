//
// Created by Cédric Goffin on 2020-10-12.
//

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include "../utils/math.h"

/*
 * Problem 24:
 *
 * A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation
 * of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically,
 * we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:
 *
 *                              012   021   102   120   201   210
 *
 * What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
 */


/*
 * Explanation:
 * https://medium.com/@aiswaryamathur/find-the-n-th-permutation-of-an-ordered-string-using-factorial-number-system-9c81e34ab0c8
 *
 * Collection = {a, b, c, d}
 * Question: What is the 15th lexicographic permutation of the previous collection?
 * Solution:
 *  Step 1: Convert nth permutation to index
 *       15 - 1 = 14
 *
 *  Step 2: Convert index to factoradic system
 *       14 = 2*3! + // 2 * 3! = 2 * 6 = 12
 *            1*2! + // 1 * 2! = 1 * 2 = 2
 *            0*1! +
 *            0*0!   // 12 + 2 = 14
 *          = 2100 in factoradic system
 *
 *  Step 3: For each digit in the factoradic number, take that element from the collection and remove it
 *                               /---\
 *       2 => {a, b, c, d}[2] => | c |
 *       1 => {a, b, d}[1]    => | b |
 *       0 => {a, d}[0]       => | a |
 *       0 => {a}[0]          => | d |
 *                               \---/
 *
 *  Step 4: Check!
 *       cbad => 15th permutation
 *
 *      1  abcd       7   bacd       13  cabd       19  dabc
 *      2  abdc       8   badc       14  cadb       20  dacb
 *      3  acbd       9   bcad       15  cbad       21  dbac
 *      4  acdb       10  bcda       16  cbda       22  dbca
 *      5  adbc       11  bdac       17  cdab       23  dcab
 *      6  adcb       12  bdca       18  cdba       24  dcba
 */

int main() {
    // Initialize variables
    int nthPermutation = 1000000, currentPermutation = nthPermutation - 1;
    std::vector<int> digits(10), number;

    // Populate digits vector
    std::iota(digits.begin(), digits.end(), 0);

    // Move digits from digits vector to number vector until 1 digit is left
    int currentFactorial, currentIndex;
    while (digits.size() > 1) {
        // Calculate the largest possible factorial <= currentPermutation
        currentFactorial = INT_MAX;
        for (int i = digits.size(); i > 0 && currentFactorial > currentPermutation; --i)
            currentFactorial = factorial(i);


        // Get index to of digit to push to number
        currentIndex = (int) trunc(currentPermutation / currentFactorial);

        // Add digit to number vector and delete from digits vector
        number.push_back(digits[currentIndex]);
        digits.erase(digits.begin() + currentIndex);

        // Set new currentPermutation
        currentPermutation %= currentFactorial;
    }
    // Add last digit to number vector
    number.push_back(digits[0]);

    // Print number
    std::cout << ("Solution problem 24: ");
    for (int &num : number) std::cout << num;
    std::cout << std::endl;
}