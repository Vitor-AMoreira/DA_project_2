
#include <algorithm>
#include <limits>
#include "Graph.h"
#include "auxFunctions.cpp"

using namespace std;

static double tspBacktrack(Graph& graph, vector<Node*>& path, vector<bool>& visited, double currentDistance, double& shortestDistance) {
//    cout << "Shortest distance: " << shortestDistance << endl;
    if (path.size() == graph.getNodes().size()) {
        // All nodes visited, add the edge back to the starting node
        Node* lastNode = path.back();
        Node* firstNode = path.front();

        double distance = graph.getDistance(lastNode, firstNode);
        currentDistance += distance;
        shortestDistance = min(shortestDistance, currentDistance);
        return shortestDistance;
    }

    for (auto& node : graph.getNodes()) {
        if (!visited[node->index]) {
            visited[node->index] = true;
            Node* lastNode = path.back();

            path.push_back(node);
            double distance = graph.getDistance(lastNode, node);

            double newDistance = currentDistance + distance;
            if (newDistance < shortestDistance) {
                tspBacktrack(graph, path, visited, newDistance, shortestDistance);
            }

            path.pop_back();
            visited[node->index] = false;
        }
    }

    return shortestDistance;
}

static double solveTSP(Graph& graph) {
    double shortestDistance = numeric_limits<double>::max();

    vector<Node*> path;
    vector<bool> visited(graph.getNodes().size(), false);
    visited[0] = true;  // Starting node is always visited
    path.push_back(graph.getNodes()[0]);

    tspBacktrack(graph, path, visited, 0.0, shortestDistance);

    return shortestDistance;
}
// Find the nearest neighbor of a node that has not been visited
static int findNearestNeighbor(int node, const vector<Node*>& nodes, const vector<bool>& visited) {
    int nearestNeighbor = -1;
    double minDistance = numeric_limits<double>::max();

    for (int i = 0; i < nodes.size(); ++i) {
        if (i != node && !visited[i]) {
            double distance = getDistance(nodes[node]->latitude, nodes[node]->longitude, nodes[i]->latitude, nodes[i]->longitude);
            if (distance < minDistance) {
                minDistance = distance;
                nearestNeighbor = i;
            }
        }
    }

    return nearestNeighbor;
}

// Triangular Approximation Heuristic for TSP
static double tspTriangularApproximation(Graph& graph) {
    vector<Node*> nodes = graph.getNodes();
    vector<bool> visited(nodes.size(), false);
    vector<Node*> path;
    path.push_back(nodes[0]);
    double distance = 0;

    // Start at node 0
    int currentNode = 0;
    visited[currentNode] = true;

    // Find the nearest neighbor and create an edge until all nodes are visited
    while (find(visited.begin(), visited.end(), false) != visited.end()) {
        int nearestNeighbor = findNearestNeighbor(currentNode, nodes, visited);
        visited[nearestNeighbor] = true;
        path.push_back(nodes[nearestNeighbor]);
        distance += getDistance(nodes[currentNode]->latitude,nodes[currentNode]->longitude, nodes[nearestNeighbor]->latitude, nodes[nearestNeighbor]->longitude);
        currentNode = nearestNeighbor;
    }

    // Complete the path by connecting the last node to the starting node
    path.push_back(nodes[0]);
    distance += getDistance(nodes[currentNode]->latitude,nodes[currentNode]->longitude, nodes[0]->latitude, nodes[0]->longitude);
    return distance;
}