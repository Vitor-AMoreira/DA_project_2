

#ifndef DA_PROJECT_2_MENU_H
#define DA_PROJECT_2_MENU_H

#include <chrono>
#include "Graph.h"
#include "Algorithms.cpp"

using namespace std;

class Menu {
public:
    int menuOption;

    Menu();

    void showMenu();

    void showMenuOpt1();
    void showMenuOpt1_1();
    void showMenuOpt1_2();
    void showMenuOpt1_3();

    void showMenuOpt2();
    static void showMenuOpt2_1(Graph);
    static void showMenuOpt2_2(Graph);

    void clearBuffer();
};


#endif //DA_PROJECT_2_MENU_H
