#ifndef TSP_A_STAR_H
#define TSP_A_STAR_H
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <functional>

using namespace std;

struct Node_a {
    vector<int> path; // Current path taken
    int currentCity; // Current city in the path
    int longestDistance; // Longest distance in the current path
    int estimatedCost; // Estimated cost from current node_a to the goal
};

// Heuristic function: Estimated cost from current city to the goal
int heuristic(const vector<vector<int>>& distanceMatrix, const vector<int>& remainingCities, int currentCity) {
    int minDist = INT_MAX;
    for (int city : remainingCities) {
        if (city != currentCity) {
            minDist = min(minDist, distanceMatrix[currentCity][city]);
        }
    }
    return minDist;
}

// Function to perform A* search to find the path with the minimum longest distance
pair<vector<int>, int> AStar(const vector<vector<int>>& distanceMatrix, int startCity) {
    int n = distanceMatrix.size();
    vector<int> allCities(n);
    for (int i = 0; i < n; ++i) {
        allCities[i] = i;
    }

    priority_queue<Node_a, vector<Node_a>, function<bool(const Node_a&, const Node_a&)>> pq(
            [](const Node_a& a, const Node_a& b) {
                return a.estimatedCost > b.estimatedCost;
            }
    );

    pq.push({{startCity}, startCity, 0, heuristic(distanceMatrix, allCities, startCity)});
    int minLongestDist = INT_MAX; // Initialize minimum longest distance with maximum possible value
    vector<int> bestPath; // To store the best path found

    while (!pq.empty()) {
        Node_a current = pq.top();
        pq.pop();

        // If the path covers all cities, complete the cycle by returning to the start city
        if (current.path.size() == n) {
            current.path.push_back(startCity);
            current.longestDistance = max(current.longestDistance, distanceMatrix[current.currentCity][startCity]);
            if (current.longestDistance < minLongestDist) {
                minLongestDist = current.longestDistance;
                bestPath = current.path;
            }
            continue;
        }

        // Explore next cities
        for (int nextCity = 0; nextCity < n; ++nextCity) {
            if (find(current.path.begin(), current.path.end(), nextCity) == current.path.end()) {
                vector<int> newPath = current.path;
                newPath.push_back(nextCity);
                int newLongestDist = max(current.longestDistance, distanceMatrix[current.currentCity][nextCity]);
                int estimatedCost = newLongestDist + heuristic(distanceMatrix, newPath, nextCity);
                pq.push({newPath, nextCity, newLongestDist, estimatedCost});
            }
        }
    }

    return {bestPath, minLongestDist};
}

#endif //TSP_A_STAR_H
