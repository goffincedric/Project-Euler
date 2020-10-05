//
// Created by Cédric Goffin on 2020-10-01.
//

#include <iostream>
#include <queue>
#include <deque>

using namespace std;

/*
 * Problem 15:
 *
 * Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
 *
 * How many such routes are there through a 20×20 grid?
 */

int main() {
    /*
     * Explanation:
     *
     * You can count the paths through these lattices by adding together the numbers of paths to each point in the lattice.
     * There’s only one way to start at the leftmost point, so mark that point with a 1. Next, you can take a step northeast
     * or a step southeast, with only one way to get to each of these points, so mark each of those with a 1. After that,
     * you can get to the second point on the dotted line in two ways: NE-then-SE, or SE-then-NE. Continuing this way,
     * you see that each of the points is described by the binomial coefficients, and the sequence of path counts for lattices
     * of different sizes is 1, 2, 6, 20, 70, …, also known as the central binomial coefficients.
     *
     * Source: https://robertdickau.com/lattices.html
     *
     * (Zie middelste getallen van Pascal's Triangle; Binomium van Newton)
     */

    // Start benchmark
    auto start = std::chrono::system_clock::now();

    // Initialize variables
    int gridWidth = 20, gridHeight = 20;
    long grid[gridHeight + 1][gridWidth + 1];

    // Build Pascal's Triangle
    for (int y = 0; y <= gridHeight; ++y) {
        for (int x = 0; x <= gridWidth; ++x) {
            if (x > 0 && y > 0) {
                printf("(%d, %d) = %ld\n", y, x, grid[y - 1][x] + grid[y][x - 1]);
                grid[y][x] = grid[y - 1][x] + grid[y][x - 1];
            } else {
                grid[y][x] = 1;
            }
        }
    }

    // Print solution
    printf("Solution problem 15: %ld lattice paths found in %dx%d grid\n", grid[gridHeight][gridWidth], gridHeight, gridWidth);

    // Print benchmark
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    /*
     * // Brute force: too slow
     *
     * // Initialize variables
     * int pathsFound = 0,
     *         gridWidth = 20,
     *         gridHeight = 20,
     *         startX = 0,
     *         startY = 0;
     * // Create queue for positions to explore
     * queue<pair<int, int>> pathsToExplore;
     * pathsToExplore.push(make_pair(startY, startX));
     *
     * // Explore all positions in queue
     * while (!pathsToExplore.empty()) {
     *     // Get and remove first element in queue
     *     auto currentPath = pathsToExplore.front();
     *     pathsToExplore.pop();
     *
     *     // Check if current element is bottom-right corner part of grid
     *     if (currentPath == make_pair(gridHeight, gridWidth)) {
     *         pathsFound++;
     *     } else {
     *         // Check if next row is not out of grid bounds
     *         if (currentPath.first + 1 <= gridHeight) {
     *             // Add new position to queue
     *             pathsToExplore.push(make_pair(currentPath.first + 1, currentPath.second));
     *         }
     *
     *         // Check if next column is not out of grid bounds
     *         if (currentPath.second + 1 <= gridWidth) {
     *             // Add new position to queue
     *             pathsToExplore.push(make_pair(currentPath.first, currentPath.second + 1));
     *         }
     *     }
     * }
     */
}