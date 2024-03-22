#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 4 // Number of vertices

// Function to find the nearest unvisited vertex
int nearestVertex(int distance[], bool visited[]) {
    int minDistance = INT_MAX, minVertex;
    for (int v = 0; v < V; v++) {
        if (visited[v] == false && distance[v] < minDistance) {
            minDistance = distance[v];
            minVertex = v;
        }
    }
    return minVertex;
}

// Function to find the minimum spanning tree using Prim's algorithm
int tspGreedy(int graph[V][V]) {
    int distance[V];    // Distance array to store the distance of vertices from the current vertex
    bool visited[V];    // Array to mark visited vertices
    int path[V];        // Array to store the path
    int totalDistance = 0; // Total distance traveled

    // Initialize distance array and visited array
    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    // Start from vertex 0
    distance[0] = 0;
    path[0] = -1; // Start of path

    // Find the nearest unvisited vertex at each step
    for (int count = 0; count < V - 1; count++) {
        int u = nearestVertex(distance, visited);
        visited[u] = true;

        // Update distance array
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && visited[v] == false && graph[u][v] < distance[v]) {
                distance[v] = graph[u][v];
                path[v] = u; // Update path
            }
        }
    }

    // Calculate total distance and print the path
    printf("Path: ");
    for (int i = 1; i < V; i++) {
        totalDistance += graph[i][path[i]];
        printf("%d ", path[i]);
    }
    totalDistance += graph[path[V - 1]][0]; // Return to starting vertex
    printf("0\n"); // Print the starting vertex
    return totalDistance;
}

// Main function
int main() {
    int graph[V][V] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    int minCost = tspGreedy(graph);
    printf("Minimum cost to visit all vertices once and return to vertex 0: %d\n", minCost);
    return 0;
}