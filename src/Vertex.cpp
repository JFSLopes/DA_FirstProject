#include "../header/Vertex.h"
#include "../header/City.h"
#include "../header/Reservoir.h"
#include <cfloat>

Vertex::Vertex(Node* node) : node(node), path(nullptr) {}

Node* Vertex::getNode() const {
    return node;
}

std::vector<Edge *> Vertex::getAdj() const {
    return adj;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return incoming;
}

void Vertex::addEdge(Vertex* d, double w) {
    Edge* edge = new Edge(this, d, w);
    adj.push_back(edge);
    d->incoming.push_back(edge);
}

bool Vertex::isVisited() const{
    return this->visited;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

Edge* Vertex::getPath() const {
    return this->path;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

double Vertex::remainReservoirDelivery() const {
    if (node->getCode().front() != 'R') return -1;
    double currDelivery = 0;
    for (Edge* e : adj) currDelivery += e->getFlow();
    Reservoir* reservoir = dynamic_cast<Reservoir*>(node);
    return reservoir->getMaxDelivery() - currDelivery;
}

void Vertex::removeEdges(){
    for (auto itr = adj.begin(); itr != adj.end();){
        Vertex* target = (*itr)->getOrig();
        (*itr)->getDest()->removeEdge(target);
        delete *itr;
        itr = adj.erase(itr);
    }
    for (auto itr = incoming.begin(); itr != incoming.end();){
        Vertex* target = (*itr)->getDest();
        (*itr)->getOrig()->removeEdge(target);
        delete *itr;
        itr = incoming.erase(itr);
    }
}

void Vertex::removeEdge(Vertex *target) {
    auto itr = adj.begin();
    while (itr != adj.end()){
        if ((*itr)->getDest() == target){
            itr = adj.erase(itr);
        }
        else itr++;
    }

    itr = incoming.begin();
    while (itr != incoming.end()){
        if ((*itr)->getOrig() == target){
            itr = incoming.erase(itr);
        }
        else itr++;
    }
}

double Vertex::cityAmountOfWater() const {
    if (node->getCode().front() == 'C'){
        double water = 0;
        for (Edge* e : incoming) water += e->getFlow();

        return water;
    }
    return -1;
}

bool Vertex::operator<(const Vertex other) const {
    City* city1 = dynamic_cast<City*>(this->getNode());
    City* city2 = dynamic_cast<City*>(other.getNode());

    double diff1 = this->cityAmountOfWater() - city1->getDemand();
    double diff2 = other.cityAmountOfWater() - city2->getDemand();
    return diff1 > diff2;
}

Edge *Vertex::edgeMoreFull() const {
    double min = DBL_MAX;
    Edge* answer;
    for (Edge* e : incoming){
        double diff = e->getWeight() - e->getFlow();
        if (diff < min){
            min = diff;
            answer = e;
        }
    }
    return answer;
}

bool Vertex::incomingFull() const {
    for (Edge* e : incoming){
        if (e->getFlow() != e->getWeight()){
            return false;
        }
    }
    return true;
}