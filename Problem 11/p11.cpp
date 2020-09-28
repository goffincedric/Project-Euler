//
// Created by Cédric Goffin on 2020-09-26.
//

#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

/*
 * Problem 11:
 *
 * In the 20×20 grid below, four numbers along a diagonal line have been marked in red.
 *
 *      08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
 *      49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
 *      81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
 *      52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
 *      22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
 *      24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
 *      32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70
 *      67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21
 *      24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72
 *      21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95
 *      78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
 *      16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
 *      86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
 *      19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
 *      04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
 *      88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
 *      04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
 *      20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
 *      20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
 *      01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48
 *
 * The product of these numbers is 26 × 63 × 78 × 14 = 1788696.
 * What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20×20 grid?
 */

enum Direction {
    HORIZONTAL, VERTICAL, DIAGONAL
};

template<int rows, int columns, typename T>
void copyArray(T (&source)[rows][columns], T (&destination)[rows][columns]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            destination[i][j] = source[i][j];
        }
    }
}

long checkHorizontal(int (&matrix)[20][20], int (&positions)[4][2], int row, int column) {
    if (column - 4 + 1 >= 0) {
        // Set product
        long product = 1;

        // Loop over left-adjacent factors
        for (int i = 0; i < 4 && matrix[row][column - i] > 0; ++i) {
            product *= matrix[row][column - i];
            positions[4 - 1 - i][0] = row;
            positions[4 - 1 - i][1] = column - i;
        }

        // Return product
        return product;
    }
    return 0;
}

long checkVertical(int (&matrix)[20][20], int (&positions)[4][2], int row, int column) {
    if (row - 4 + 1 >= 0) {
        // Set product
        long product = 1;

        // Loop over top-adjacent factors
        for (int i = 0; i < 4 && matrix[row - i][column] > 0; ++i) {
            product *= matrix[row - i][column];
            positions[4 - 1 - i][0] = row - i;
            positions[4 - 1 - i][1] = column;
        }

        // Return product
        return product;
    }
    return 0;
}

long checkDiagonal(int (&matrix)[20][20], int (&positions)[4][2], int row, int column) {
    // Initialize largest product
    long largestProduct = 0;

    // Top-left diagonal
    if (row - 4 + 1 >= 0 && column - 4 + 1 >= 0) {
        // Set largest product
        largestProduct = 1;

        // Loop over top-diagonally-adjacent factors
        for (int i = 0; i < 4 && matrix[row - i][column - i] > 0; ++i) {
            largestProduct *= matrix[row - i][column - i];
            positions[4 - 1 - i][0] = row - i;
            positions[4 - 1 - i][1] = column - i;
        }
    }

    // Top-right diagonal
    if (row - 4 + 1 >= 0 && column + 4 - 1 < 20) {
        // Set product
        long product = 1;
        int newPositions[4][2];

        // Loop over top-adjacent factors
        for (int i = 0; i < 4 && matrix[row - i][column + i] > 0; ++i) {
            product *= matrix[row - i][column + i];

            newPositions[4 - 1 - i][0] = row - i;
            newPositions[4 - 1 - i][1] = column + i;
        }

        // Check if product is larger
        if (product > largestProduct) {
            largestProduct = product;
            copyArray(newPositions, positions);
        }
    }

    // Return largest product
    return largestProduct;
}

int traverseMatrix(int (&matrix)[20][20], int (&positions)[4][2]) {
    long largestProduct = 0;
    map<Direction, pair<long, int (*)[4][2]>> directionsMap;
    int positionsHorizontal[4][2], positionsVertical[4][2], positionsDiagonal[4][2];

    // Traverse matrix
    for (int row = 0; row < 20; ++row) {
        for (int column = 0; column < 20 - 4; ++column) {
            // Check positions
            directionsMap[Direction::HORIZONTAL] =  // Check horizontal
                    make_pair(checkHorizontal(matrix, positionsHorizontal, row, column), &positionsHorizontal);
            directionsMap[Direction::VERTICAL] =    // Check vertical
                    make_pair(checkVertical(matrix, positionsVertical, row, column), &positionsVertical);
            directionsMap[Direction::DIAGONAL] =    // Check diagonal
                    make_pair(checkDiagonal(matrix, positionsDiagonal, row, column), &positionsDiagonal);

            // Check products
            for (auto directionPair : directionsMap) {
                if (directionPair.second.first > largestProduct) {
                    // Set largest product and positions
                    largestProduct = directionPair.second.first;
                    copyArray(*directionPair.second.second, positions);
                }
            }
        }
    }

    // Return largest product found
    return largestProduct;
}

int main() {
    auto start = std::chrono::system_clock::now();

    // Declare matrix and pointer to first dimension of 2d matrix
    int matrix[20][20] = {
            {8,  2,  22, 97, 38, 15, 0,  40, 0,  75, 4,  5,  7,  78, 52, 12, 50, 77, 91, 8},
            {49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4,  56, 62, 0},
            {81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3,  49, 13, 36, 65},
            {52, 70, 95, 23, 4,  60, 11, 42, 69, 24, 68, 56, 1,  32, 56, 71, 37, 2,  36, 91},
            {22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80},
            {24, 47, 32, 60, 99, 3,  45, 2,  44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50},
            {32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70},
            {67, 26, 20, 68, 2,  62, 12, 20, 95, 63, 94, 39, 63, 8,  40, 91, 66, 49, 94, 21},
            {24, 55, 58, 5,  66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72},
            {21, 36, 23, 9,  75, 0,  76, 44, 20, 45, 35, 14, 0,  61, 33, 97, 34, 31, 33, 95},
            {78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3,  80, 4,  62, 16, 14, 9,  53, 56, 92},
            {16, 39, 5,  42, 96, 35, 31, 47, 55, 58, 88, 24, 0,  17, 54, 24, 36, 29, 85, 57},
            {86, 56, 0,  48, 35, 71, 89, 7,  5,  44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58},
            {19, 80, 81, 68, 5,  94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4,  89, 55, 40},
            {4,  52, 8,  83, 97, 35, 99, 16, 7,  97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66},
            {88, 36, 68, 87, 57, 62, 20, 72, 3,  46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69},
            {4,  42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8,  46, 29, 32, 40, 62, 76, 36},
            {20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4,  36, 16},
            {20, 73, 35, 29, 78, 31, 90, 1,  74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5,  54},
            {1,  70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1,  89, 19, 67, 48}
    };
    // Declare array for positions of largest product and pointer
    int positions[4][2];

    // Traverse matrix and find largest product
    long largestProduct = traverseMatrix(matrix, positions);

    // Print solution and positions
    printf("Solution problem 11: %ld\nPositions:\n", largestProduct);
    for (auto position : positions)
        printf("\t(%d, %d): %d\n", position[0], position[1], matrix[position[0]][position[1]]);

    // Print benchmark
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}