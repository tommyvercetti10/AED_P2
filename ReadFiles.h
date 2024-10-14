//
// Created by miguel-duarte on 27-12-2023.
//

#ifndef PROJETO2AED_READFILES_H
#define PROJETO2AED_READFILES_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <unordered_map>

#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include "Graph.h"

using namespace std;

class ReadFiles {
private:
    unordered_map<string,Airport> airports;
    unordered_map<string, Airline> airlines;
    set<Flight> flights;
    Graph graph;

public:
    ///Go to the file airports.csv and read its contents line by line, knowing that each line shows the information of one airport.
    ///Creates an Airport object for each airport containing the information and adds it to an unordered_map to make it easier to query the data
    void readerAirports();
    ///Go to the file airlines.csv and read its contents line by line, knowing that each line shows the information of one airline.
    ///Creates an Airline object for each airline containing the information and adds it to an unordered_map to make it easier to query the data
    void readerAirlines();
    ///Go to the file flights.csv and read its contents line by line, knowing that each line shows the information of one flights.
    ///Creates an Flight object for each flight containing the information and adds it to a set to make it easier to query the data
    ///The flight information will be placed in a graph and linked to airports and airlines to improve the organisation and search of the desired datae
    void readerFlights();
    unordered_map<string,Airport>& getairports();
    unordered_map<string,Airline>& getairlines();
    set<Flight>& getflights();
    Graph& getgraph();
    vector<Airport> getAirports(string code);
};


#endif //PROJETO2AED_READFILES_H
