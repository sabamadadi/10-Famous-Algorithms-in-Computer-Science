#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int start) {
    int numNodes = graph.size();
    vector<int> distance(numNodes, INF);
    vector<bool> visited(numNodes, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
            }
        }
    }

    return distance;
}

int main() {
    int numNodes = 6;
    vector<vector<pair<int, int>>> graph(numNodes);

    // Add edges to the graph
    graph[0].push_back({1, 5});
    graph[0].push_back({2, 3});
    graph[1].push_back({3, 6});
    graph[1].push_back({2, 2});
    graph[2].push_back({4, 4});
    graph[2].push_back({5, 2});
    graph[2].push_back({3, 7});
    graph[3].push_back({4, -1});
    graph[4].push_back({5, -2});

    int startNode = 0;
    vector<int> distances = dijkstra(graph, startNode);

    cout << "Shortest distances from node " << startNode << ":" << endl;
    for (int i = 0; i < numNodes; i++) {
        cout << "Node " << i << ": " << distances[i] << endl;
    }

    return 0;
}
