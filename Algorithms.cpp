
#include <algorithm>
#include <limits>
#include "Graph.h"
#include "Node_Edge.h"

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
            path.push_back(node);

            Node* lastNode = path[path.size() - 2];
            Node* currentNode = path.back();
            double distance = graph.getDistance(lastNode, currentNode);

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

