//
// Created by Vitor on 16/05/2023.
//

#include "Node_Edge.h"


Node::Node(string index) {
    this->index = stoi(index);
}

Node::Node(string index, string longitude, string latitude) {
    this->index = stoi(index);
    this->longitude = longitude;
    this->latitude = latitude;
}

void Node::print() {
    cout << "|" << setw(20) <<  index << "|" << setw(20) << latitude << "|" << setw(20) << longitude << "|" << endl;
}

Edge::Edge(Node* source, Node* target, double distance) {
    this->source = source;
    this->target = target;
    this->distance = distance;
};