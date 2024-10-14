

#ifndef PROJETO2AED_GRAPH_H
#define PROJETO2AED_GRAPH_H


#include <cstddef>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>

#include "Airport.h"
#include "Airline.h"
#include "Flight.h"


using namespace std;

class Edge;
class Graph;
class Vertex;


/****************** Provided structures  ********************/

///Vertices representing airports.
class Vertex {
    Airport info;                // contents
    vector<Edge> adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int distance = 0;
    Vertex* parent;
    int arrival = 0;
    int num;
    int low;
public:
    ///Vertex constructor
    ///\param in corresponding airport
    Vertex(Airport in);
    ///\return corresponding airport
    Airport getInfo() const;
    void setInfo(Airport in);
    ///\return visited value
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    ///\return distance variable value
    int getDistance();
    ///\return list of outgoing edges
    const vector<Edge> &getAdj() const;
    ///\return arrival variable value
    int getArrival();
    void setAdj(const vector<Edge> &adj);
    ///add an outgoing edge associated with this vertex
    ///\param dest destination of the edge
    ///\param h	airline
    void addEdge(Vertex *dest, Airline h);
    ///increases the count of incoming edges
    void addArrival();
    bool removeEdgeTo(Vertex *d);
    void setnum(int x);
    void setlow(int x);
    int getnum();
    int getlow();

    friend class Graph;
};

class Edge {
    ///destination of the edge
    Vertex * dest;
    ///Airline associated with that Edge and connects the two airports involved
    Airline weight;
public:
    ///Edge constructor
    ///\return d destination of the edge
    ///\return h Airline associated with that Edge and connects the two airports involved
    Edge(Vertex *d, Airline h);
    ///\return destination of the edge
    Vertex *getDest() const;
    void setDest(Vertex *dest);
    ///\return Airline associated with that Edge
    Airline getWeight() const;
    void setWeight(Airline weight);
    ///	Declaration of the Graph class to access the private members of this class.
    friend class Graph;
    ///Declaration of the Vertex class to access the private members of this class.
    friend class Vertex;
};

///Graph to represent all the flights.
class Graph {
    map<string, Vertex*> vertexSet;    // vertex set
public:
    Vertex *findVertex(Airport &in) const;
    int getNumVertex() const;
    void addVertex(Airport &in);
    bool removeVertex(Airport &in);
    ///Adds an edge to current graph with the given source and destination and with an airline
    ///\param src Edge source
    ///\param dest Edge destination
    bool addEdge(Airport &source, Airport &dest, Airline h);
    bool removeEdge(Airport &source, Airport &dest);
    ///\return map with all Verteces
    map<string, Vertex*> getVertexSet() const;
    void dfs(Airport air);
    ///Function used to find the journey with the most stopovers possible from the airport received. To do this, a Breadth-first search is used
    ///The longest distance is stored in the vertex distance variable
    ///Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph
    ///\param air Departure airport
    ///\return Vertex containing the destination airport of the journey with the most stopovers from the received airport.
    Vertex* maxDistance(Airport air);
    ///Function used to find the journey with the fewest stops between the airports received.
    ///The shorter distance is stored in the vertex distance variable
    ///Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph.
    /// \param dep Departure airport
    /// \param arr Arrival airport
    /// \return Sets that store the vectors containing the airports of the routes obtained
    set<vector<Vertex*>> minDistance(Airport dep, Airport arr); // bfs
    //int inDegree(const T &v) const;
};


#endif //PROJETO2AED_GRAPH_H
