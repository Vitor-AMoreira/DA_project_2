//
// Created by Vitor on 16/05/2023.
//

#include "Graph.h"
#include "Node_Edge.h"
#include <chrono>

Graph::Graph() {}

Graph::Graph(string graph_file) {
    setEmptyGraph();

    auto start = std::chrono::high_resolution_clock::now();

    if(graph_file.find("Toy-Graphs") != std::string::npos) {
        readToyGraphs(graph_file);
        cout << "readToyGraphs" << endl;
    } else if(graph_file.find("world") != std::string::npos) {
        readRealWorldGraphs(graph_file);
        cout << "readRealWorldGraphs" << endl;
    } else if(graph_file.find("Extra_Fully_Connected_Graphs") != std::string::npos) {
        readExtraFullyConnectedGraphs(graph_file);
        cout << "readExtraFullyConnectedGraphs" << endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    double durationInSeconds = duration.count();

    if(!empty_graph) {
        cout << endl << "Data set read successfully!" << endl;
        cout << "Time taken to create the graph: " << durationInSeconds << " seconds" << endl;
    }
}

vector<Node*> Graph::getNodes() {
    vector<Node*> nodes_vector;
    for(auto it:nodes) {
        nodes_vector.push_back(it.second);
    }
    return nodes_vector;
}

vector<Edge> Graph::getEdges() {
    return edges;
}

bool Graph::getEmptyGraph() {
    return empty_graph;
}

void Graph::setEmptyGraph() {
    empty_graph = !empty_graph;
    nodes = {};
    edges = {};
}

bool isNumeric(string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false && str[i] != '.') return false;
    return true;
}

void Graph::readToyGraphs(string graph_file) {

    ifstream file(graph_file);
    string line;
    // Read and parse the CSV file
    bool isFirstRow = true;
    while (getline(file, line)) {
        stringstream ss(line);

        string source, target;
        double distance;

        if (isFirstRow) {
            isFirstRow = false;
            continue;  // Skip the first row
        }

        getline(ss, source, ',');
        getline(ss, target, ',');
        ss >> distance;

        if(!isNumeric(source) || !isNumeric(target)) break;

        int int_source = stoi(source);
        int int_target = stoi(target);

        // Create nodes if they don't exist
        if (nodes.find(int_source) == nodes.end())
            addNode(source);
        if (nodes.find(int_target) == nodes.end())
            addNode(target);

        // Add edge to the graph
        addEdge(nodes[int_source], nodes[int_target], distance);
    }

    // Close the file
    file.close();
}

void Graph::readRealWorldGraphs(string graph_file) {

    ifstream edges_file(graph_file + "/edges.csv");
    string line;

    //To read the edges file
    bool isFirstRow = true;
    while (getline(edges_file, line)) {
        stringstream ss(line);
        string source, target;
        double distance;

        if(line.size() < 5) break;

        if (isFirstRow) {
            isFirstRow = false;
            continue;  // Skip the first row
        }


        getline(ss, source, ',');
        getline(ss, target, ',');
        ss >> distance;

        if(!isNumeric(source) || !isNumeric(target)) break;

        int int_source = stoi(source);
        int int_target = stoi(target);

        // Create nodes if they don't exist
        if (nodes.find(int_source) == nodes.end())
            addNode(source);
        if (nodes.find(int_target) == nodes.end())
            addNode(target);

        // Add edge to the graph
        addEdge(nodes[int_source], nodes[int_target], distance);
    }
    // Close the file
    edges_file.close();

    //To read the nodes file
    ifstream nodes_file(graph_file + "/nodes.csv");

    isFirstRow = true;
    while (getline(nodes_file, line)) {
        stringstream ss(line);
        string index, latitude, longitude;
        double distance;

        if(line.size() < 5) break;

        if (isFirstRow) {
            isFirstRow = false;
            continue;  // Skip the first row
        }

        getline(ss, index, ',');
        getline(ss, longitude, ',');
        ss >> latitude;

        if(!isNumeric(index)) break;

        int int_index = stoi(index);

        // Create nodes if they don't exist
        if (nodes.find(int_index) == nodes.end()) {
            cout << "The node: " << index << " was not created previously!" << endl;
            continue;
        } else {
            addNodeWithCoords(index, longitude, latitude);
        }
    }
    // Close the file
    nodes_file.close();
}

void Graph::readExtraFullyConnectedGraphs(string graph_file) {
    ifstream file(graph_file);
    string line;
    int i = 0;
    // Read and parse the CSV file
    while (getline(file, line)) {

        if (line.empty() || line.find_first_not_of(' ') == string::npos) {
            continue;
        }
        stringstream ss(line);
        string source, target;
        double distance;

//        if(line.size() < 5) break;
        getline(ss, source, ',');
        getline(ss, target, ',');
        ss >> distance;

        if(!isNumeric(source) || !isNumeric(target)) break;

        int int_source = stoi(source);
        int int_target = stoi(target);

        // Create nodes if they don't exist
        if (nodes.find(int_source) == nodes.end())
            addNode(source);
        if (nodes.find(int_target) == nodes.end())
            addNode(target);

        // Add edge to the graph
        addEdge(nodes[int_source], nodes[int_target], distance);
    }

    // Close the file
    file.close();
}

double Graph::getDistance(Node* source, Node* target) {
    for (const auto& edge : getEdges()) {
        if ((edge.source == source && edge.target == target) || (edge.source == target && edge.target == source)) {
            return edge.distance;
        }
    }

    // If no edge is found between the source and target nodes, return a placeholder distance
    return numeric_limits<double>::infinity();

}

void Graph::addNode(const string& index) {
    int int_index = stoi(index);
    nodes[int_index] = new Node{index};
}

void Graph::addNodeWithCoords(string index, string longitude, string latitude) {
    int int_index = stoi(index);
    nodes[int_index] = new Node{index, longitude, latitude};
}

void Graph::addEdge(Node* source, Node* target, double distance) {
    edges.push_back(Edge(source, target, distance));
    edges.push_back(Edge(target, source, distance));
}

void Graph::printGraph() {
    cout << "Nodes:" << endl;
    for (const auto& pair : nodes) {
        pair.second->print();
    }

    cout << "Edges:" << endl;
    for (const auto& edge : edges) {
        cout << edge.source->index << " -> " << edge.target->index
             << " (distance: " << edge.distance << ")" << endl;
    }
}


