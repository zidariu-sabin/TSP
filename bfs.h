#ifndef BFS_H
#define BFS_H
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;



struct Node {
    vector<int> path; // Current path taken
    int currentCity; // Current city in the path
    int longestDistance; // Longest distance in the current path
};


// Function to perform Breadth-First Search to find the path with the minimum longest distance
pair<vector<int>, int> bfs(const vector<vector<int>>& distanceMatrix, int startCity) {
    int n = distanceMatrix.size();
    queue<Node> q;
    q.push({{startCity}, startCity, 0});
    int minLongestDist = INT_MAX; // Initialize minimum longest distance with maximum possible value
    vector<int> bestPath; // To store the best path found

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

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
                q.push({newPath, nextCity, newLongestDist});
            }
        }
    }

    return {bestPath, minLongestDist};
}
#endif  BFS_H