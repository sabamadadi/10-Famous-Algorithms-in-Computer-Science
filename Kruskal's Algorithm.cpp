#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a weighted edge
struct Edge {
    int source, destination, weight;

    Edge(int src, int dest, int wt) : source(src), destination(dest), weight(wt) {}
};

// Structure to represent a disjoint set for union-find operations
struct DisjointSet {
    vector<int> parent, rank;

    DisjointSet(int numVertices) {
        parent.resize(numVertices);
        rank.resize(numVertices, 0);

        for (int i = 0; i < numVertices; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (xApologies for the incomplete response. Here's the complete code for Kruskal's algorithm:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a weighted edge
struct Edge {
    int source, destination, weight;

    Edge(int src, int dest, int wt) : source(src), destination(dest), weight(wt) {}
};

// Structure to represent a disjoint set for union-find operations
struct DisjointSet {
    vector<int> parent, rank;

    DisjointSet(int numVertices) {
        parent.resize(numVertices);
        rank.resize(numVertices, 0);

        for (int i = 0; i < numVertices; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

// Function to find the minimum spanning tree using Kruskal's algorithm
void kruskalMST(vector<Edge>& edges, int numVertices) {
    // Sort edges in non-decreasing order of weight
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    // Create a disjoint set for union-find operations
    DisjointSet ds(numVertices);

    // Vector to store the edges in the minimum spanning tree
    vector<Edge> mst;

    // Process each edge in ascending order of weight
    for (const auto& edge : edges) {
        int rootX = ds.find(edge.source);
        int rootY = ds.find(edge.destination);

        // If including the current edge does not form a cycle, add it to the minimum spanning tree
        if (rootX != rootY) {
            mst.push_back(edge);
            ds.unionSets(rootX, rootY);
        }
    }

    // Print the minimum spanning tree
    cout << "Edges in the minimum spanning tree:" << endl;
    for (const auto& edge : mst) {
        cout << "Edge: " << edge.source << " - " << edge.destination << endl;
    }
}

int main() {
    int numVertices = 5;

    // Create a vector of edges
    vector<Edge> edges;
    edges.push_back(Edge(0, 1, 2));
    edges.push_back(Edge(0, 3, 6));
    edges.push_back(Edge(1, 2, 3));
    edges.push_back(Edge(1, 3, 8));
    edges.push_back(Edge(1, 4, 5));
    edges.push_back(Edge(2, 4, 7));

    kruskalMST(edges, numVertices);

    return 0;
}
