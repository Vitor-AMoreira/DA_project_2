
#include <algorithm>
#include <limits>
#include <cmath>
#include "Graph.h"
#include "Node_Edge.h"

using namespace std;

//BACKTRACKING ALGORITHM
static void tspBacktrack(Graph& graph, vector<Node*>& path, vector<bool>& visited, double currentDistance, double& shortestDistance) {

    if (path.size() == graph.getNodes().size()) {
        // All nodes visited, add the edge back to the starting node
        Node* lastNode = path.back();
        Node* firstNode = path.front();

        double distance = graph.getDistance(firstNode, lastNode);
        currentDistance += distance;
        shortestDistance = min(shortestDistance, currentDistance);
        return;
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

//TENHO QUE RETORNAR O VETOR DO CAMINHO QUE OS ALGORITMOS CONSEGUEM

static Node* findNearestNode(Node* node1, Graph graph, vector<Node*> tour, unordered_map<int, bool>visited) {
    Node* node2 = nullptr;
    //find the closest node to node1 and not visited
    for(int i = tour.size(); i >= 0; i--) {
        vector<Edge> edges = graph.getEdges();
        Node* adjNode = nullptr;
        for(Edge edge : edges) {
            if(edge.source == tour[i]) {
                adjNode = edge.target;
                if(visited[adjNode->index]) adjNode = nullptr;
            } else if(edge.target == tour[i]) {
                adjNode = edge.source;
                if(visited[adjNode->index]) adjNode = nullptr;
            }
            if(adjNode != nullptr && !visited[adjNode->index]) {
                node2 = adjNode;
                break;
            }
        }
        if(adjNode != nullptr) {
            break;
        }
    }
    return node2;
}

static double calculateDistance(Node* node1, Node* node2, Graph graph) {

    if (node1->latitude != "" && node2->latitude != "" && node1->longitude != "" && node2->longitude != "") {
        // Calculate distance based on latitude and longitude
        double lat1 = stod(node1->latitude);
        double lon1 = stod(node1->longitude);
        double lat2 = stod(node2->latitude);
        double lon2 = stod(node2->longitude);

        // Convert degrees to radians
        const double degToRad = M_PI / 180.0;
        lat1 *= degToRad;
        lon1 *= degToRad;
        lat2 *= degToRad;
        lon2 *= degToRad;

        // Earth's radius in meters
        const double earthRadius = 6371000.0;

        // Haversine formula to calculate great-circle distance between two points
        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;
        double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
                   std::cos(lat1) * std::cos(lat2) *
                   std::sin(dlon / 2) * std::sin(dlon / 2);
        double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
        double distance = earthRadius * c;

        return distance;
    } else {
        // Use Dijkstra's algorithm to find the distance between nodes

        // Create a priority queue for the nodes to be visited
        std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<std::pair<double, Node*>>> pq;

        // Create a map to store the distance from the source node
        std::unordered_map<Node*, double> distanceMap;

        // Initialize all distances to infinity except the source node
        for (const auto& kvp : graph.getEdges()) {
            Node* node = kvp.target;
            distanceMap[node] = std::numeric_limits<double>::infinity();
        }
        distanceMap[node1] = 0.0;

        // Add the source node to the priority queue
        pq.push(std::make_pair(0.0, node1));

        while (!pq.empty()) {
            Node* currNode = pq.top().second;
            double currDist = pq.top().first;
            pq.pop();

            // If the current node is the target node, return the distance
            if (currNode == node2) {
                return currDist;
            }

            // Iterate through the neighbors of the current node
            for (const Edge& edge : graph.getEdges()) {
                if (edge.source == currNode) {
                    Node* neighbor = edge.target;
                    double edgeDist = edge.distance;
                    double neighborDist = currDist + edgeDist;

                    // If the new distance is shorter, update the distance and add the neighbor to the priority queue
                    if (neighborDist < distanceMap[neighbor]) {
                        distanceMap[neighbor] = neighborDist;
                        pq.push(std::make_pair(neighborDist, neighbor));
                    }
                }
            }
        }

        // If the target node is not reachable, return infinity
        return std::numeric_limits<double>::infinity();
    }
}




//TRIANGULAR APPROXIMATION HEURISTIC
static vector<Node*> tspTriangularApproximation(Graph& graph) {
    std::vector<Node*> tour;
    double distance = 0.0;

    // Select a starting node (e.g., the node with index 0)
    Node* startNode = graph.getNodes()[0];
    tour.push_back(startNode);

    // Create a set to keep track of visited nodes
    std::unordered_map<int, bool> visited;
    visited[startNode->index] = true;

    // Repeat until all nodes are visited
    while (tour.size() < graph.getNodes().size()) {
        Node* current = tour.back();
        double minDistance = std::numeric_limits<double>::infinity();
        Node* nextNode = nullptr;

        // Find the nearest unvisited neighbor node
        for (Node* neighbor : graph.getNodes()) {
            if (!visited[neighbor->index]) {
                distance = graph.getDistance(current, neighbor);
                if (distance < minDistance) {
                    minDistance = distance;
                    nextNode = neighbor;
                }
            }
        }

        if(nextNode == nullptr) {
            nextNode = findNearestNode(current, graph, tour, visited);
            cout << "Nearest node found: " << current->index << " -> " << nextNode->index << endl;
            distance = calculateDistance(current, nextNode, graph);
            cout << "Distance between them: " << distance << endl;
            if(distance < minDistance) {
                minDistance = distance;
            }
        }

        // Add the nearest neighbor to the tour
        tour.push_back(nextNode);
        visited[nextNode->index] = true;
    }

    // Add the start node to complete the tour
    tour.push_back(startNode);

    return tour;
}