//
// Created by tomast12 on 27/12/23.
//

#include "Airline.h"
using namespace std;


Airline::Airline(string code, string name, string callsign , string country) {
    this->code = code;
    this->name = name;
    this->country = country;
    this->callsign = callsign;
}

string Airline::getcode() {return this->code;}

string Airline::getname() {return this->name;}

string Airline::getcountry() {return this->country;}

string Airline::getcallsign() {return this->callsign;}


