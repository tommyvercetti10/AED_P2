

#include <iostream>
#include "ReadFiles.h"
#include "Menu.h"

using namespace std;


int main() {
    ReadFiles rf;
    rf.readerAirports();
    rf.readerAirlines();
    rf.readerFlights();
    Management management(rf);
    Menu menu(management);
    menu.run();
    return 0;
}