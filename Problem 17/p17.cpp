//
// Created by Cédric Goffin on 2020-10-05.
//

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <deque>

using namespace std;

/*
 * Problem 17:
 *
 * If the numbers 1 to 5 are written out in words: one, two, three, four, five,
 * then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total. If all the numbers
 * from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
 *
 * NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two)
 * contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
 */

// Declare constants
const unordered_map<int, string> NUMBERS_MAP = {
        {1,  "one"},
        {2,  "two"},
        {3,  "three"},
        {4,  "four"},
        {5,  "five"},
        {6,  "six"},
        {7,  "seven"},
        {8,  "eight"},
        {9,  "nine"},
        {10, "ten"},
        {11, "eleven"},
        {12, "twelve"},
        {13, "thirteen"},
        {14, "fourteen"},
        {15, "fifteen"},
        {16, "sixteen"},
        {17, "seventeen"},
        {18, "eighteen"},
        {19, "nineteen"},
        {20, "twenty"},
        {30, "thirty"},
        {40, "forty"},
        {50, "fifty"},
        {60, "sixty"},
        {70, "seventy"},
        {80, "eighty"},
        {90, "ninety"},
};
const string MULTIPLIERS[] = {"hundred", "thousand", "million", "billion", "trillion"}; // Ascending order
const string NUMBER_SEPARATOR = "and";

string numberToText(long number) {
    // Initialize variables
    string numberString = to_string(number);
    deque<string> numberGroups;

    // Create number groups of 3
    string groupToAdd;
    while (!numberString.empty()) {
        if (numberString.length() > 3) {
            groupToAdd = numberString.substr(numberString.length() - 3, 3);
            numberString = numberString.erase(numberString.length() - 3, numberString.length());
        } else {
            groupToAdd = numberString;
            numberString = "";
        }

        // Remove leading zeros in group
        while (!groupToAdd.empty() && groupToAdd[0] == '0')
            groupToAdd.erase(0, 1);

        // Add numberGroup to numberGroups
        numberGroups.push_front(groupToAdd);
    }

    // Convert groups to text
    string group, groupMultiplier, groupText;
    numberString = "";
    for (int i = numberGroups.size() - 1; i >= 0; --i) {
        // Reset vars
        group = numberGroups[numberGroups.size() - 1 - i];
        groupMultiplier = "";
        groupText = "";

        // Check if group is empty after removing leading zeros
        if (group.empty())
            continue;

        // Get groupMultiplier if available
        if (i + 1 <= (sizeof(MULTIPLIERS) / sizeof(*MULTIPLIERS)) && i > 0) {
            groupMultiplier = MULTIPLIERS[i];
        }

        // Convert hundred-digit to text
        if (group.length() == 3) {
            // Add first number and hundred multiplier to groupText
            groupText.append(NUMBERS_MAP.find(group[0] - '0')->second + " " + MULTIPLIERS[0]);

            // Erase first character
            group.erase(0, 1);

            // Remove leading zeros in group
            while (!group.empty() && group[0] == '0')
                group.erase(0, 1);
        }

        // Check if group is empty after removing leading zeros
        if (!group.empty()) {
            if (!groupText.empty())
                // Add separator to groupText
                groupText.append(" " + NUMBER_SEPARATOR);

            if (!groupText.empty())
                groupText.append(" ");

            // Check if last two digits combined are found in map
            auto mapIterator = NUMBERS_MAP.find(stoi(group.substr(0, 2)));
            if (mapIterator != NUMBERS_MAP.end()) {
                // Add map value to groupText
                groupText.append(mapIterator->second);
            } else {
                // Check if second number is zero
                if (group[0] != '0') {
                    // Get decimal number text from map
                    groupText.append(NUMBERS_MAP.find(stoi(group.substr(0, 1) + "0"))->second);
                    // Check if hyphen needs to be added
                    if (group[1] - '0' > 0)
                        groupText.append("-");
                }
                // Add last digit of group to groupText
                groupText.append(NUMBERS_MAP.find(group[1] - '0')->second);
            }
        }

        // Add groupText to numberString
        numberString += ((!numberString.empty()) ? " " : "") + groupText;

        // Add groupMultiplier to numberString if necessary
        if (!groupMultiplier.empty())
            numberString += " " + groupMultiplier;
    }

    // Return combined numberGroups
    return numberString;
}

string cleanString(string text, const vector<char> &charsToClean) {
    // Loop over chars to clean
    for (auto &character : charsToClean)
        // Erase character from text
        text.erase(remove(text.begin(), text.end(), character), text.end());

    // Return cleaned text
    return text;
}

int main() {
    // Initialize variables
    vector<char> charsToClean = {'\n', '\t', '-', ' '};

    // Loop over all numbers from 1 to 1000 (1000 inclusive)
    string numbers, number;
    for (int i = 1; i <= 1000; ++i) {
        // Convert number to text
        number = numberToText(i);
        // Print out number and text
        printf("%-4s = %s\n", to_string(i).c_str(), number.c_str());

        // Clean text and add to string
        numbers += cleanString(number, charsToClean);
    }

    // Print solution
    printf("\nSolution problem 17: %lu alphabetic characters in all numbers above", numbers.length());
}