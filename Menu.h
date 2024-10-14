//
// Created by miguel-duarte on 20-12-2023.
//

#ifndef PROJETO2AED_MENU_H
#define PROJETO2AED_MENU_H


#include "ReadFiles.h"
#include "Management.h"
#include <list>

class Menu {
private:
    Management& m;
public:
    Menu(Management& m_);
    void run();
    void flightOptions();
    vector<double> convertCoordinates(string coordinates);
    vector<string> convertAirlines(string airlines);
};


#endif //PROJETO2AED_MENU_H
