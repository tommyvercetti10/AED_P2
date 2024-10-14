
#ifndef PROJETO2AED_FLIGHT_H
#define PROJETO2AED_FLIGHT_H
#include <string>
using namespace std;

class Flight {
private:
    string source;
    string target;
    string airline;
public:
    ///The flight builder contains the place of departure and arrival and the airline that will make the flight
    Flight(string source, string target, string airline);
    string getsource();
    string gettarget();
    string getairline();

    bool operator<(const Flight flight) const{
        if(source==flight.source && target==flight.target) return airline<flight.airline;
        else if(source == flight.source) return target < flight.target;
        return source < flight.source;
    }

    bool operator==(const Flight flight) const{
        return source == flight.source;
    }
};


#endif //PROJETO2AED_FLIGHT_H
