/**
 * @file TSPAlgorithms.cpp
 * @author G04_T07
 * @brief This file handles the TSP algorithms
 * @version 0.1
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "Graph.h"
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

/**
 * @brief Bactracking algorithm.
 *
 * @see backtrackTSP()
 *
 * @param graph Graph where all the data is stored.
 * @param path Path placeholder, where to build the path for later checking it's length.
 * @param visited Vector that stores the visited state of each node.
 * @param currentNode Node where the algorithm is at in this iteration.
 * @param currentCost Length of the current path
 * @param minCost Smallest length of the full path already found.
 */
static void backtrackTSPHelper(const Graph *graph, vector<int> &path, vector<bool> &visited, int currentNode, double currentCost, double *minCost)
{
    // Base case: All nodes visited, return to the starting node
    if (path.size() == visited.size())
    {
        currentCost += graph->getDistance(currentNode, path.front(), false);

        // Update the minimum cost if a better path is found
        *minCost = min(currentCost, *minCost);
        return;
    }
    // Recursive case: Try visiting unvisited nodes
    for (auto neighbor : graph->getNeighbors(currentNode))
    {
        if (!visited[neighbor.destination])
        {
            visited[neighbor.destination] = true;
            path.push_back(neighbor.destination);
            currentCost += neighbor.weight;

            // Explore the next node in the path
            backtrackTSPHelper(graph, path, visited, neighbor.destination, currentCost, minCost);

            // Backtrack: Remove the visited node from the path and reset the visited and cost values
            path.pop_back();
            visited[neighbor.destination] = false;
            currentCost -= neighbor.weight;
        }
    }
}

/**
 * @brief Bactracking algorithm preparation.
 *
 * @see backtrackTSPHelper()
 *
 * @param graph Graph where all the data is stored.
 * @return double Minimal path length found. Travelling salesman solution cost.
 */
static double backtrackTSP(const Graph *graph)
{
    int numNodes = graph->getNumNodes();
    vector<bool> visited(numNodes, false);               // Track visited nodes
    vector<int> path;                                    // Store the current path
    double minCost = numeric_limits<double>::infinity(); // Initialize minimum cost with a large value

    visited[0] = true;
    path.push_back(0);

    backtrackTSPHelper(graph, path, visited, 0, 0.0, &minCost);

    return minCost;
}

/**
 * @brief Function to find the closest node to the current node.
 *
 * @see triangularApproximation()
 *
 * @param graph Graph where all the data is stored.
 * @param curNode Current Node
 * @param visited Vector that stores the visited state of each node.
 * @return int The closest node to the current node.
 */
static int findMin(Graph *graph, int curNode, const vector<bool> &visited)
{
    int minIndex = -1;
    double minValue = numeric_limits<double>::infinity();

    for (int id = 0; id < graph->getNumNodes(); id++)
    {
        if (!visited[id] && graph->getDistance(curNode, id, true) < minValue)
        {

            minValue = graph->getDistance(curNode, id, true);
            minIndex = id;
        }
    }
    return minIndex;
}

/**
 * @brief Function to find the closest node to the current node. (Only using nodes from path)
 *
 * @see divideAndConquer()
 *
 * @param graph Graph where all the data is stored.
 * @param path Vector of nodes from wich it can search the closest
 * @param curNode Current Node
 * @param visited Vector that stores the visited state of each node.
 * @return int The closest node from path to the current node.

 */
static int findMin(Graph *graph, vector<int> path, int curNode, const vector<bool> &visited)
{
    int minIndex = -1;
    double minValue = numeric_limits<double>::infinity();

    for (int i = 0; i < path.size(); i++)
    {
        if (!visited[path[i]] && graph->getDistance(curNode, path[i], true) < minValue)
        {

            minValue = graph->getDistance(curNode, path[i], true);
            minIndex = path[i];
        }
    }
    return minIndex;
}

/**
 * @brief Triangular Aproximation Algorithm
 *
 * @param graph Graph where all the data is stored.
 * @return double Minimal path found. Best path length found using triangular aproximation heuristic.
 */
static double triangularApproximation(Graph *graph)
{
    int n = graph->getNumNodes();
    double minCost = numeric_limits<double>::infinity();
    vector<bool> visited(n, false);
    vector<int> path;
    path.push_back(0);
    bool end = false;

    while (path.size() < n && !end)
    {
        int curNode = path.back();
        visited[curNode] = true;
        int nextNode = findMin(graph, curNode, visited);
        if (nextNode != -1)
            path.push_back(nextNode);
        else
            end = true;
    }
    path.push_back(0);
    if (!end)
        minCost = min(minCost, graph->calculatePathLength(path, true));
    return minCost;
}

/**
 * @brief Depth First Search algorithm
 *
 * @param graph Graph where all the data is stored.
 * @param currentNode Current Node
 * @param visited Vector that stores the visited state of each node.
 * @param path Variable where the path is going to be built on
 */
