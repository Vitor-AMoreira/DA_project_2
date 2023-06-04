//
// Created by Vitor on 16/05/2023.
//

#include <conio.h>
#include "Menu.h"

Menu::Menu() {
    showMenu();
}

void Menu::clearBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}

void Menu::showMenu() {
    cout << " ____________________________________ " << endl;
    cout << "| --- What would you like to do? --- |" << endl;
    cout << "| 1 - Data Set                       |" << endl;
    cout << "| 2 - Functionalities                |" << endl;
    cout << "| 0 - Exit                           |" << endl;
    cout << "|____________________________________|" << endl;
    cout << "Option: ";
    cin >> menuOption;
    clearBuffer();
}


void Menu::showMenuOpt1() {
    cout << " ______________________________________________________" << endl;
    cout << "| --- Choose the category of graph you want to use --- |" << endl;
    cout << "| 1 - Toy-Graphs                                       |" << endl;
    cout << "| 2 - Real-world Graphs                                |" << endl;
    cout << "| 3 - Extra_Fully_Connected_Graphs                     |" << endl;
    cout << "| 0 - Go to main menu                                  |" << endl;
    cout << "|______________________________________________________|" << endl;
    cout << "Option: ";
    cin >> menuOption;
    clearBuffer();
}

void Menu::showMenuOpt1_1() {
    cout << " _________________________________________" << endl;
    cout << "| --- Choose the file you want to use --- |" << endl;
    cout << "| 1 - Shipping                            |" << endl;
    cout << "| 2 - Tourism                             |" << endl;
    cout << "| 3 - Stadiums                            |" << endl;
    cout << "| 0 - Go to main menu                     |" << endl;
    cout << "|_________________________________________|" << endl;
    cout << "Option: ";
    cin >> menuOption;
    clearBuffer();

}

void Menu::showMenuOpt1_2() {
    cout << " _________________________________________" << endl;
    cout << "| --- Choose the file you want to use --- |" << endl;
    cout << "| 1 - Graph 1                             |" << endl;
    cout << "| 2 - Graph 2                             |" << endl;
    cout << "| 3 - Graph 3                             |" << endl;
    cout << "| 0 - Go to main menu                     |" << endl;
    cout << "|_________________________________________|" << endl;
    cout << "Option: ";
    cin >> menuOption;
    clearBuffer();
}

void Menu::showMenuOpt1_3() {
    cout << " _________________________________________" << endl;
    cout << "| --- Choose the file you want to use --- |" << endl;
    cout << "| 1 - Edges_25                            |" << endl;
    cout << "| 2 - Edges_50                            |" << endl;
    cout << "| 3 - Edges_75                            |" << endl;
    cout << "| 4 - Edges_100                           |" << endl;
    cout << "| 5 - Edges_200                           |" << endl;
    cout << "| 6 - Edges_300                           |" << endl;
    cout << "| 7 - Edges_400                           |" << endl;
    cout << "| 8 - Edges_500                           |" << endl;
    cout << "| 9 - Edges_600                           |" << endl;
    cout << "| 10 - Edges_700                          |" << endl;
    cout << "| 11 - Edges_800                          |" << endl;
    cout << "| 12 - Edges_900                          |" << endl;
    cout << "| 0 - Go to main menu                     |" << endl;
    cout << "|_________________________________________|" << endl;
    cout << "Option: ";
    cin >> menuOption;
    clearBuffer();

}

void Menu::showMenuOpt2() {
    cout << endl;
    cout << " __________________________________________________ " << endl;
    cout << "| --- Choose the functionality you want to use --- |" << endl;
    cout << "| 1 - Backtracking Algorithm                       |" << endl;
    cout << "| 2 - Triangular Approximation Heuristic           |" << endl;
    cout << "| 3 - Our Heuristic                                |" << endl;
    cout << "| 0 - Go to main menu                              |" << endl;
    cout << "|__________________________________________________|" << endl;
    cout << "Option: ";
    cin >> menuOption;
    clearBuffer();
}

//Back tracking algorithm
void Menu::showMenuOpt2_1(Graph graph) {

    cout << endl;
    cout << "Back tracking algorithm running..." << endl << endl;

    // Start the clock
    auto start = std::chrono::high_resolution_clock::now();

    double shortest_path = solveTSP(graph);

    cout << "Shortest path found: " << shortest_path << endl;

    // Stop the clock
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    chrono::duration<double> duration = end - start;

    // Convert duration to seconds
    double durationInSeconds = duration.count();
    cout << "Time taken to run the algorithm: " << durationInSeconds << " seconds" << endl;
    cout << endl << "Press any key to return to main menu" << endl;
    _getch();
}

void Menu::showMenuOpt2_2(Graph graph) {

    cout << endl;
    cout << "Triangular approximation heuristic running..." << endl << endl;

    // Start the clock
    auto start = std::chrono::high_resolution_clock::now();

    vector<Node*> path = tspTriangularApproximation(graph);
    double distance = 0;
    cout << "Best path found: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->index << " ";
        double newDistance = graph.getDistance(path[i], path[i+1]);
        if(newDistance == numeric_limits<double>::infinity()) {
            newDistance = calculateDistance(path[i], path[i+1], graph);
        }
        distance += newDistance;
        if(path[i+1] == path.back()) {
            cout << path[i+1]->index << endl;
            break;
        }
    }
    cout << "Shortest distance found: " << distance << endl;


    // Stop the clock
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    chrono::duration<double> duration = end - start;

    // Convert duration to seconds
    double durationInSeconds = duration.count();
    cout << "Time taken to run the algorithm: " << durationInSeconds << " seconds" << endl;
    cout << endl << "Press any key to return to main menu" << endl;
    _getch();
}