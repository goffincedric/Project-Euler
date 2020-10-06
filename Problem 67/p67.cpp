//
// Created by Cédric Goffin on 2020-10-06.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>

using namespace std;

/*
 * Problem 18:
 *
 * By starting at the top of the triangle below and moving to adjacent numbers on the row below,
 * the maximum total from top to bottom is 23.
 *         3
 *        7 4
 *       2 4 6
 *      8 5 9 3
 * That is, 3 + 7 + 4 + 9 = 23.
 *
 * Find the maximum total from top to bottom in p67_triangle.txt, a 15K text file containing a triangle
 * with one-hundred rows.
 *
 * NOTE: This is a much more difficult version of Problem 18. It is not possible to try every route
 * to solve this problem, as there are 299 altogether! If you could check one trillion (1012) routes
 * every second it would take over twenty billion years to check them all. There is an efficient
 * algorithm to solve it. ;o)
 */

void fillVector(vector<vector<int>> &pyramid) {
    // Clear pyramid
    pyramid.clear();

    // Read from the text file
    ifstream MyReadFile(__fs::filesystem::relative("../Resources/p67_triangle.txt"));

    // Use getLine() to read file line by line
    string line, token, delimiter = " ";
    vector<int> layer;
    while (getline(MyReadFile, line)) {
        // Loop over numbers in line
        size_t pos = 0;
        layer.clear();
        while ((pos = line.find(delimiter)) != string::npos) {
            // Get first number from line
            token = line.substr(0, pos);

            // Add number to layer vector
            layer.push_back(stoi(token));

            // Delete number from string
            line.erase(0, pos + delimiter.length());
        }

        // Add last remaining number in line to layer vector
        layer.push_back(stoi(line));

        // Add layer to pyramid
        pyramid.push_back(layer);
    }

    // Close the file
    MyReadFile.close();
}



int main() {
    // Initialize pyramid
    vector<vector<int>> pyramid;

    // Fill pyramid vector with file data
    fillVector(pyramid);

    // Add each node in each layer to the two nodes diagonally below
    vector<int> maximums, temp;
    for (auto &layer : pyramid) {
        // Copy temp to layer
        temp = layer;

        // Check if maximums vector needs to be filled first
        if (!maximums.empty()) {
            for (int j = 0; j < maximums.size(); ++j) {
                if (j > 0 && maximums[j - 1] < maximums[j])
                    temp[j] = layer[j] + maximums[j];
                else if (temp[j] == layer[j])
                    temp[j] += maximums[j];
                temp[j + 1] += maximums[j];
            }
        }

        // Copy temp to maximums vector
        maximums = temp;
    }

    // Find largest number in maximums vector
    int largestMaximum = accumulate(maximums.begin(), maximums.end(), 0, [](long i, long j) {
        return max(i, j);
    });

    // Print solution
    printf("Solution problem 67: %d", largestMaximum);
}