#ifndef Uniform_cost_search_H
#define Uniform_cost_search_H
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

struct Node_ucs {
    vector<int> path;         // Current path taken
    int currentCity;          // Current city in the path
    int longestDistance;      // Longest distance in the current path

    // Comparator for priority queue to prioritize nodes with smaller longestDistance
    bool operator>(const Node_ucs& other) const {
        return longestDistance > other.longestDistance;
    }
};

pair<vector<int>, int> ucs(const vector<vector<int>>& distanceMatrix, int startCity) {
    int n = distanceMatrix.size(); // Number of cities
    priority_queue<Node_ucs, vector<Node_ucs>, greater<Node_ucs>> pq; // Priority queue for UCS
    pq.push({{startCity}, startCity, 0}); // Start UCS from the start city

    int minLongestDist = INT_MAX; // Initialize minimum longest distance with maximum possible value
    vector<int> bestPath;         // To store the best path found

    // UCS loop
    while (!pq.empty()) {
        Node_ucs current = pq.top(); // Get the node_ucs with the smallest longestDistance
        pq.pop();                // Remove the node_ucs from the priority queue

        // If the path covers all cities, complete the cycle by returning to the start city
        if (current.path.size() == n) {
            current.path.push_back(startCity); // Complete the cycle
            current.longestDistance = max(current.longestDistance, distanceMatrix[current.currentCity][startCity]);
            if (current.longestDistance < minLongestDist) {
                minLongestDist = current.longestDistance; // Update the minimum longest distance
                bestPath = current.path;                  // Update the best path
            }
            continue;
        }

        // Explore next cities
        for (int nextCity = 0; nextCity < n; ++nextCity) {
            // Check if the next city has not been visited in the current path
            if (find(current.path.begin(), current.path.end(), nextCity) == current.path.end()) {
                vector<int> newPath = current.path; // Create a new path including the next city
                newPath.push_back(nextCity);
                int newLongestDist = max(current.longestDistance, distanceMatrix[current.currentCity][nextCity]); // Calculate the new longest distance
                pq.push({newPath, nextCity, newLongestDist}); // Push the new node_ucs to the priority queue
            }
        }
    }

    return {bestPath, minLongestDist}; // Return the best path and its cost
}

#endif Uniform_cost_search_H
