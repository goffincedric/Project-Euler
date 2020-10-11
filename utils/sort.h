//
// Created by Cédric Goffin on 2020-10-10.
//

#include <vector>
#include <string>

#ifndef PROJECT_EULER_SORT_H
#define PROJECT_EULER_SORT_H

// String compare
int compare(const std::string &s1, const std::string &s2);
// Type-generic compare
template<typename T>
int compare(T s1, T s2);

// Bubble Sort function
template<typename T>
void bubbleSort(std::vector<T> &vector, bool ascending = true) {
    // Initialize variables
    T temp;

    // Loop over all strings
    int comparison;
    for (int i = 0; i < vector.size(); ++i) {
        // Loop over all vector entries after current entry
        for (int j = i + 1; j < vector.size(); ++j) {
            comparison = compare(vector[i], vector[j]);
            // Check if current entry is smaller/larger than current next entry
            if (ascending && comparison >= 1) {
                // Switch larger and smaller entry to ascending order
                temp = vector[i];
                vector[i] = vector[j];
                vector[j] = temp;
            } else if (!ascending && comparison <= -1) {
                // Switch larger and smaller entry to descending order
                temp = vector[j];
                vector[j] = vector[i];
                vector[i] = temp;
            }
        }
    }
}

#endif //PROJECT_EULER_SORT_H
