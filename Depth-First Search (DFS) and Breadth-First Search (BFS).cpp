#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void dfs(const vector<vector<int>>& graph, vector<bool>& visited, int node) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(graph, visited, neighbor);
        }
    }
}

void bfs(const vector<vector<int>>& graph, int start) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int numNodes = 7;
    vector<vector<int>> graph(numNodes);

    // Add edges to the graph
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(3);
    graph[1].push_back(4);
    graph[2].push_back(5);
    graph[2].push_back(6);

    int startNode = 0;

    cout << "DFS traversal: ";
    vector<bool> visitedDFS(numNodes, false);
    dfs(graph, visitedDFS, startNode);
    cout << endl;

    cout << "BFS traversal: ";
    bfs(graph, startNode);
    cout << endl;

    return 0;
}
