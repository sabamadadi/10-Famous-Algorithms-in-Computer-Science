#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

using namespace std;

// Structure to represent a node in the graph
struct Node {
    int x, y;        // Coordinates of the node
    double gScore;   // Cost from start node to current node
    double fScore;   // Estimated total cost from start node to goal node (gScore + heuristic)

    Node(int xCoord, int yCoord, double g, double f) : x(xCoord), y(yCoord), gScore(g), fScore(f) {}
};

// Calculate the Euclidean distance between two nodes
double calculateDistance(const Node& node1, const Node& node2) {
    int dx = node2.x - node1.x;
    int dy = node2.y - node1.y;
    return sqrt(dx * dx + dy * dy);
}

// Function to perform the A* search algorithm
void aStarSearch(vector<vector<int>>& graph, Node start, Node goal) {
    int numRows = graph.size();
    int numCols = graph[0].size();

    // Create a 2D vector to keep track of visited nodes
    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));

    // Create a 2D vector to store the gScore for each node
    vector<vector<double>> gScore(numRows, vector<double>(numCols, numeric_limits<double>::max()));

    // Create a priority queue to store the nodes based on their fScore
    priority_queue<Node, vector<Node>, function<bool(const Node&, const Node&)>> pq(
        [](const Node& a, const Node& b) { return a.fScore > b.fScore; }
    );

    // Set the gScore of the start node to 0
    gScore[start.x][start.y] = 0;

    // Set the fScore of the start node to the estimated cost to the goal node
    start.fScore = calculateDistance(start, goal);

    // Add the start node to the priority queue
    pq.push(start);

    while (!pq.empty()) {
        // Get the node with the lowest fScore from the priority queue
        Node current = pq.top();
        pq.pop();

        // Check if the current node is the goal node
        if (current.x == goal.x && current.y == goal.y) {
            cout << "Path found!" << endl;
            return;
        }

        // Mark the current node as visited
        visited[current.x][current.y] = true;

        // Generate the neighbors of the current node
        vector<Node> neighbors;
        if (current.x > 0 && graph[current.x - 1][current.y] != 0) {
            neighbors.push_back(Node(current.x - 1, current.y, 0, 0));
        }
        if (current.x < numRows - 1 && graph[current.x + 1][current.y] != 0) {
            neighbors.push_back(Node(current.x + 1, current.y, 0, 0));
        }
        if (current.y > 0 && graph[current.x][current.y - 1] != 0) {
            neighbors.push_back(Node(current.x, current.y - 1, 0, 0));
        }
        if (current.y < numCols - 1 && graph[current.x][current.y + 1] != 0) {
            neighbors.push_back(Node(current.x, current.y + 1, 0, 0));
        }

        // Update the gScore and fScore of the neighbors
        for (Node& neighbor : neighbors) {
            // Skip the neighbor if it has already been visited
            if (visited[neighbor.x][neighbor.y]) {
                continue;
            }

            // Calculate the tentative gScore for the neighbor
            double tentativeGScore = current.gScore + calculateDistance(current, neighbor);

            // Add the neighbor to the priority queue if it is not already in it
            if (tentativeGScore < gScore[neighbor.x][neighbor.y]) {
                neighbor.gScore = tentativeGScore;
                neighbor.fScore = neighbor.gScore + calculateDistance(neighbor, goal);
                pq.push(neighbor);
                gScore[neighbor.x][neighbor.y] = tentativeGScore;
            }
        }
    }

    // If the priority queue becomes empty, there is no path from the start node to the goal node
    cout << "Path not found!" << endl;
}

int main() {
    // Example graph represented as a 2D vector
    vector<vector<int>> graph = {
        {1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };

    // Start node
    Node start(0, 0, 0, 0);

    // Goal node
    Node goal(4, 4, 0, 0);

    // Perform A* search
    aStarSearch(graph, start, goal);

    return 0;
}
