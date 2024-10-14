//
// Created by tomast12 on 27/12/23.
//

#ifndef PROJETO2AED_AIRLINE_H
#define PROJETO2AED_AIRLINE_H
#include <string>
using namespace std;

class Airline {
    private:
        string code, name,country, callsign;

    public:
        ///The constructor for an airline consists of a code, name, country of origin and a callsign
        Airline(string code, string name, string callsign, string country );
        string getcode();
        string getname();
        string getcountry();
        string getcallsign();

        bool operator<(const Airline airline) const{
            return code<airline.code;
        }

        bool operator==(const Airline airline) const{
            return code == airline.code;
        }
};



#endif //PROJETO2AED_AIRLINE_H
