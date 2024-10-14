//
// Created by miguel-duarte on 27-12-2023.
//

#ifndef PROJETO2AED_AIRPORT_H
#define PROJETO2AED_AIRPORT_H
#include <string>
using namespace std;

class Airport {
private:
    string code, name, city, country, latitude, longitude;
public:
    ///The constructor of an airport consists of a code, name and the city and country where it is located
    Airport(string code, string name, string city, string country, string latitude, string longitude);
    string getcode();
    string getname();
    string getcity();
    string getcountry();
    string getlatitude();
    string getlongitude();

    bool operator<(const Airport& airport) const;
    bool operator==(const Airport airport) const;
};


#endif //PROJETO2AED_AIRPORT_H
