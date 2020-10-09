//
// Created by Cédric Goffin on 2020-10-06.
//

using namespace std;

#include <iostream>
#include <string>
#include <cmath>
#include <unordered_map>

/*
 * Problem 19:
 *
 * You are given the following information, but you may prefer to do some research for yourself. 1 Jan 1900 was a Monday.
 *
 *      Thirty days has September,
 *      April, June and November.
 *      All the rest have thirty-one,
 *      Saving February alone,
 *      Which has twenty-eight, rain or shine.
 *      And on leap years, twenty-nine.
 *
 * A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
 * How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
 */


const unordered_map<int, pair<string, int>> MONTH_DATA = {
        {1,  make_pair("JANUARY", 31)},
        {2,  make_pair("FEBRUARY", 28)},
        {3,  make_pair("MARCH", 31)},
        {4,  make_pair("APRIL", 30)},
        {5,  make_pair("MAY", 31)},
        {6,  make_pair("JUNE", 30)},
        {7,  make_pair("JULY", 31)},
        {8,  make_pair("AUGUST", 31)},
        {9,  make_pair("SEPTEMBER", 30)},
        {10, make_pair("OCTOBER", 31)},
        {11, make_pair("NOVEMBER", 30)},
        {12, make_pair("DECEMBER", 31)},
};
const unordered_map<int, string> DAY_DATA = {
        {1, "MONDAY"},
        {2, "TUESDAY"},
        {3, "WEDNESDAY"},
        {4, "THURSDAY"},
        {5, "FRIDAY"},
        {6, "SATURDAY"},
        {7, "SUNDAY"},
};

bool isLeapYear(int year) {
    return year % 4 == 0 && (year % 400 == 0 || year % 100 != 0);
}

int main() {
    // Start benchmark
    auto start = std::chrono::system_clock::now();

    // Initialize variables
    int day = 31,
            month = 12,
            year = 1899,
            count = 0,
            daysInMonth = MONTH_DATA.at(month).second + (month == 2 && isLeapYear(year) ? 1 : 0);

    /*
     *    // elapsed time: ~0.000184s
     *    // in 5271 loops and 1512 condition checks
     *    //while (year < 2001) {
     *    //    // Check if sunday needs to be counted
     *    //    if (year > 1900 && day == 1)
     *    //        count++;
     *    //
     *    //    // Set day to next sunday
     *    //    day += 7;
     *    //
     *    //    // Check if days are above maximum of month
     *    //    if (day > daysInMonth) {
     *    //        day %= daysInMonth;
     *    //
     *    //        // Set month to next month
     *    //        month++;
     *    //
     *    //        // Check if months > maximum of year
     *    //        if (month == 13) {
     *    //            month = 1;
     *    //            year++;
     *    //        }
     *    //
     *    //        // Set new daysInMonth
     *    //        daysInMonth = MONTH_DATA.at(month).second + (month == 2 && isLeapYear(year) ? 1 : 0);
     *    //    }
     *    //}
     */

    // elapsed time: 0.000184s
    // in 1213 loops and 462 condition checks
    while (year < 2001) {
        // Check if sunday needs to be counted
        if (year > 1900 && day == 1)
            count++;

        // Set day to sunday of next month
        while (day <= daysInMonth)
            day += 7;
        day %= daysInMonth;

        // Set to next month
        month++;
        if (month == 13) {
            month = 1;

            // Increment year by one
            year++;
        }

        // Set new daysInMonth
        daysInMonth = MONTH_DATA.at(month).second + (month == 2 && isLeapYear(year) ? 1 : 0);
    }

    // Print solution
    printf("Solution problem 19: %d sundays on the first of the month, between 01/01/1901 and 31/12/2001", count);

    // Print benchmark
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "\n\nelapsed time: " << elapsed_seconds.count() << "s\n";
}