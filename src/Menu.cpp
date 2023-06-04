#include "Menu.h"

using namespace std;

void Menu::clearBuffer()
{
    cin.clear();
    cin.ignore(1000, '\n');
}

Menu::Menu() = default;

void Menu::displayMenu(Graph *graph)
{
    cout << "Welcome to the Traveling Salesman Problem Solver!" << endl;

    while (true)
    {
        cout << "What would you like to do?" << endl;
        cout << "1. Read data set" << endl;
        cout << "2. Use algorithms" << endl;
        cout << "0. Exit" << endl;

        handleSelection(graph);
        cout << endl;
        clearBuffer();
    }
}

void Menu::handleSelection(Graph *graph)
{
    int selection = getUserChoice();

    switch (selection)
    {
    case 0:
        cout << "Exiting the program. Goodbye!" << endl;
        exit(0);
        break;
    case 1:
        displayMenuReadDataSet(graph);
        break;
    case 2:
        displayMenuTSPAlgorithms(graph);
        break;
    default:
        cout << "Invalid selection. Please try again." << endl;
    }
}

void Menu::displayMenuReadDataSet(Graph *graph)
{
    cout << "Read Data Set" << endl;
    bool end = false;
    while (!end)
    {
        cout << "Choose the category of graph you want to use" << endl;
        cout << "1. Toy-Graphs" << endl;
        cout << "2. Real-world Graphs" << endl;
        cout << "3. Extra_Fully_Connected_Graphs" << endl;
        cout << "0. Exit" << endl;

        handleReadCSV(graph, end);
        cout << endl;
    }
}

void Menu::handleReadCSV(Graph *graph, bool &end)
{
    int selection = getUserChoice();

    switch (selection)
    {
    case 1:
        handleToyGraphs(graph, end);
        break;
    case 2:
        handleRealWorldGraphs(graph, end);
        break;
    case 3:
        handleExtraFullyConnectedGraphs(graph, end);
        break;
    case 0:
        end = true;
        break;
    default:
        cout << "Invalid selection. Please try again." << endl;
    }
}

void Menu::displayMenuTSPAlgorithms(Graph *graph)
{
    bool end = false;
    while (!end)
    {
        cout << "Choose the algorithm you want to use" << endl;
        cout << "1. Backtracking" << endl;
        cout << "2. Triangular Approximation" << endl;
        cout << "3. MST-based Algorithm" << endl;
        cout << "4. Divide and Conquer Algorithm (Only for Real-World graphs) (not working)" << endl;
        cout << "0. Exit" << endl;

        handleTSPAlgorithms(graph, end);
        cout << endl;
    }
}

void Menu::handleTSPAlgorithms(Graph *graph, bool &end)
{
    int selection = getUserChoice();

    switch (selection)
    {
    case 1:
        handleTSPBacktracking(graph);
        break;
    case 2:
        handleTriangularApproximation(graph);
        break;
    case 3:
        handleMSTApproximation(graph);
        break;
    case 4:
        handleDivideAndConquer(graph);
        break;
    case 0:
        end = true;
        break;
    default:
        cout << "Invalid selection. Please try again." << endl;
    }
}

void Menu::handleToyGraphs(Graph *graph, bool &end)
{
    cout << "Choose the data set you want to use" << endl;
    cout << "1. Tourism" << endl;
    cout << "2. Stadiums" << endl;
    cout << "3. Shipping" << endl;
    int fileNumber = getFileNumber(3);
    // Handle the selected file from the Toy-Graphs group
    switch (fileNumber)
    {
    case 1:
        *graph = Graph("../graphs/Toy-Graphs/tourism.csv", 5);
        end = true;
        break;
    case 2:
        *graph = Graph("../graphs/Toy-Graphs/stadiums.csv", 11);
        end = true;
        break;
    case 3:
        *graph = Graph("../graphs/Toy-Graphs/shipping.csv", 14);
        end = true;
        break;
    default:
        cout << "Invalid selection. Please try again." << endl;
    }
}

void Menu::handleRealWorldGraphs(Graph *graph, bool &end)
{
    cout << "Choose the data set you want to use" << endl;
    cout << "1. 1000 nodes" << endl;
    cout << "2. 5000 nodes" << endl;
    cout << "3. 10000 nodes" << endl;
    int fileNumber = getFileNumber(3);
    // Handle the selected file from the Real-world Graphs group
    switch (fileNumber)
    {
    case 1:
        *graph = Graph("../graphs/Real-world Graphs/graph1", 1000);
        end = true;
        break;
    case 2:
        *graph = Graph("../graphs/Real-world Graphs/graph2", 5000);
        end = true;
        break;
    case 3:
        *graph = Graph("../graphs/Real-world Graphs/graph3", 10000);
        end = true;
        break;
    default:
        cout << "Invalid selection. Please try again." << endl;
    }
}

