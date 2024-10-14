
#include "Graph.h"

Vertex::Vertex(Airport in): info(in) {}

Edge::Edge(Vertex *d, Airline h): dest(d), weight(h) {}

int Graph::getNumVertex() const {
    return vertexSet.size();
}

map<string, Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}

Airport Vertex::getInfo() const {
    return info;
}

void Vertex::setInfo(Airport in) {
    Vertex::info = in;
}

bool Vertex::isProcessing() const {
    return processing;
}

void Vertex::setProcessing(bool p) {
    Vertex::processing = p;
}

int Vertex::getDistance() {
    return distance;
}

Vertex *Edge::getDest() const {
    return dest;
}

void Edge::setDest(Vertex *d) {
    Edge::dest = d;
}

Airline Edge::getWeight() const {
    return weight;
}


void Edge::setWeight(Airline weight) {
    weight = weight;
}



bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setVisited(bool v) {
    Vertex::visited = v;
}

const vector<Edge> &Vertex::getAdj() const {
    return adj;
}

void Vertex::setAdj(const vector<Edge> &adj) {
    this->adj = adj;
}

Vertex* Graph::findVertex(Airport &in) const {
    auto it = vertexSet.find(in.getcode());
    return (it != vertexSet.end()) ? it->second : nullptr;
}

void Graph::dfs(Airport air) {
    Vertex* vertex = findVertex(air);
    vertex->setVisited(true);
    for (auto e : vertex->getAdj()) {
        Vertex* w = findVertex(e.getDest()->info);
        if (!w->isVisited()) {
            dfs(w->getInfo());
        }
    }
}

void Graph::addVertex(Airport &in) {
    auto it = findVertex(in);
    if(it == nullptr){
        Vertex* i = new Vertex (in);
        vertexSet.emplace(in.getcode(), i);
    }
    /*if (findVertex(in) == NULL) {
        Vertex* i = new Vertex (in);
        vertexSet.emplace(in.getcode(), *i);
        return true;
    }*/
}


bool Graph::addEdge(Airport &source ,Airport &dest, Airline h) {
    if (findVertex(source) != nullptr && findVertex(dest) != nullptr) {
        findVertex(source)->addEdge(findVertex(dest),h);
        //findVertex(dest)->addArrival(findVertex(source), h);
        findVertex(dest)->addArrival();
        return true;
    }
    // HINT: use findVertex to obtain the actual vertices
    return false;
}

void Vertex::addEdge(Vertex *d, Airline w) {
    this->adj.push_back(Edge(d,w));
}



void Vertex::addArrival() {
    arrival++;
}

int Vertex::getArrival() {
    return this->arrival;
}

Vertex* Graph::maxDistance(Airport air) {
    Vertex* airport;
    queue<Airport> q;
    q.push(air);
    for (auto v : vertexSet) {
        v.second->setVisited(false);
        v.second->distance = 0;
    }
    Vertex* v = findVertex(air);
    v->distance = 0;
    v->setVisited(true);
    while (!q.empty()) {
        Airport air2 = q.front();
        q.pop();
        Vertex* u = findVertex(air2);
        for (auto e : u->getAdj()) {
            if (!e.getDest()->isVisited()) {
                q.push(e.getDest()->getInfo());
                e.getDest()->setVisited(true);
                e.getDest()->distance = u->distance + 1;
                airport = e.getDest();
            }
        }
    }
    return airport;
}

set<vector<Vertex*>> Graph::minDistance(Airport dep, Airport arr) {
    queue<Airport> q;
    set<vector<Vertex*>> paths;
    q.push(dep);
    for (auto v : vertexSet) {
        v.second->setVisited(false);
        v.second->distance = 0;
        v.second->parent = nullptr;
    }
    Vertex* v = findVertex(dep);
    v->distance = 0;
    v->setVisited(true);
    int minDistance = 0;
    bool breakLoop = false;
    while (!q.empty()) {
        Airport air2 = q.front();
        q.pop();
        Vertex* u = findVertex(air2);
        for (auto e : u->getAdj()) {
            if (!e.getDest()->isVisited()) {
                q.push(e.getDest()->getInfo());
                e.getDest()->setVisited(true);
                e.getDest()->distance = u->distance + 1;
                e.getDest()->parent = u;
                if (e.getDest()->getInfo() == arr){
                    vector<Vertex*> path;
                    if (e.getDest()->distance > minDistance && minDistance != 0) {
                        breakLoop = true;
                        break;
                    }
                    minDistance = e.getDest()->distance;
                    if (e.getDest()->distance != 1) e.getDest()->setVisited(false);
                    while (e.getDest() != nullptr) {
                        path.insert(path.begin(), e.getDest());
                        e.dest = e.getDest()->parent;
                    }
                    paths.insert(path);
                }
            }
        }
        if (breakLoop) break;
    }
    /*for (vector<Vertex*> i : paths) {
        for (Vertex* b : i) {
            cout << b->getInfo().getcode() << " -> ";
            //else cout << b->getInfo().getcode() << '\n';
        }
        cout << "Stops of the trip: " << i.size() - 2 << '\n';
    }*/
    return paths;
}

int Vertex::getnum(){
    return num;
}

void Vertex::setnum(int num) {
    Vertex::num = num;
}

int Vertex::getlow(){
    return low;
}

void Vertex::setlow(int low) {
    Vertex::low=low;
}

