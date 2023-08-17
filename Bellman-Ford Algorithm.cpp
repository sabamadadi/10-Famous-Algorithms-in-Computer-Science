#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Structure to represent a weighted edge
struct Edge {
    int source, destination, weight;
};

// Function to find the shortest paths using the Bellman-Ford algorithm
void bellmanFord(vector<Edge>& edges, int numVertices, int source) {
    vector<int> distance(numVertices, numeric_limits<int>::max());

    // Set the distance of the source vertex to 0
    distance[source] = 0;

    // Relax all edges (V-1) times
    for (int i = 0; i < numVertices - 1; i++) {
        for (const auto& edge : edges) {
            int u = edge.source;
            int v = edge.destination;
            int weight = edge.weight;

            if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (const auto& edge : edges) {
        int u = edge.source;
        int v = edge.destination;
        int weight = edge.weight;

        if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
            cout << "Negative-weight cycle detected. The graph contains negative cycles." << endl;
            return;
        }
    }

    // Print the shortest distances
    cout << "Shortest distances from the source vertex (" << source << "):" << endl;

    for (int i = 0; i < numVertices; i++) {
        cout << "Vertex " << i << ": ";
        
        if (distance[i] == numeric_limits<int>::max()) {
            cout << "Infinity" << endl;
        } else {
            cout << distance[i] << endl;
        }
    }
}

int main() {
    int numVertices = 5;
    int source = 0;

    vector<Edge> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    bellmanFord(edges, numVertices, source);

    return 0;
}
