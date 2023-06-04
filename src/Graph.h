/**
 * @file Graph.h
 * @author G04_T07
 * @brief This file handles the creation and utilization of graphs, edges and nodes
 * @version 0.1
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <cmath>
#include <iostream>
#include <random>
#include <algorithm>

/**
 * @brief Variable to easily convert values from degrees to radians.
 *
 */
constexpr double toRadians = M_PI / 180.0;

/**
 * @brief Variable that represents the average nodes per centroid.
 *
 */
const int stepSize = 100;

using namespace std;

/**
 * @brief Class that represents each node of the graph. It's composed by it's id, latitude and longitude.
 *
 */
class Node
{
public:
    /// @brief Id of the node.
    int id;

    /// @brief Latitude of the node.
    double latitude;

    /// @brief Longitude of the node.
    double longitude;

    /**
     * @brief Construct a new Node object
     *
     * @param nodeId Id of the new node.
     * @param lat Latitude of the new node.
     * @param lon Longitude of the new node.
     */
    Node(int nodeId, double lat = 0.0, double lon = 0.0) : id(nodeId), latitude(lat), longitude(lon) {}
};

/**
 * @brief Class that represents each edge of the graph. It's composed by it's source node id, destination node id and it's weigth(length).
 *
 */
class Edge
{
public:
    /// @brief Id of the node that is at one of its ends.
    int source;

    /// @brief Id of the node that is at the other end.
    int destination;

    /// @brief Length of the edge.
    double weight;

    /**
     * @brief Construct a new Edge object
     *
     * @param src  Id of the node that is at one of its ends.
     * @param dest Id of the node that is at the other end.
     * @param edgeWeight Length of the edge.
     */
    Edge(int src, int dest, double edgeWeight) : source(src), destination(dest), weight(edgeWeight) {}
};

/**
 * @brief Struct to more easily compare edges by their weigths.
 *
 */
struct CompareEdges
{
    /**
     * @brief Function to compare edges by their weights.
     *
     * @param e1 Edge1.
     * @param e2 Edge2.
     * @return true If Edge1 weight is larger than Edge2 weight.
     * @return false If Edge1 weight is equal or smaller than Edge2 weight.
     */
    bool operator()(const Edge &e1, const Edge &e2)
    {
        return e1.weight > e2.weight;
    }
};

/**
 * @brief Class that represents the graph. It's composed by an adjacency list, a node's vector and it's cluster distribution.
 *
 */
class Graph
{
private:
    /// @brief Total number of nodes in the graph.
    int numNodes;

    /// @brief Adjacency List of the graph. Stores a list of Edges that are connected to each node.
    vector<list<Edge>> adjacencyList;

    /// @brief Vector of nodes of the graph.
    vector<Node *> nodes;

    /// @brief Vector that shows at wich cluster each node belongs (after k-mean, only for real-world graphs / nodes with coordinates).
    vector<vector<int>> clusters;

