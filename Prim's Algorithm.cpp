#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

// Structure to represent a weighted edge
struct Edge {
    int source, destination, weight;

    Edge(int src, int dest, int wt) : source(src), destination(dest), weight(wt) {}
};

// Function to find the minimum spanning tree using Prim's algorithm
void primMST(vector<vector<Edge>>& graph, int numVertices) {
    vector<bool> visited(numVertices, false);
    vector<int> parent(numVertices, -1);
    vector<int> key(numVertices, INT_MAX);

    // Priority queue to store vertices and their key values
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Start with the first vertex
    int startVertex = 0;
    pq.push(make_pair(0, startVertex));
    key[startVertex] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        visited[u] = true;

        // Traverse all adjacent vertices of u
        for (const auto& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            if (!visited[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push(make_pair(key[v], v));
            }
        }
    }

    // Print the minimum spanning tree
    cout << "Edges in the minimum spanning tree:" << endl;
    for (int i = 1; i < numVertices; i++) {
        cout << "Edge: " << parent[i] << " - " << i << endl;
    }
}

int main() {
    int numVertices = 5;

    // Create a weighted graph
    vector<vector<Edge>> graph(numVertices);

    graph[0].push_back(Edge(0, 1, 2));
    graph[1].push_back(Edge(1, 0, 2));

    graph[0].push_back(Edge(0, 3, 6));
    graph[3].push_back(Edge(3, 0, 6));

    graph[1].push_back(Edge(1, 2, 3));
    graph[2].push_back(Edge(2, 1, 3));

    graph[1].push_back(Edge(1, 3, 8));
    graph[3].push_back(Edge(3, 1, 8));

    graph[1].push_back(Edge(1, 4, 5));
    graph[4].push_back(Edge(4, 1, 5));

    graph[2].push_back(Edge(2, 4, 7));
    graph[4].push_back(Edge(4, 2, 7));

    primMST(graph, numVertices);

    return 0;
}
