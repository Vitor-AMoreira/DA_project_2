#include <iostream>
#include "Graph.h"
#include "Menu.h"

using namespace std;

int main()
{
    // Create a graph
    Graph graph;

    // Create a menu object
    Menu menu = Menu();

    menu.displayMenu(&graph);
}
