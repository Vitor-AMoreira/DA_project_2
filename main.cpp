#include <iostream>

#include "Graph.h"
#include "Menu.h"

using namespace std;

int main() {
    Graph graph;
    while(true) {
        Menu menu;
        if(menu.menuOption == 0) break;

        //Read graph data
        if(menu.menuOption == 1) {
            menu.showMenuOpt1();
            if(menu.menuOption == 0) continue;
            //Read Toy-Graphs files
            if(menu.menuOption == 1) {
                menu.showMenuOpt1_1();
                if(menu.menuOption == 0) continue;
                else if(menu.menuOption == 1) {
                    graph = Graph("../Toy-Graphs/Toy-Graphs/shipping.csv");
                } else if(menu.menuOption == 2) {
                    graph = Graph("../Toy-Graphs/Toy-Graphs/tourism.csv");
                } else if(menu.menuOption == 3) {
                    graph = Graph("../Toy-Graphs/Toy-Graphs/stadiums.csv");
                } else {
                    cout << "Wrong input. Try again!" << endl;
                    continue;
                }
              //Read Real-world Graphs files
            } else if(menu.menuOption == 2) {
                menu.showMenuOpt1_2();
                if(menu.menuOption == 0) continue;
                else if(menu.menuOption == 1) {
                    graph = Graph("../Real-world Graphs/Real-world Graphs/graph1");
                } else if(menu.menuOption == 2) {
                    graph = Graph("../Real-world Graphs/Real-world Graphs/graph2");
                } else if(menu.menuOption == 3) {
                    graph = Graph("../Real-world Graphs/Real-world Graphs/graph3");
                } else {
                    cout << "Wrong input. Try again!" << endl;
                    continue;
                }
              // Read Extra_Fully_Connected_Graphs files
            } else if(menu.menuOption == 3) {
                menu.showMenuOpt1_3();
                if(menu.menuOption == 0) continue;
                else if(menu.menuOption == 1) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv");
                } else if(menu.menuOption == 2) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_50.csv");
                } else if(menu.menuOption == 3) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_75.csv");
                } else if(menu.menuOption == 4) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_100.csv");
                } else if(menu.menuOption == 5) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_200.csv");
                } else if(menu.menuOption == 6) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_300.csv");
                } else if(menu.menuOption == 7) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_400.csv");
                } else if(menu.menuOption == 8) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_500.csv");
                } else if(menu.menuOption == 9) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_600.csv");
                } else if(menu.menuOption == 10) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_700.csv");
                } else if(menu.menuOption == 11) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_800.csv");
                } else if(menu.menuOption == 12) {
                    graph = Graph("../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_900.csv");
                } else {
                    cout << "Wrong input. Try again!" << endl;
                    continue;
                }
            } else {
                cout << "Wrong input. Try again!" << endl;
                continue;
            }
            cout << endl << "Data set read successfully!" << endl;
          //Functionalities
        } else if(menu.menuOption == 2 && !graph.getEmptyGraph()) {
            menu.showMenuOpt2();
            if(menu.menuOption == 0) continue;
            else if(menu.menuOption == 1) {
                menu.showMenuOpt2_1(graph);
            }
        } else if(graph.getEmptyGraph()) {
            cout << "You must read a graph from the csv files before using any other operation!" << endl;
            continue;
        }
    }
    return 0;
}