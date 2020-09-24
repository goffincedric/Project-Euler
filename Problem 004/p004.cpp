//
// Created by Cédric Goffin on 2020-09-24.
//
#include <iostream>
#include <sstream>

using namespace std;


void reverse(string &str) {
    int n = str.length();

    for (int i = 0; i < n / 2; i++) {
        swap(str[i], str[n - i - 1]);
    }
}

bool isPalindrome(int number) {
    // Copy original number
    int original = number;

    // Convert original number to string and reverse
    string reversedString = std::to_string(original);
    reverse(reversedString);

    // Convert reversed string back to number
    int reversed = 0;
    stringstream intValue(reversedString);
    intValue >> reversed;

    // Check if is palindrome
    return original / reversed == 1 && original % reversed == 0;
}

int main() {
    int number = 0,
            largestPalindrome = 0,
            a = 0,
            b = 0;
    for (int i = 999; i > 99; --i) {
        for (int j = 999; j > 99; --j) {
            number = i * j;
            if (isPalindrome(number) && number > largestPalindrome) {
                largestPalindrome = number;
                a = i;
                b = j;
            }
        }
    }

    printf("Solution problem 4: %d * %d = %d", a, b, largestPalindrome);
}