void Menu::handleExtraFullyConnectedGraphs(Graph *graph, bool &end)
{
    cout << "Choose the data set you want to use" << endl;
    cout << "1. 25 nodes" << endl;
    cout << "2. 50 nodes" << endl;
    cout << "3. 75 nodes" << endl;
    cout << "4. 100 nodes" << endl;
    cout << "5. 200 nodes" << endl;
    cout << "6. 300 nodes" << endl;
    cout << "7. 400 nodes" << endl;
    cout << "8. 500 nodes" << endl;
    cout << "9. 600 nodes" << endl;
    cout << "10. 700 nodes" << endl;
    cout << "11. 800 nodes" << endl;
    cout << "12. 900 nodes" << endl;
    int fileNumber = getFileNumber(12);
    // Handle the selected file from the Extra-Fully-Connected-Graphs group
    switch (fileNumber)
    {
    case 1:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_25.csv", 25);
        end = true;
        break;
    case 2:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_50.csv", 50);
        end = true;
        break;
    case 3:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_75.csv", 75);
        end = true;
        break;
    case 4:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_100.csv", 100);
        end = true;
        break;
    case 5:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_200.csv", 200);
        end = true;
        break;
    case 6:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_300.csv", 300);
        end = true;
        break;
    case 7:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_400.csv", 400);
        end = true;
        break;
    case 8:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_500.csv", 500);
        end = true;
        break;
    case 9:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_600.csv", 600);
        end = true;
        break;
    case 10:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_700.csv", 700);
        end = true;
        break;
    case 11:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_800.csv", 800);
        end = true;
        break;
    case 12:
        *graph = Graph("../graphs/Extra_Fully_Connected_Graphs/edges_900.csv", 900);
        end = true;
        break;
    default:
        cout << "Invalid selection. Please try again." << endl;
    }
}

void Menu::handleTSPBacktracking(Graph *graph)
{
    // Implement the TSP solving using Backtracking algorithm
    cout << "Solving TSP using Backtracking algorithm..." << endl;
    // Start the clock
    auto start = chrono::high_resolution_clock::now();

    double shortest_path = backtrackTSP(graph);

    cout << "Shortest distance: " << shortest_path << endl;

    // Stop the clock
    auto end = chrono::high_resolution_clock::now();

    // Calculate the duration
    chrono::duration<double> duration = end - start;

    // Convert duration to seconds
    double durationInSeconds = duration.count();
    cout << "Time taken to run the algorithm: " << durationInSeconds << " seconds" << endl;
    cout << "Press any key to return to main menu" << endl;
}

void Menu::handleTriangularApproximation(Graph *graph)
{
    // Implement the TSP solving using Triangular Approximation algorithm
    cout << "Solving TSP using Triangular Approximation algorithm..." << endl;
    // Start the clock
    auto start = chrono::high_resolution_clock::now();

    double shortest_path = triangularApproximation(graph);

    cout << "Shortest path found: " << shortest_path << endl;

    // Stop the clock
    auto end = chrono::high_resolution_clock::now();

    // Calculate the duration
    chrono::duration<double> duration = end - start;

    // Convert duration to seconds
    double durationInSeconds = duration.count();
    cout << "Time taken to run the algorithm: " << durationInSeconds << " seconds" << endl;
    cout << "Press any key to return to main menu" << endl;
}

void Menu::handleMSTApproximation(Graph *graph)
{
    // Implement the TSP solving using an MST-based algorithm
    cout << "Solving TSP using MST-based algorithm..." << endl;

    // Start the clock
    auto start = chrono::high_resolution_clock::now();

    double shortest_path = mstApproximation(graph);

    cout << "Shortest path found: " << shortest_path << endl;

    // Stop the clock
    auto end = chrono::high_resolution_clock::now();

    // Calculate the duration
    chrono::duration<double> duration = end - start;

    // Convert duration to seconds
    double durationInSeconds = duration.count();
    cout << "Time taken to run the algorithm: " << durationInSeconds << " seconds" << endl;
    cout << "Press any key to return to main menu" << endl;
}

void Menu::handleDivideAndConquer(Graph *graph)
{
    // Implement the TSP solving using Divide and Conquer algorithm
    cout << "Solving TSP using Divide and Conquer algorithm..." << endl;

    // Start the clock
    auto start = chrono::high_resolution_clock::now();

    double shortest_path = divideAndConquer(graph);

    cout << "Shortest path found: " << shortest_path << endl;

    // Stop the clock
    auto end = chrono::high_resolution_clock::now();

    // Calculate the duration
    chrono::duration<double> duration = end - start;

    // Convert duration to seconds
    double durationInSeconds = duration.count();
    cout << "Time taken to run the algorithm: " << durationInSeconds << " seconds" << endl;
    cout << "Press any key to return to main menu" << endl;
}

int Menu::getUserChoice()
{
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl
         << endl;
    return choice;
}

int Menu::getFileNumber(int numFiles)
{
    int fileNumber;
    cout << "Please enter the file number (1-" << numFiles << "): ";
    cin >> fileNumber;
    return fileNumber;
}
