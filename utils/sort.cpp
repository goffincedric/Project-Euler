//
// Created by Cédric Goffin on 2020-10-10.
//

#include <vector>
#include <string>
#include "sort.h"

//template<typename T>
void bubbleSort(std::vector<std::string> &vector, bool ascending) {
    // Initialize variables
    std::string temp;

    // Loop over all strings
    for (int i = 0; i < vector.size(); ++i) {
        // Loop over all vector entries after current entry
        for (int j = i + 1; j < vector.size(); ++j) {
            // Check if current entry is smaller/larger than current next entry
            if (ascending && vector[i].compare(vector[j]) >= 1) {
                // Switch larger and smaller entry to ascending order
                temp = vector[i];
                vector[i] = vector[j];
                vector[j] = temp;
            } else if (!ascending && vector[i].compare(vector[j]) <= -1) {
                // Switch larger and smaller entry to descending order
                temp = vector[j];
                vector[j] = vector[i];
                vector[i] = temp;
            }
        }
    }
}