//
// Created by Cédric Goffin on 2020-10-09.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../utils/files.h"
#include "../utils/sort.h"

/*
 * Problem 22:
 *
 * Using names.txt (right click and 'Save Link/Target As...'), a 46K text file
 * containing over five-thousand first names, begin by sorting it into alphabetical
 * order. Then working out the alphabetical value for each name, multiply this value
 * by its alphabetical position in the list to obtain a name score.
 *
 * For example, when the list is sorted into alphabetical order, COLIN, which is worth
 * 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a
 * score of 938 × 53 = 49714.
 *
 * What is the total of all the name scores in the file?
 */

void fillVector(std::vector<std::string> &names) {
    // Initialize path variable
    std::string path = "../Resources/p22_names.txt";

    // Fill vector with names
    readCSVFile(names, path);
}

int main() {
    // Initialize variables
    std::vector<std::string> names;
    long sum = 0;

    // Fill vector with names from file
    fillVector(names);

    // Sort names alphabetically ascending
    bubbleSort(names);

    // Calculate values of each name
    int temp;
    for (int i = 1; i <= names.size(); ++i) {
        // Set temp to zero
        temp = 0;

        // Add all character values to temp
        for (auto &character : names[i - 1])
            temp += character - 'A' + 1;

        // Multiply temp with index and add to sum
        temp *= i;
        sum += temp;
    }

    // Print solution
    printf("Solution problem 22: %ld", sum);
}