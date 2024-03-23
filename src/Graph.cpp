#include <iostream>
#include <queue>
#include <cfloat>
#include <cmath>
#include <algorithm>
#include "../header/Graph.h"


const std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

bool Graph::addVertex(Vertex* v) {
    vertexSet.push_back(v);
}

Vertex *Graph::findVertex(std::string &code) const {
    for (Vertex* v : vertexSet){
        if (v->getNode()->getCode() == code) return v;
    }
    return nullptr;
}

City *Graph::getCity(cityEnum type, std::string& str, uint32_t id) const {
    switch (type){
        case C_ID:{
            for (Vertex* v : vertexSet){
                if (v->getNode()->getID() == id and v->getNode()->getCode().front() == 'C') return dynamic_cast<City*>(v->getNode());
            }
        }
        break;

        case C_CODE:{
            for (Vertex* v : vertexSet){
                if (v->getNode()->getCode() == str) return dynamic_cast<City*>(v->getNode());
            }
        }
        break;

        case C_NAME:{
            for (Vertex* v : vertexSet){
                if (v->getNode()->getCode().front() != 'C') continue;
                City* city = dynamic_cast<City*>(v->getNode());
                if (city->getName() == str) return city;
            }
        }
    }
    return nullptr;
}

Station *Graph::getStation(stationEnum type, std::string &str, uint32_t id) const {
    switch (type){
        case S_ID:{
            for (Vertex* v : vertexSet){
                if (v->getNode()->getID() == id and v->getNode()->getCode().front() == 'P') return dynamic_cast<Station*>(v->getNode());
            }
        }
        break;

        case S_CODE:{
            for (Vertex* v : vertexSet){
                if (v->getNode()->getCode() == str) return dynamic_cast<Station*>(v->getNode());
            }
        }
        break;
    }
    return nullptr;
}

Reservoir *Graph::getReservoir(reservoirEnum type, std::string &str, uint32_t id) const {
    switch (type){
        case R_ID:{
            for (Vertex* v : vertexSet){
                if (v->getNode()->getID() == id and v->getNode()->getCode().front() == 'R') return dynamic_cast<Reservoir*>(v->getNode());
            }
        }
        break;

        case R_CODE:{
            for (Vertex* v : vertexSet){
                if (v->getNode()->getCode() == str) return dynamic_cast<Reservoir*>(v->getNode());
            }
        }
        break;

        case R_NAME:{
            for (Vertex* v : vertexSet){
                if (v->getNode()->getCode().front() != 'R') continue;
                Reservoir* reservoir = dynamic_cast<Reservoir*>(v->getNode());
                if (reservoir->getName() == str) return reservoir;
            }
        }
    }
    return nullptr;
}

// 4.1 max flow of specific city

bool Graph::findAugPath(Vertex* source, Vertex* sink) { // bfs search

    for (Vertex* v: vertexSet) {
        v->setVisited(false);
    }

    std::queue<Vertex*> q;
    q.push(source);
    source->setVisited(true);

    while(!q.empty() && !sink->isVisited()) {
        Vertex* v = q.front();
        q.pop();
        for (Edge* e : v->getAdj()) {
            Vertex* dest = e->getDest();
            if (!dest->isVisited() && (e->getWeight() - e->getFlow() > 0)) {
                dest->setVisited(true);
                dest->setPath(e);
                q.push(dest);
            }
        }
        for (Edge* e: v->getIncoming()) {
            Vertex* origin = e->getOrig();
            if (!origin->isVisited() && (e->getFlow() > 0)) {
                origin->setVisited(true);
                origin->setPath(e);
                q.push(origin);
            }
        }
    }
    return sink->isVisited();
}

double Graph::minResAugPath(Vertex *source, Vertex *sink) { // flow máx em cada path
    double maxFlow = DBL_MAX;
    for (Vertex* v = sink; v != source;) {
        Edge* e = v->getPath();
        if (e->getDest() == v) {
            maxFlow = std::min(maxFlow, e->getWeight()-e->getFlow());
            v = e->getOrig();
        } else {
            maxFlow = std::min(maxFlow, e->getFlow());
            v = e->getDest();
        }
    }
    return maxFlow;
}

void Graph::augmentFlowPath(Vertex *source, Vertex *sink,double  f) {
    for(Vertex* v = sink ; v!=source;){
        Edge* e = v->getPath();
        double flow = e->getFlow();
        if(e->getDest() == v){
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else{
            e->setFlow(flow -f);
            v = e->getDest();
        }
    }
}

void Graph::createSuperSourceSink() {
    std::string id = "F";
    Node s = Node(0, id);
    std::string id1 = "X";
    Node t = Node(1, id1);
    Vertex source = Vertex(&s);
    Vertex target = Vertex(&t);
    addVertex(&source);
    addVertex(&target);
    for (auto v: getVertexSet()) {
        char code = v->getNode()->getCode()[0];
        if (code == 'R') {
            source.addEdge(v, DBL_MAX);
        } else if (code == 'C') {
            v->addEdge(&target, DBL_MAX);
        }
    }
}
void Graph::edmondsKarp(){
    std::string id = "F";
    std::string id1 = "X";
    auto s = findVertex(id);
    auto t = findVertex(id1);
    if(  s == nullptr || t == nullptr || s == t) return;
    for (auto v:getVertexSet()){
        for (auto e : v->getAdj()){
            e->setFlow(0);std::string id1 = "X";
        }
    }
    while (findAugPath(s,t)){
        double f = minResAugPath(s,t);
        augmentFlowPath(s,t,f);
    }
}





