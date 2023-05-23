//
// Created by Vitor on 16/05/2023.
//

#ifndef DA_PROJECT_2_GRAPH_H
#define DA_PROJECT_2_GRAPH_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include "Node_Edge.h"
#include <map>

class Graph {
private:
    unordered_map<int, Node*> nodes;
    vector<Edge> edges;
    bool empty_graph = true;
public:
    Graph();
    Graph(string graph_file);

    vector<Node*> getNodes();
    vector<Edge> getEdges();

    bool getEmptyGraph();
    void setEmptyGraph();

    void readToyGraphs(string graph_file);
    void readRealWorldGraphs(string graph_file);
    void readExtraFullyConnectedGraphs(string graph_file);

    void addNode(const string& index);
    void addNodeWithCoords(string index, string longitude, string latitude);

    void addEdge(Node* source, Node* target, double distance);

    void printGraph();

};

#endif //DA_PROJECT_2_GRAPH_H
