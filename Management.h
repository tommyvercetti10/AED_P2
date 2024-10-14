

//
// Created by tomast12 on 30/12/23.
//

#ifndef PROJETO2AED_MANAGEMENT_H
#define PROJETO2AED_MANAGEMENT_H


#include "ReadFiles.h"
#include <queue>
#include <list>
#include <unordered_set>
#include <stack>

class Management {
private:
    ReadFiles& rf;
    int maxDistance = 0;
public:
    Management(ReadFiles& rf_);
    ///Function that stores the countries to which the airports contained in the vector have flights
    ///\param airports
    ///\return set with the desired countries
    set<string> countriesForAirCity(vector<Airport> airports);
    ///Function that gathers the routes with the most possible stops
    ///It also calculates the number of stops on these routes and stores it in the maxDistance variable.
    ///\return pairs with the departure and final airports for these trips
    set<pair<Airport,Airport>> maxStops();
    ///Function that calculates the flight with the fewest possible stopovers between the given location
    ///\param depAir departure location
    ///\param arrAir arrival location
    ///\return vector that stores vectors containing the airports of the best flights
    vector<vector<Airport>> bestFlights(string depAir, string arrAir, Graph graph);
    ReadFiles& getRf();
    int flightsForCityAirline(string x);
    int flightsForAirport(string x);
    vector<int> destinationsForAirport(string x);
    vector<int> destinationsForAirportLayOvers(string x, int i);
    int getMaxDistance();
    ///Function that calculates the nearest airport to the point received, which is defined by latitude and longitude.
    ///\param latitude
    ///\param longitude
    ///\return Vertex of the airport closest to the given point
    Vertex* nearestAirport(double latitude, double longitude);
    ///The Haversine funtion calculates the distance between two points defined by latitude and longitude
    double haversine(double lat1, double lon1, double lat2, double lon2);
    ///Function that finds the airlines that make trips between the given airports
    ///Time complexity: O(n), where n is the number of edges in the graph
    ///\param arr arrival airport
    ///\param dep departure airport
    ///\return set with the desired airlines
    set<Airline> tripAirlines(Airport dep, Airport arr, Graph graph);
    ///Function to obtain the possible airlines on the incoming trip.
    ///Used to obtain the airlines that the user can use for the desired journey.
    ///The user can choose whether to travel with as many airlines as possible or as few as possible.
    ///Time complexity: O(n), where n is the number of airports
    ///\param airports airports of the trip
    ///\param min bool variable that informs the function if the user wants to change the airline on their trip as few times as possible
    ///\return list of possible airlines
    Graph airline_preferences(vector<string> airlines);
    list<Airline> fullTripAirlines(vector<Airport> airports, bool min);
    ///Function to find the airline with the most or least trips between the given locations
    /// \param arr arrival airport
    /// \param dep departure airport
    /// \param airlines list of airlines sorted in ascending or descending order according to the number of trips between the given locations, depending on what the user has chosen
    /// \return airline with the most or least trips between the given locations
    Airline minMaxAirline(Airport arr, Airport dep, list<Airline>& airlines);
    static bool comparePair(pair<Vertex*, int>& a, pair<Vertex*, int>& b);
    ///Function that transforms the direct graph into an undirect graph
    ///\param undirectedgraph
    void makeUndirected(Graph& undirectedgraph);
    ///The function searches using a DFS to find articulation points, i.e. airports which, if removed, make the network zones inaccessible.
    ///Time complexity: O(V + E), where V is the number of vertices in the graph and E is the number of edges. This is because the code uses a depth-first search (DFS) algorithm to traverse the graph, visiting each vertex and each edge once.
    void dfs9(Graph graph, Vertex* v, unordered_set<string>& res, stack<Airport> s, int& i);
    void essentialAirports();
};


#endif //PROJETO2AED_MANAGEMENT_H