    /**
     * @brief Function to calculate the haversine distance between two coordinates.
     *
     * @param latitude1 latitude of node1.
     * @param longitude1 longitude of node1.
     * @param latitude2 latitude of node2.
     * @param longitude2 longitude of node2.
     * @return double distance between two coordinates
     */
    double haversine(double latitude1, double longitude1, double latitude2, double longitude2) const
    {
        double latDiff = (latitude2 - latitude1) * toRadians;
        double lonDiff = (longitude2 - longitude1) * toRadians;

        // Haversine formula
        double a = sin(latDiff / 2) * sin(latDiff / 2) +
                   cos(latitude1) * cos(latitude2) *
                       sin(lonDiff / 2) * sin(lonDiff / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double distance = 6371.0 * c;

        return distance;
    }

    // Function to initialize the centroids randomly
    vector<Node> initializeCentroids(int k)
    {
        vector<Node> centroids;
        vector<int> selectedIndices;

        random_device rd;                                  // Obtain a random number from hardware
        mt19937 eng(rd());                                 // Seed the generator
        uniform_int_distribution<> distr(0, numNodes - 1); // Define the range

        while (centroids.size() < k)
        {
            int index = distr(eng); // Generate the random number
            if (find(selectedIndices.begin(), selectedIndices.end(), index) == selectedIndices.end())
            {
                selectedIndices.push_back(index);
                centroids.push_back(*getNodes()[index]);
            }
        }

        return centroids;
    }

    /**
     * @brief Function to assign each node to the nearest centroid
     *
     * @param centroids Vector of centroids
     * @param clusterAssignments Vector of the centroid assigned to each node
     */
    void assignNodesToCentroids(const vector<Node> &centroids, vector<int> &clusterAssignments)
    {
        for (int nodeIndex = 0; nodeIndex < getNumNodes(); ++nodeIndex)
        {
            double minDistance = numeric_limits<double>::max();
            int closestCentroidIndex = -1;

            for (int centroidIndex = 0; centroidIndex < centroids.size(); ++centroidIndex)
            {
                const Node &centroid = centroids[centroidIndex];
                const Node *node = getNodes()[nodeIndex];

                double distance = haversine(centroid.latitude, centroid.longitude, node->latitude, node->longitude);

                if (distance < minDistance)
                {
                    minDistance = distance;
                    closestCentroidIndex = centroidIndex;
                }
            }

            clusterAssignments[nodeIndex] = closestCentroidIndex;
        }
    }

    /**
     * @brief Function to recalculate the cluster centroids
     *
     * @param clusterAssignments Vector of the centroid assigned to each node
     * @param centroids Vector of centroids
     */
    void updateCentroids(const vector<int> &clusterAssignments, vector<Node> &centroids)
    {
        vector<int> clusterCounts(centroids.size(), 0);
        vector<double> clusterSumsX(centroids.size(), 0.0);
        vector<double> clusterSumsY(centroids.size(), 0.0);

        for (int nodeIndex = 0; nodeIndex < getNumNodes(); ++nodeIndex)
        {
            int centroidIndex = clusterAssignments[nodeIndex];
            const Node *node = getNodes()[nodeIndex];

            clusterCounts[centroidIndex]++;
            clusterSumsX[centroidIndex] += node->latitude;
            clusterSumsY[centroidIndex] += node->longitude;
        }

        for (int centroidIndex = 0; centroidIndex < centroids.size(); ++centroidIndex)
        {
            int clusterCount = clusterCounts[centroidIndex];
            double clusterSumX = clusterSumsX[centroidIndex];
            double clusterSumY = clusterSumsY[centroidIndex];

            if (clusterCount > 0)
            {
                centroids[centroidIndex].latitude = clusterSumX / clusterCount;
                centroids[centroidIndex].longitude = clusterSumY / clusterCount;
            }
        }
    }

    /**
     * @brief Function to check if the cluster assignments have changed
     *
     * @param prevClusterAssignments Previous vector of centroids assigned to each cluster
     * @param clusterAssignments Current vector of centroids assigned to each cluster
     * @return true If cluster assignments hasn't changed
     * @return false If cluster assignments has changed
     */
    bool hasConverged(const vector<int> &prevClusterAssignments, const vector<int> &clusterAssignments)
    {
        return prevClusterAssignments == clusterAssignments;
    }

public:
    /// @brief Default constructor
    Graph() = default;

    /**
     * @brief Construct a new Graph object
     *
     * @param filename Name of file to read where the graph is stored
     * @param numNodes Total number of nodes of the graph
     */
    Graph(string filename, int numNodes) : numNodes(numNodes)
    {
        adjacencyList.resize(numNodes);
        string line;

        // If it is a real-world graph it also has a nodes file to read from
        if (filename.find("world") != string::npos)
        {
            ifstream file(filename + "/nodes.csv");
            getline(file, line); // Skip the header line
            filename = filename + "/edges.csv";
            nodes.resize(numNodes);

            string sid, lon;
            int id;
            double latitude, longitude;

            // Populate the graph with nodes from the CSV file
            while (getline(file, line))
            {
                stringstream iss(line);
                getline(iss, sid, ',');
                getline(iss, lon, ',');
                iss >> latitude;

                id = stoi(sid);
                longitude = stod(lon);

                nodes[id] = new Node{id, latitude, longitude};
            }
            file.close();
            // Pointless to be here since divide and conquer doesn't work
            // clusters = divideUsingKMeans(numNodes / stepSize);
        }

        ifstream file(filename);
        getline(file, line); // Skip the header line

        string src, dest;
        int source, destination;
        double weight;

        // Populate the graph with edges from the CSV file
        while (getline(file, line))
        {
            stringstream iss(line);
            getline(iss, src, ',');
            getline(iss, dest, ',');
            iss >> weight;

            source = stoi(src);
            destination = stoi(dest);

            Edge edge(source, destination, weight);
            adjacencyList[source].push_back(edge);
            Edge edge1(destination, source, weight);
            adjacencyList[destination].push_back(edge1);
        }
        file.close();
    }

    /**
     * @brief Get the Num Nodes object
     *
     * @return int Total number of nodes in the graph
     */
    int getNumNodes() const
    {
        return numNodes;
    }

    /**
     * @brief Get the Adj List object
     *
     * @return vector<list<Edge>> Adjacency List of the graph
     */
    vector<list<Edge>> getAdjList() const
    {
        return adjacencyList;
    }

    /**
     * @brief Get the Adjacency List of the especific node
     *
     * @param node Node of wich we want the adjacency list
     * @return list<Edge> Edges to the "neighbors" of the node
     */
    list<Edge> getNeighbors(int node) const
    {
        return adjacencyList[node];
    }

    /**
     * @brief Get the distance betteen two nodes
     *
     * @param source Id of node1
     * @param destination Id of node2
     * @param fake Flag to distinguish if the function can or not use the nodes coordinates to calculate the distance betweeen them in case the edge between them doesn't exist.
     * @return double distance between node1 and node2
     */
    double getDistance(int source, int destination, bool fake) const
    {
        // Assuming the adjacency list stores pairs of (destination, weight)
        for (const auto edge : adjacencyList[source])
        {
            if (edge.destination == destination)
            {
                return edge.weight;
            }
        }
        double weight;
        if (!nodes.empty() && fake)
            return haversine(nodes[source]->latitude, nodes[source]->longitude, nodes[destination]->latitude, nodes[destination]->longitude);

        return numeric_limits<double>::infinity();
    }

    /**
     * @brief Get the Nodes vector (only for real-world graphs)
     *
     * @return vector<Node *> vector of nodes of the graph
     */
    vector<Node *> getNodes()
    {
        return nodes;
    }

    /**
     * @brief Get the Clusters vector
     *
     * @return vector<vector<int>> vector of wich cluster every node is assigned to
     */
    vector<vector<int>> getClusters()
    {
        return clusters;
    }

    /**
     * @brief Calculates the path's length
     *
     * @param path Path for wich we will calculate the length
     * @param fake Flag to distinguish if the function can or not use the nodes coordinates to calculate the distance betweeen them in case the edge between them doesn't exist.
     * @return double Path's total length
     */
    double calculatePathLength(vector<int> path, bool fake) const
    {
        int curNode = path.back();
        double length = 0.0;
        path.pop_back();

        while (!path.empty())
        {
            length += getDistance(path.back(), curNode, fake);
            curNode = path.back();
            path.pop_back();
        }
        return length;
    }

    /**
     * @brief Creates a minimal spanning tree for the graph
     *
     * @param startNode Initial Node
     * @return Graph A graph with only the mst edges
     */
    Graph createMST(int startNode) const
    {
        Graph mstGraph;
        mstGraph.numNodes = numNodes;
        vector<bool> visited(numNodes, false);
        mstGraph.adjacencyList.resize(numNodes);
        priority_queue<Edge, vector<Edge>, CompareEdges> pq;

        visited[startNode] = true;
        for (const Edge &edge : adjacencyList[startNode])
        {
            pq.push(edge);
        }

        while (!pq.empty())
        {
            Edge minEdge = pq.top();
            pq.pop();

            int destination = minEdge.destination;

            // If the destination node is already visited, skip this edge
            if (visited[destination])
                continue;

            visited[destination] = true;
            mstGraph.adjacencyList[minEdge.source].push_back(minEdge);

            for (const Edge &edge : adjacencyList[destination])
            {
                if (!visited[edge.destination])
                {
                    pq.push(edge);
                }
            }
        }

        return mstGraph;
    }

    /**
     * @brief K-means algorithm to divide the problem into smaller subproblems
     *
     * @param k Number of clusters to divide the nodes
     * @return vector<vector<int>> Nodes divided into clusters
     */
    vector<vector<int>> divideUsingKMeans(int k)
    {
        vector<Node> centroids = initializeCentroids(k);
        vector<int> clusterAssignments(getNumNodes(), -1);

        bool converged = false;
        while (!converged)
        {
            vector<int> prevClusterAssignments = clusterAssignments;

            assignNodesToCentroids(centroids, clusterAssignments);
            updateCentroids(clusterAssignments, centroids);

            converged = hasConverged(prevClusterAssignments, clusterAssignments);
        }

        vector<vector<int>> subproblemClusters(k);
        for (int nodeIndex = 0; nodeIndex < getNumNodes(); ++nodeIndex)
        {
            int clusterIndex = clusterAssignments[nodeIndex];
            subproblemClusters[clusterIndex].push_back(nodeIndex);
        }

        return subproblemClusters;
    }
};

#endif // GRAPH_H
