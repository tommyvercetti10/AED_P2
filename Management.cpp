//
// Created by tomast12 on 30/12/23.
//

#include "Management.h"
#include <iostream>
#include <cmath>

using namespace std;


Management::Management(ReadFiles &rf_) : rf(rf_) {}


bool Management::comparePair(pair<Vertex*, int>& a, pair<Vertex*, int>& b){
    return a.second>b.second;
}

ReadFiles& Management::getRf() {
    return rf;
}


int Management::flightsForCityAirline(string x) {
    int res = 0;
    for(auto it = rf.getflights().begin(); it != rf.getflights().end(); it++){
        auto flight = *it;
        if(rf.getairports().at(flight.getsource()).getcity() == x || rf.getairports().at(flight.gettarget()).getcity() == x || flight.getairline() == x){
            res++;
        }
    }
    return res;
}

int Management::flightsForAirport(std::string x) {
    int res = 0;
    for(auto it = rf.getflights().begin(); it != rf.getflights().end(); it++){
        auto flight = *it;
        if ((flight.getsource() == x || flight.gettarget() == x)) res++;
    }
    return res;
}

vector<int> Management::destinationsForAirport(string x) {
    set<string> airports, countries;
    set<pair<string,string>> cities;
    vector<int> destinationsNum;
    int num_cities=0, num_airports=0, num_countries=0;
    Airport airport(rf.getairports().at(x));
    Vertex* source = rf.getgraph().findVertex(airport);
    if(source == nullptr) return destinationsNum;
    for (auto vertex : rf.getgraph().getVertexSet()) {
        vertex.second->setVisited(false);
    }
    queue<pair<Vertex*, int>> bfsqueue;
    bfsqueue.push(make_pair(source,0));
    source->setVisited(true);
    while(!bfsqueue.empty()) {
        Vertex *current = bfsqueue.front().first;
        int d = bfsqueue.front().second;
        bfsqueue.pop();
        for(auto edge : current->getAdj()){
            if(!edge.getDest()->isVisited()){
                Vertex* v = edge.getDest();
                bfsqueue.push(make_pair(v, d));
                edge.getDest()->setVisited(true);
                if(cities.find(make_pair(edge.getDest()->getInfo().getcity(), edge.getDest()->getInfo().getcountry())) == cities.end()){
                    num_cities++;
                    cities.insert(make_pair(edge.getDest()->getInfo().getcity(), edge.getDest()->getInfo().getcountry()));
                }
                if(countries.find(edge.getDest()->getInfo().getcountry())==countries.end()){
                    num_countries++;
                    countries.insert(edge.getDest()->getInfo().getcountry());
                }
                airports.insert(edge.getDest()->getInfo().getcode());
                num_airports++;
            }
        }
    }
    destinationsNum.push_back(num_airports);
    destinationsNum.push_back(num_cities);
    destinationsNum.push_back(num_countries);
    return destinationsNum;
}

vector<int> Management::destinationsForAirportLayOvers(string x, int i){
    set<string> airports, countries;
    set<pair<string,string>> cities;
    vector<int> destinationsNum;
    int num_cities=0, num_airports=0, num_countries=0;
    Airport airport(rf.getairports().at(x));
    Vertex* source = rf.getgraph().findVertex(airport);
    if(source == nullptr) return destinationsNum;
    for (auto vertex : rf.getgraph().getVertexSet()) {
        vertex.second->setVisited(false);
    }
    queue<pair<Vertex*, int>> bfsqueue;
    bfsqueue.push(make_pair(source,0));
    source->setVisited(true);
    while(!bfsqueue.empty()){
        Vertex* current = bfsqueue.front().first;
        int d = bfsqueue.front().second;
        bfsqueue.pop();
        if(d == i && bfsqueue.size()!=0){
            bfsqueue.pop();
        }
        if(d < i){
            d++;
            for(auto edge : current->getAdj()){
                if(!edge.getDest()->isVisited()){
                    Vertex* v = edge.getDest();
                    bfsqueue.push(make_pair(v, d));
                    edge.getDest()->setVisited(true);
                    if(cities.find(make_pair(edge.getDest()->getInfo().getcity(), edge.getDest()->getInfo().getcountry())) == cities.end()){
                        num_cities++;
                        cities.insert(make_pair(edge.getDest()->getInfo().getcity(), edge.getDest()->getInfo().getcountry()));
                    }
                    if(countries.find(edge.getDest()->getInfo().getcountry())==countries.end()){
                        num_countries++;
                        countries.insert(edge.getDest()->getInfo().getcountry());
                    }
                    airports.insert(edge.getDest()->getInfo().getcode());
                    num_airports++;
                }
            }
        }
    }
    destinationsNum.push_back(num_airports);
    destinationsNum.push_back(num_cities);
    destinationsNum.push_back(num_countries);
    return destinationsNum;
}

