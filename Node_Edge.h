//
// Created by Vitor on 16/05/2023.
//

#ifndef DA_PROJECT_2_NODE_EDGE_H
#define DA_PROJECT_2_NODE_EDGE_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Node {
public:
    int index;
    double latitude;
    double longitude;

    Node(string index);
    Node(string index, string longitude, string latitude);

    void print();
};

class Edge {
public:
    Node* source;
    Node* target;
    double distance;

    Edge(Node* source, Node* target, double distance);
};

#endif //DA_PROJECT_2_NODE_EDGE_H
