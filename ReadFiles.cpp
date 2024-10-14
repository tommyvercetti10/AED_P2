//
// Created by miguel-duarte on 27-12-2023.
//

#include "ReadFiles.h"


void ReadFiles::readerAirports(){
    ifstream in("../dataset/airports.csv");

    string code, name, city, country, latitude, longitude, line;

    getline(in, line);

    while(getline(in,code, ','), getline(in,name, ','), getline(in,city, ','), getline(in,country, ','), getline(in,latitude, ','), getline(in,longitude)){
        Airport airport(code, name, city, country, latitude, longitude);
        airports.emplace(code, airport);
        graph.addVertex(airport);
    }
}

void ReadFiles::readerAirlines() {
    ifstream in("../dataset/airlines.csv");

    string code, name, country, callsign, line;

    getline(in, line);

    while(getline(in, code, ','), getline(in, name, ','), getline(in, callsign, ','), getline(in, country)) {
        Airline airline(code, name, callsign, country);
        airlines.emplace(code, airline);
    }
}

void ReadFiles::readerFlights() {
    ifstream in("../dataset/flights.csv");

    string source, target, airline, line;

    getline(in, line);

    //int i=1;

    while(getline(in, source, ','), getline(in, target, ','), getline(in, airline)) {
        Flight flight(source, target, airline);
        flights.insert(flight);
        graph.addEdge(airports.at(source), airports.at(target), airlines.at(airline));
        //cout << i << " "<< graph.findVertex(airports.at(source))->getAdj().size() << '\n';
        //i++;
    }
}

vector<Airport> ReadFiles::getAirports(string code) {
    vector<Airport> foundAirports;
    auto it = airports.find(code);
    if (it == airports.end()) { // code is invalid, search for city or name
        auto it2 = airports.begin();
        while (it2 != airports.end()) {
            if (it2->second.getcity() == code || it2->second.getname() == code) {
                foundAirports.push_back(it2->second);
            }
            it2++;
        }
    }
    else {
        foundAirports.push_back(it->second);
    }
    return foundAirports;
}

unordered_map<string,Airport>& ReadFiles::getairports() {
    return airports;
}

unordered_map<string, Airline>& ReadFiles::getairlines() {
    return airlines;
}

set<Flight>& ReadFiles::getflights() {
    return flights;
}

Graph& ReadFiles::getgraph() {
    return graph;
}