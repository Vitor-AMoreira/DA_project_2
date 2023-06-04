/**
 * @file Menu.h
 * @author G04_T07
 * @brief This file handles the menu.
 * @version 0.1
 * @date 2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <chrono>
#include "Graph.h"
#include "TSPAlgorithms.cpp"

/**
 * @brief Class that encapsulates the menu interface.
 *
 */
class Menu
{
public:
    /**
     * @brief Function to clear input buffer.
     *
     * Calls cin.clear() and cin.ignore().
     */
    void clearBuffer();

    /**
     * @brief Construct a new Menu object
     *
     */
    Menu();

    /**
     * @brief Prints the various main menu options available on screen.
     *
     * @param graph The graph in wich we want to do any operation.
     */
    void displayMenu(Graph *graph);

    /**
     * @brief Handles what to do when the user chooses an option
     *
     * @param graph The graph in wich we want to do any operation.
     */
    void handleSelection(Graph *graph);

private:
    /**
     * @brief Prints the various read menu options available on screen.
     *
     * @param graph The graph in wich we want to do any operation.
     */
    void displayMenuReadDataSet(Graph *graph);

    /**
     * @brief Handles what to do when the user chooses the read option
     *
     * @param graph The graph in wich we want to do any operation.
     * @param end When this flag is true goes back to main menu
     */
    void handleReadCSV(Graph *graph, bool &end);

    /**
     * @brief
     *
     * @param graph The graph in wich we want to do any operation.
     */
    void displayMenuTSPAlgorithms(Graph *graph);

    /**
     * @brief Handles what to do when the user chooses the TSP algorithms option
     *
     * @param graph The graph in wich we want to do any operation.
     * @param end When this flag is true goes back to main menu
     */
    void handleTSPAlgorithms(Graph *graph, bool &end);

    /**
     * @brief Handles what to do when the user chooses the Toy Graphs option
     *
     * @param graph The graph in wich we want to do any operation.
     * @param end When this flag is true goes back to main menu
     */
    void handleToyGraphs(Graph *graph, bool &end);

    /**
     * @brief Handles what to do when the user chooses the Real World Graphs option
     *
     * @param graph The graph in wich we want to do any operation.
     * @param end When this flag is true goes back to main menu
     */
    void handleRealWorldGraphs(Graph *graph, bool &end);

    /**
     * @brief Handles what to do when the user chooses the Extra Fully Connected Graphs option
     *
     * @param graph The graph in wich we want to do any operation.
     * @param end When this flag is true goes back to main menu
     */
    void handleExtraFullyConnectedGraphs(Graph *graph, bool &end);

    /**
     * @brief Handles what to do when the user chooses the backtracking option
     *
     * @param graph The graph in wich we want to do any operation.
     */
    void handleTSPBacktracking(Graph *graph);

    /**
     * @brief Handles what to do when the user chooses the triangular approximation option
     *
     * @param graph The graph in wich we want to do any operation.
     */
    void handleTriangularApproximation(Graph *graph);

    /**
     * @brief Handles what to do when the user chooses the mst approximation option
     *
     * @param graph The graph in wich we want to do any operation.
     */
    void handleMSTApproximation(Graph *graph);

    /**
     * @brief Handles what to do when the user chooses the divide and conquer option
     *
     * @param graph The graph in wich we want to do any operation.
     */
    void handleDivideAndConquer(Graph *graph);

    /**
     * @brief Get the option chosen by the user
     *
     * @return int
     */
    int getUserChoice();

    /**
     * @brief Get the file number chosen by the user
     *
     * @param numFiles
     * @return int
     */
    int getFileNumber(int numFiles);
};

#endif // MENU_H