void Management::dfs9(Graph graph, Vertex* v, unordered_set<string>& res, stack<Airport> s, int& i){
    v->setnum(i);
    v->setlow(i);
    i++;
    int children = 0;
    s.push(v->getInfo());
    for(Edge edge: v->getAdj()){
        if (edge.getDest()->getnum() == 0) {
            children++;
            dfs9(graph, edge.getDest(), res, s, i);
            v->setlow(min(v->getlow(), edge.getDest()->getlow()));
            if (v->getInfo().getcode() != graph.getVertexSet().begin()->second->getInfo().getcode() && edge.getDest()->getlow() >= v->getnum()) {
                res.insert(v->getInfo().getcode());
            }
        }
        else {
            v->setlow(min(v->getlow(), edge.getDest()->getnum()));
        }
    }
}

set<string> Management::countriesForAirCity(vector<Airport> airports) {
    set<string> countries;
    for (int i = 0; i < airports.size(); i++) {
        Vertex* airport = rf.getgraph().findVertex(airports[i]);
        for (int k = 0; k < airport->getAdj().size(); k++)
            countries.insert(airport->getAdj()[k].getDest()->getInfo().getcountry());
    }
    return countries;
}


set<pair<Airport, Airport>> Management::maxStops() {
    set<pair<Airport, Airport>> airs;
    int maxDistance = 0;
    for (auto v : rf.getgraph().getVertexSet()) {
        Vertex* possibleDest = rf.getgraph().maxDistance(v.second->getInfo());
        if (possibleDest->getDistance() >= maxDistance)
        {
            if (possibleDest->getDistance() > maxDistance) airs.clear();
            airs.insert(make_pair(v.second->getInfo(), possibleDest->getInfo()));
            /*cout << v.second->getInfo().getcity() + " to " + possibleDest->getInfo().getcity()
            + "Stops:" << possibleDest->getDistance() << '\n';*/
            maxDistance = possibleDest->getDistance();
        }
    }
    this->maxDistance = maxDistance;
    //cout << "Number of trips with maximum stops: " << airs.size() << '\n';
    return airs;
}


vector<vector<Airport>> Management::bestFlights(string depAir, string arrAir, Graph graph) {
    vector<vector<Airport>> flights;
    set<vector<Vertex*>> paths;
    vector<Airport> dep = rf.getAirports(depAir);
    vector<Airport> arr = rf.getAirports(arrAir);
    //cout << dep.size() << " " << arr.size() << '\n';
    int minStops = 1000;
    for (int i = 0; i < dep.size(); i++) {
        //cout << dep[i].getcode() << '\n';
        for (int b = 0; b < arr.size(); b++) {
            //cout << arr[b].getcode() << '\n';
            set<vector<Vertex*>> pts = graph.minDistance(dep[i], arr[b]);
            //cout << pts.size() << '\n';
            for (vector<Vertex*> c : pts) {
                paths.insert(c);
                if (minStops > c.size()) minStops = c.size();
            }
            //cout << paths.size();
        }
    }
    for (vector<Vertex*> i : paths) {
        if (i.size() == minStops) {
            vector<Airport> airs;
            for (Vertex* b : i) {
                airs.push_back(b->getInfo());
            }
            flights.push_back(airs);
        }
    }
    /*for (vector<Airport> v : flights) {
        for (Airport a : v) {
            cout << a.getcode() << " -> ";
        }
        cout << "Stops of the trip: " << v.size() - 2 << '\n';
    }*/
    return flights;
}


list<Airline> Management::fullTripAirlines(vector<Airport> airports, bool min) {
    map<Airline, int> airlineCount;
    for (int b = 0; b < airports.size(); b++) {    //count of the airlines with the most trips
        if (b != airports.size() - 1) {
            //cout << flights[i][b].getcode() << " -> \n";
            for (Airline airline : tripAirlines(airports[b], airports[b + 1], rf.getgraph()))
                airlineCount[airline] += 1;
        }
        //else cout << airports[b].getcode() << '\n';
    }
    int max = 0;
    list<Airline> airlines;
    for (pair<Airline, int> p : airlineCount) {
        if (p.second >= max) {
            for (int i = 0; i < p.second; i++)
                min ? airlines.push_front(p.first) : airlines.push_back(p.first); //if the user chooses the min, the airline with the most journeys will go to the front of the list to be chosen
                max = p.second;
        }
        else {
            for (int i = 0; i < p.second; i++)
                min ? airlines.push_back(p.first) : airlines.push_front(p.first);  //Otherwise, it will be the one with the fewest trips at the front
        }
    }
    return airlines;
}


