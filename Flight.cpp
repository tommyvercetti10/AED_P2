

#include "Flight.h"

Flight::Flight(std::string source, std::string target, std::string airline) {
    this->source = source;
    this->target = target;
    this->airline = airline;
}

string Flight::getsource() {return source;}
string Flight::gettarget() {return target;}
string Flight::getairline() {return airline;}