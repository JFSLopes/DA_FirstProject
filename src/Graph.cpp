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
    return true;
}

void Graph::removeVertex(Vertex *v) {
    for (auto itr = vertexSet.begin(); itr != vertexSet.end(); itr++){
        if (*itr == v){
            vertexSet.erase(itr);
            break;
        }
    }
    v->removeEdges();
    delete v;
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
    for (Vertex* v : vertexSet) {
        v->setVisited(false);
    }

    std::queue<Vertex*> q;
    q.push(source);
    source->setVisited(true);

    while(!q.empty() && !sink->isVisited()) {
        Vertex* v = q.front();
        q.pop();
        for (Edge* e : v->getAdj()) {
            if (e->getRemoved()) continue;
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

double Graph::minResAugPath(Vertex *source, Vertex *sink) { // flow mÃ¡x em cada path
    double maxFlow = DBL_MAX;
    for (Vertex* v = sink; v != source;) {
        Edge* e = v->getPath();
        if (e->getDest() == v){
            maxFlow = std::min(maxFlow, e->getWeight() - e->getFlow());
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

void Graph::createSuperSourceSink(){
    std::string sourceCode = "F", sinkCode = "X";
    if ((findVertex(sourceCode) != nullptr) or (findVertex(sinkCode) != nullptr)) return;

    Node* s = new Node(0, sourceCode);
    Node* t = new Node(1, sinkCode);
    Vertex* source = new Vertex(s);
    Vertex* target = new Vertex(t);
    addVertex(source);
    addVertex(target);

    for (auto v: getVertexSet()) {
        char code = v->getNode()->getCode().front();
        if (code == 'R') {
            Reservoir* reservoir = dynamic_cast<Reservoir*>(v->getNode());
            source->addEdge(v, reservoir->getMaxDelivery());
        } else if (code == 'C') {
            City* city = dynamic_cast<City*>(v->getNode());
            v->addEdge(target, city->getDemand());
        }
    }
}

void Graph::removeSuperSourceSink() {
    std::string sourceCode = "F", sinkCode = "X";
    Vertex* source = findVertex(sourceCode);
    Vertex* sink = findVertex(sinkCode);
    removeVertex(source);
    removeVertex(sink);
}

double Graph::edmondsKarp(){
    createSuperSourceSink();
    std::string sourceCode = "F";
    std::string sinkCode = "X";
    Vertex* s = findVertex(sourceCode);
    Vertex* t = findVertex(sinkCode);

    for (auto v : getVertexSet()){
        for (auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
    double maxFlow = 0;
    while (findAugPath(s,t)){
        double f = minResAugPath(s,t);
        maxFlow += f;
        augmentFlowPath(s,t,f);
    }
    removeSuperSourceSink();
    return maxFlow;
}
double Graph::edmondsKarpRemovePipeline(Edge *edge) {
    createSuperSourceSink();
    std::string sourceCode = "F";
    std::string sinkCode = "X";
    Vertex* s = findVertex(sourceCode);
    Vertex* t = findVertex(sinkCode);

    for (auto v : getVertexSet()){
        for (auto e : v->getAdj()){
            e->setFlow(0);
            e->setRemoved(false);
        }
    }
    edge->setRemoved(true);
    double maxFlow = 0;
    while (findAugPath(s,t)){
        double f = minResAugPath(s,t);
        maxFlow += f;
        augmentFlowPath(s,t,f);
    }
    removeSuperSourceSink();
    return maxFlow;
}

metrics Graph::calculateMetrics() const {
    double sum = 0, maxDiff = DBL_MIN;
    uint32_t num = 0;
    for (Vertex* v : vertexSet){
        for (Edge* e : v->getAdj()){
            double diff = e->getWeight() - e->getFlow();
            maxDiff = std::max(maxDiff, diff);
            sum += diff;
            num++;
        }
    }
    double avg = sum/num;
    double variance = 0;
    for (Vertex* v : vertexSet){
        for (Edge* e : v->getAdj()){
            double diff = e->getWeight() - e->getFlow();
            double aux = diff - avg;
            variance += (aux * aux);
        }
    }
    variance /= (num - 1);
    variance = sqrt(variance);
    metrics m = {avg, variance, maxDiff};
    return m;
}

void Graph::orderCitiesByCumulative(std::priority_queue<Vertex>& q) const{
    for (Vertex* v : vertexSet){
        if (v->getNode()->getCode().front() == 'C'){
            q.push(*v);
        }
    }
}

void Graph::balanceLoad() {
    std::vector<Edge*> allEdges;
    for (Vertex* v : vertexSet){
        v->setVisited(false);
        for (Edge* e : v->getAdj()){
            allEdges.push_back(e);
        }
    }
    /// Start with edges that closer to be full
    std::sort(allEdges.begin(), allEdges.end(), [](Edge* a, Edge* b) {return a->getWeight() - a->getFlow() < b->getWeight() - b->getFlow();});

    for (Edge* e : allEdges){
        std::vector<Edge*> path;
        std::vector<std::vector<Edge*>> allPaths;
        findAllPaths(e->getOrig(), e->getDest(), path, allPaths);

        double maxDiff = DBL_MIN; /// Stores the minimal value that can be carried from the PS to the city for the path bestPath
        size_t bestPathIndex = 0;
        for (size_t index = 0; index < allPaths.size(); index++){
            double ans = minimalDiffCapacityFlow(allPaths[index]);
            if (ans > maxDiff) {
                maxDiff = ans;
                bestPathIndex = index;
            }
        }
        double amountWater = ((e->getWeight() - e->getFlow()) + maxDiff) / 2;
        e->setFlow(e->getFlow() - amountWater); /// Reduce the water on the chosen pipe
        incrementFlow(allPaths[bestPathIndex], amountWater); /// Increment the flow on the chosen alternative path
    }
}

void Graph::findAllPaths(Vertex *s, Vertex *d, std::vector<Edge *>& path, std::vector<std::vector<Edge *>>& paths) const {
    s->setVisited(true);

    if (s == d){
        paths.push_back(path);
    }
    else{
        for (Edge* e : s->getAdj()){
            if (!e->getDest()->isVisited()){
                path.push_back(e);
                findAllPaths(e->getDest(), d, path, paths);
            }
        }
    }
    if (!path.empty()) path.pop_back();
    s->setVisited(false);
}

double Graph::minimalDiffCapacityFlow(std::vector<Edge *>& path) const {
    double min = DBL_MAX;
    for (Edge* e : path){
        min = std::min(min, e->getWeight() - e->getFlow());
    }
    return min;
}

void Graph::incrementFlow(std::vector<Edge *>& path, double flow) {
    for (Edge* e : path){
        e->setFlow(e->getFlow() + flow);
    }
}

// 4.1.2 water deficit

std::set<std::pair<std::string, double>> Graph::checkWaterNeeds() {

    std::set<std::pair<std::string, double>> deficit;
    std::pair<std::string, double> waterNeeds;

    for (Vertex* v: vertexSet) {
        if (v->getNode()->getCode().front() == 'C') {
            std::string random = "name";
            City* city = getCity(C_ID, random, v->getNode()->getID());

            if (city == nullptr) {
                waterNeeds.first = "Error";
                waterNeeds.second = 0;
                std::cout << "Invalid input. Enter another one:\n";
            }

            double waterDemand = city->getDemand();
            double totalWater = v->cityAmountOfWater();

            double waterDeficit = waterDemand - totalWater;
            if (waterDeficit > 0) {
                waterNeeds.first = city->getCode();
                waterNeeds.second = waterDeficit;
                deficit.insert(waterNeeds);
            }
        }
    }
    return deficit;
}