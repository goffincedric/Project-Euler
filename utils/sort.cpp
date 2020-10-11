//
// Created by Cédric Goffin on 2020-10-10.
//

#include <vector>
#include <string>
#include "sort.h"

// String compare
int compare(const std::string &s1, const std::string &s2) {
    return s1.compare(s2);
}

// Type-generic compare
template<typename T>
int compare(const T &s1, const T &s2) {
    if (s1 > s2) {
        return 1;
    } else if (s1 == s2) {
        return 0;
    } else {
        return -1;
    }
}