Airline Management::minMaxAirline(Airport arr, Airport dep, list<Airline>& airlines) {
    auto it = airlines.begin();
    Airline airline = *it;
    while (true) {
        Vertex* arrVertex = getRf().getgraph().findVertex(arr);
        Vertex* depVertex = getRf().getgraph().findVertex(dep);
        for (Edge e : arrVertex->getAdj()) {
            if (e.getWeight() == airline && e.getDest() == depVertex) {
                airlines.erase(it);
                return airline;
            }
        }
        it++;
        airline = *it;
    }
}

int Management::getMaxDistance() {
    return maxDistance;
}


double toRadians(double degree) {
    return degree * M_PI / 180.0;
}


double Management::haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0;  // Raio médio da Terra em quilômetros

    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2.0) * sin(dlat / 2.0) + cos(lat1) * cos(lat2) * sin(dlon / 2.0) * sin(dlon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    double distance = R * c;

    return distance;
}


Vertex* Management::nearestAirport(double latitude, double longitude) {
    double minDistance = std::numeric_limits<double>::max();
    Vertex* nearestVertex;
    for (auto v : rf.getgraph().getVertexSet()) {
        double tmp =haversine(latitude, longitude, stod(v.second->getInfo().getlatitude()), stod(v.second->getInfo().getlongitude()));
        if (tmp < minDistance) {
            minDistance = tmp;
            nearestVertex = v.second;
        }
    }
    return nearestVertex;
}

Graph Management::airline_preferences(vector<string> airlines) {
    Graph g;
    //auto it = rf.getgraph().getVertexSet().begin();
    for(auto i : rf.getgraph().getVertexSet()){
        auto it = i.second;
        Vertex* v = it;
        Airport actual_airport = v->getInfo();
        g.addVertex(actual_airport);
        Vertex* actual_vertex = g.findVertex(actual_airport);
        string actual_airline = "TAP";
        bool flag = false;
        for(auto edge : v->getAdj()){
            for(auto& airline : airlines){
                if(edge.getWeight().getcode()==airline){
                    actual_airline = airline;
                    flag = true;
                    break;
                }
            }
            if(flag == true){
                Airport a = edge.getDest()->getInfo();
                g.addVertex(a);
                g.addEdge(actual_airport, a, rf.getairlines().at(actual_airline));
            }
            flag = false;
        }
    }
    int i=0;
    for(auto v : g.getVertexSet()){
        i+= v.second->getAdj().size();
    }
    return g;
}    
set<Airline> Management::tripAirlines(Airport dep, Airport arr, Graph graph) {
    set<Airline> airlines;
    Vertex* depVertex = graph.findVertex(dep);
    Vertex* arrVertex = graph.findVertex(arr);
    for (Edge i : depVertex->getAdj()) {
        if (i.getDest() == arrVertex) airlines.insert(i.getWeight());
    }
    return airlines;
}

void Management::makeUndirected(Graph& undirectedgraph) {
    for (const auto& v : rf.getgraph().getVertexSet()) {
        Airport airport = v.second->getInfo();
        undirectedgraph.addVertex(airport);
    }

    for (auto& v : rf.getgraph().getVertexSet()) {
        for (auto& edge : v.second->getAdj()) {
            Airport source = v.second->getInfo();
            Airport dest = edge.getDest()->getInfo();
            undirectedgraph.addEdge(source, dest, edge.getWeight());
            undirectedgraph.addEdge(dest, source, edge.getWeight());
        }
    }
}

void Management::essentialAirports() {
    unordered_set<string> res;
    stack<Airport> s;
    int i=0;
    Graph undirectedgraph;
    makeUndirected(undirectedgraph);
    for (auto vertex : undirectedgraph.getVertexSet()) {
        vertex.second->setnum(0);
        vertex.second->setVisited(false);
        vertex.second->setlow(0);
    }

    i++;
    for (auto vertex : undirectedgraph.getVertexSet()) {
        if (vertex.second->getnum() == 0) {
            dfs9(undirectedgraph, vertex.second, res, s, i);
        }
    }

    int count = 0;
    for (auto aux : res) {
        count++;
        auto v = undirectedgraph.getVertexSet().at(aux);
        std::cout << count << ". " << v->getInfo().getname() << std::endl;
    }

}

