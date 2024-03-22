#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 4 // Number of vertices (including the starting vertex)

// Function to solve the Travelling Salesman Problem using dynamic programming
int tsp(int graph[][V]) {
    // dp[i][j] stores the minimum cost to reach vertex i from vertex 0 and visit all vertices in subset j
    int dp[V][1 << V];

    // Initialize dp array
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < (1 << V); j++) {
            dp[i][j] = -1;
        }
    }

    // Base case: Initialize dp array for vertices with subset size 1
    for (int i = 0; i < V; i++) {
        dp[i][1 << i] = graph[0][i];
    }

    // Recursive step
    for (int j = 1; j < (1 << V); j++) { // Iterate over all subsets of vertices
        for (int i = 0; i < V; i++) {     // Iterate over all vertices
            if (!(j & (1 << i))) continue; // Skip if vertex i is not present in subset j
            for (int k = 0; k < V; k++) { // Iterate over all vertices
                if (i == k || !(j & (1 << k))) continue; // Skip if vertex k is not present in subset j or i == k
                if (dp[i][j] == -1 || dp[i][j] > dp[k][j ^ (1 << i)] + graph[k][i]) {
                    dp[i][j] = dp[k][j ^ (1 << i)] + graph[k][i];
                }
            }
        }
    }

    // Return the minimum cost to reach vertex 0 from any vertex and visit all vertices once
    int minCost = INT_MAX;
    for (int i = 1; i < V; i++) {
        if (dp[i][(1 << V) - 1] != -1 && graph[i][0] != 0) {
            minCost = (minCost > dp[i][(1 << V) - 1] + graph[i][0]) ? dp[i][(1 << V) - 1] + graph[i][0] : minCost;
        }
    }
    return minCost;
}

// Main function
int main() {
    int graph[V][V] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    int minCost = tsp(graph);
    printf("Minimum cost to visit all vertices once and return to vertex 0: %d\n", minCost);
    return 0;
}