//
// Created by miguel-duarte on 27-12-2023.
//

#include "Airport.h"
using namespace std;

Airport::Airport(string code, string name, string city, string country, string latitude, string longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

string Airport::getcode() {return code;}

string Airport::getname() {return name;}

string Airport::getcity() {return city;}

string Airport::getcountry() {return country;}

string Airport::getlatitude() {return latitude;}

string Airport::getlongitude() {return longitude;}

bool Airport::operator<(const Airport& airport) const {
    return this->code < airport.code;
}

bool Airport::operator==(const Airport airport) const{
    return code == airport.code;
}