static void dfs(const Graph &graph, int currentNode, vector<int> &visited, vector<int> &path)
{
    visited[currentNode] = true;
    path.push_back(currentNode);
    // Iterate over the neighbors of the current node
    for (const auto &neighbor : graph.getNeighbors(currentNode))
    {
        if (!visited[neighbor.destination])
        {
            dfs(graph, neighbor.destination, visited, path); // Recursively visit the unvisited neighbor
        }
    }
}

/**
 * @brief Minimal Spanning Tree based algorithm
 *
 * @see dfs()
 *
 * @param graph Graph where all the data is stored.
 * @return double Minimal path found. Best path length found using minimal spanning tree algorithm.
 */
static double mstApproximation(Graph *graph)
{
    vector<int> path, visited(graph->getNumNodes(), false);
    dfs(graph->createMST(0), 0, visited, path);
    path.push_back(path.front());
    return graph->calculatePathLength(path, false);
}

/**
 * @brief Lin-Kernighan Algorithm
 *
 * @param graph Graph where all the data is stored.
 * @param initialPath Intial path where to improve from
 */
static void linKernighan(const Graph *graph, const vector<int> &initialPath)
{
    // Initialize the current best path with the initial path
    vector<int> bestPath = initialPath;
    double bestLength = graph->calculatePathLength(initialPath, false);

    // Start the Lin-Kernighan optimization process
    bool improvement = true;
    while (improvement)
    {
        improvement = false;

        // Iterate over all possible pairs of edges in the path
        for (int i = 0; i < graph->getNumNodes() - 1; ++i)
        {
            for (int j = i + 1; j < graph->getNumNodes(); ++j)
            {
                // Check if reversing the edges between i and j leads to an improved path
                vector<int> newPath = bestPath;
                reverse(newPath.begin() + i + 1, newPath.begin() + j + 1);
                double newLength = graph->calculatePathLength(newPath, false);

                // Update the current best path if the new path is better
                if (newLength < bestLength)
                {
                    bestPath = newPath;
                    bestLength = newLength;
                    improvement = true;
                }
            }
        }
    }
}

/**
 * @brief Merges a vector of paths together to make the smallest path possible
 *
 * @param graph Graph where all the data is stored.
 * @param paths Paths to be merged together
 * @return vector<int> Minimal path found
 */
static vector<int> mergeSubpaths(Graph *graph, vector<vector<int>> paths)
{
    vector<int> mergedPath;

    // Find the subpath with the smallest path distance
    int smallestIndex = 0;
    double smallestDistance = graph->calculatePathLength(paths[0], false);
    for (int i = 1; i < paths.size(); ++i)
    {
        double distance = graph->calculatePathLength(paths[i], false);
        if (distance < smallestDistance)
        {
            smallestIndex = i;
            smallestDistance = distance;
        }
    }

    // Merge the paths starting from the smallest subpath
    mergedPath = paths[smallestIndex];
    paths.erase(paths.begin() + smallestIndex);

    while (!paths.empty())
    {
        int bestSubpathIndex = -1;
        int bestInsertionIndex = -1;
        double bestInsertionCost = numeric_limits<double>::infinity();

        // Find the best subpath and the best insertion point
        for (int i = 0; i < paths.size(); ++i)
        {
            const vector<int> subpath = paths[i];
            for (int j = 0; j <= subpath.size(); ++j)
            {
                vector<int> mergedTemp = mergedPath;
                mergedTemp.insert(mergedTemp.begin() + j, subpath.begin(), subpath.end());
                double insertionCost = graph->calculatePathLength(mergedTemp, false);
                if (insertionCost < bestInsertionCost)
                {
                    bestSubpathIndex = i;
                    bestInsertionIndex = j;
                    bestInsertionCost = insertionCost;
                }
            }
        }

        // Merge the best subpath into the merged path
        const vector<int> &bestSubpath = paths[bestSubpathIndex];
        mergedPath.insert(mergedPath.begin() + bestInsertionIndex, bestSubpath.begin(), bestSubpath.end());
        paths.erase(paths.begin() + bestSubpathIndex);
    }

    return mergedPath;
}

/**
 * @brief Divide and Conquer Algorithm
 *
 * @see divideUsingKMeans()
 * @see mergeSubpaths()
 * @see linKernighan()
 *
 * @param graph Graph where all the data is stored.
 * @return double Minimal path found. Best path length found using divide and conquer heuristic.
 */
static double divideAndConquer(Graph *graph)
{
    vector<vector<int>> paths(graph->getClusters().size());
    vector<bool> visited(graph->getNumNodes(), false);
    for (int i = 0; i < graph->getClusters().size(); i++)
    {
        bool end = false;
        paths[i].push_back(graph->getClusters()[i].front());
        while (paths[i].size() < graph->getClusters()[i].size())
        {
            int curNode = paths[i].back();
            visited[curNode] = true;
            int nextNode = findMin(graph, graph->getClusters()[i], curNode, visited);
            if (nextNode != -1)
                paths[i].push_back(nextNode);
            else
                end = true;
        }
    }
    vector<int> path = mergeSubpaths(graph, paths); // (0xC0000374) Error... Heap Corruption
    linKernighan(graph, path);
    return graph->calculatePathLength(path, false);
}
