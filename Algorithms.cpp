

#include <algorithm>
#include <limits>
#include "Graph.h"
#include "Node_Edge.h"

using namespace std;

double static tspBacktrack(Graph& graph, vector<Node*>& path, vector<bool>& visited, double currentDistance, double& shortestDistance) {
    if (path.size() == graph.getNodes().size()) {
        // All nodes visited, add the edge back to the starting node
        Node* lastNode = path.back();
        Node* firstNode = path.front();

        for (const auto& edge : graph.getEdges()) {
            if (edge.source == lastNode && edge.target == firstNode) {
                currentDistance += edge.distance;
                break;
            }
        }

        shortestDistance = min(shortestDistance, currentDistance);
        return shortestDistance;
    }

    for (auto& edge : graph.getEdges()) {
        if (!visited[edge.target->index]) {
            visited[edge.target->index] = true;
            path.push_back(edge.target);

            double newDistance = currentDistance + edge.distance;
            if (newDistance < shortestDistance) {
                tspBacktrack(graph, path, visited, newDistance, shortestDistance);
            }

            path.pop_back();
            visited[edge.target->index] = false;
        }
    }

    return shortestDistance;
}


double static solveTSP(Graph& graph) {
    double shortestDistance = numeric_limits<double>::max();

    vector<Node*> path;
    vector<bool> visited(graph.getNodes().size(), false);
    visited[0] = true;  // Starting node is always visited
    path.push_back(graph.getNodes()[0]);
    cout << graph.getNodes()[0] << endl;

    shortestDistance = tspBacktrack(graph, path, visited, 0.0, shortestDistance);

    return shortestDistance;
}

