#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "bfs.h"
#include "Uniform_cost_search.h"
#include "A_star.h"
using namespace std;
using namespace std::chrono;

// Structure to represent each node in the BFS queue


// Function to generate a random distance matrix for a given number of cities
vector<vector<int>> generateDistanceMatrix(int numCities) {
    vector<vector<int>> distanceMatrix(numCities, vector<int>(numCities, 0));
    srand(time(0)); // Seed for random number generation

    // Populate the upper triangle of the distance matrix with random values and make it symmetric
    for (int i = 0; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            int distance = rand() % 200 + 1; // Random distance between 1 and 200
            distanceMatrix[i][j] = distance;
            distanceMatrix[j][i] = distance;
        }
    }

    return distanceMatrix;
}

int main() {
    int numCities = 10;
    vector<vector<int>> distanceMatrix = generateDistanceMatrix(numCities);
    vector<vector<int>> distanceMatrixByHand = {
            {0, 45, 137, 122},
            {45, 0, 27, 188},
            {137, 27, 0, 190},
            {122, 188, 190, 0}
    };

    // Print the generated distance matrix
    cout << "Distance Matrix:" << endl;
    for (const auto& row : distanceMatrix) {
        for (int dist : row) {
            cout << dist << " ";
        }
        cout << endl;
    }
//    for (const auto& row : distanceMatrixByHand) {
//        for (int dist : row) {
//            cout << dist << " ";
//        }
//        cout << endl;
//    }


    int startCity = 0; // Starting city for the BFS algorithm

    // Measure the performance time of the BFS algorithm
    auto start = high_resolution_clock::now();
   // pair<vector<int>, int> result = bfs(distanceMatrix, startCity);
   // pair<vector<int>, int> result =ucs(distanceMatrix, startCity);
    //pair<vector<int>, int> result = AStar(distanceMatrix, startCity);
     //pair<vector<int>, int> result = bfs(distanceMatrixByHand, startCity);
     //pair<vector<int>, int> result =ucs(distanceMatrixByHand, startCity);
    pair<vector<int>, int> result = AStar(distanceMatrixByHand, startCity);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start).count();

    // Print the path taken and the cost (longest distance)
    cout << "Path taken: ";
    for (int city : result.first) {
        cout << city << " ";
    }
    cout << endl;

    cout << "Cost (Longest Distance): " << result.second << endl;
    cout << "Performance Time: " << duration << " nanoseconds" << endl;

    return 0;
}