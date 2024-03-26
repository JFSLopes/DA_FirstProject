#include <iostream>
#include <queue>
#include <cfloat>
#include <cmath>
#include <algorithm>
#include "../header/Graph.h"


const std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

void Graph::addVertex(Vertex* v) {
    vertexSet.push_back(v);
}

void Graph::DFSVisit(Vertex *v, std::vector<Vertex*>& subGraph) {
    v->setVisited(true);
    subGraph.push_back(v);
    for (Edge* e : v->getAdj()){
        if (!e->getDest()->isVisited()){
            DFSVisit(e->getDest(), subGraph);
        }
    }
}

void Graph::DFSVisitReverse(Vertex *v, std::vector<Vertex *> &subGraph) {
    for (Edge* e : v->getIncoming()){
        if (!e->getOrig()->isVisited()){
            e->getOrig()->setVisited(true);
            subGraph.push_back(e->getOrig());
            DFSVisitReverse(e->getOrig(), subGraph);
        }
    }
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

bool Graph::findAugPath(Vertex* source, Vertex* sink, Vertex* removed) { // bfs search
    for (Vertex* v : vertexSet) {
        v->setVisited(false);
    }
    if (removed != nullptr) removed->setVisited(true);

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

bool Graph::findAugPathSubGraph(Vertex *source, Vertex *sink, std::vector<Vertex *> &subGraph) {

    for (Vertex* v : vertexSet) v->setVisited(true);
    for (Vertex* v : subGraph) v->setVisited(false);

    std::queue<Vertex*> q;
    q.push(source);
    source->setVisited(true);

    while(!q.empty() && !sink->isVisited()) {
        Vertex* v = q.front();
        q.pop();
        for (Edge* e : v->getAdj()){
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

void Graph::createSuperSourceSink(Vertex* removedReservoir){
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
        if (code == 'R'){
            Reservoir* reservoir = dynamic_cast<Reservoir*>(v->getNode());
            source->addEdge(v, reservoir->getMaxDelivery());
        } else if (code == 'C') {
            City* city = dynamic_cast<City*>(v->getNode());
            v->addEdge(target, city->getDemand());
        }
    }
    if (removedReservoir == nullptr) return;
    /// Making sure the reservoir will not be used
    for (Edge* e : source->getAdj()){
        if (e->getDest() == removedReservoir) e->setFlow(e->getWeight());
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
            e->setRemoved(false);
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
void Graph::edmondsKarpRemovePipeline(Edge *edge) {
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
}

void Graph::edmondsKarpRemoveReservoir(Vertex *reservoir) {
    std::set<std::pair<std::string,double>> before = checkWaterNeeds();
    createSuperSourceSink(reservoir);
    std::string sourceCode = "F";
    std::string sinkCode = "X";
    Vertex* s = findVertex(sourceCode);
    Vertex* t = findVertex(sinkCode);

    std::vector<Vertex*> subGraph;

    for (auto v : getVertexSet()){
        v->setVisited(false);
        for (auto e : v->getAdj()){
            e->setFlow(0);
            e->setRemoved(false);
        }
    }
    DFSVisit(reservoir, subGraph);
    std::vector<Vertex*> aux(subGraph.begin(), subGraph.end());
    /// Complete the subGraph
    for (Vertex* v : aux){
        DFSVisitReverse(v, subGraph);
    }

    while (findAugPath(s, t, reservoir)){
        double f = minResAugPath(s,t);
        augmentFlowPath(s,t,f);
    }
    removeSuperSourceSink();

    std::set<std::pair<std::string,double>> after = checkWaterNeeds();
    std::cout << "Removing reservoir " << reservoir->getNode()->getCode() << " affects the following cities:\n";
    for (auto pair : after){
        auto it = before.end();
        for (auto itr = before.begin(); itr != before.end(); itr++){
            if (itr->first == pair.first){
                it = itr;
                break;
            }
        }
        if((it != before.end()) and (pair.second <= it->second)) continue;

        std::cout << pair.first << " --> DEFICIT: " << pair.second << "\n";
    }
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
        double amountWater = (maxDiff - (e->getWeight() - e->getFlow())) / 2;
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

void Graph::findAllPaths(Vertex *s, std::vector<Edge *>& path, std::vector<std::vector<Edge *>>& paths) const {
    s->setVisited(true);

    if (s->getNode()->getCode().front() == 'C'){
        paths.push_back(path);
    }
    else{
        for (Edge* e : s->getAdj()){
            if (!e->getDest()->isVisited()){
                path.push_back(e);
                findAllPaths(e->getDest(), path, paths);
            }
        }
    }
    if (!path.empty()) path.pop_back();
    s->setVisited(false);
}

bool Graph::incomeEdgesFull(std::vector<std::vector<Edge *>>& allPaths) const {
    for (std::vector<Edge*>& vec : allPaths){
        for (Edge* e : vec){
            double incomeFlow = 0;
            double maxIncomeFlow = 0;
            for (Edge* e1 : e->getDest()->getIncoming()){
                incomeFlow += e1->getFlow();
                maxIncomeFlow += e1->getWeight();
            }

            if ((incomeFlow/maxIncomeFlow) < 0.95){
                return false;
            }
        }
    }
    return true;
}

void Graph::simplerAlgorithm(std::vector<std::vector<Edge *>> &allPaths){
    for (Vertex* v : vertexSet) v->setVisited(false);

    std::unordered_map<std::string, double> lostFlow;

    for (std::vector<Edge*> vec : allPaths){
        /// The last elements is always the edge with the city
        Vertex* dest = vec.back()->getDest();
        if (!dest->isVisited()){
            dest->setVisited(true);
            auto itr = lostFlow.find(dest->getNode()->getCode());
            if (itr == lostFlow.end()){
                lostFlow.insert(std::make_pair(dest->getNode()->getCode(), vec.back()->getFlow()));
            }
            else{
                itr->second += vec.back()->getFlow();
            }
        }
    }
    for (const std::pair<std::string, double>& p : lostFlow){
        std::string code = p.first;
        Vertex* v = findVertex(code);
        City* city = dynamic_cast<City*>(v->getNode());

        std::cout << "City: " << p.first << " -> After removal: " << p.second << ", Demand: " << city->getDemand() << "\n";
    }
    std::cout << "\n";
}

void Graph::removeReservoir(Vertex *reservoir) {
    for (Vertex* v : vertexSet) v->setVisited(false);
    std::vector<Edge*> path;
    std::vector<std::vector<Edge*>> allPaths;
    findAllPaths(reservoir, path, allPaths);
    if (incomeEdgesFull(allPaths)){
        std::cout << "Running the simpler algorithm, no need for rerun Edmonds Karp.\n";
        simplerAlgorithm(allPaths);
    }
    else{
        std::cout << "Impossible to apply the simpler algorithm. Running Edmonds Karp from scratch.\n";
        edmondsKarpRemoveReservoir(reservoir);
    }
}


void Graph::edmondsKarpRemovePumpingStation(Vertex *pumpingStation) {
    createSuperSourceSink();
    std::string sourceCode = "F";
    std::string sinkCode = "X";
    Vertex* s = findVertex(sourceCode);
    Vertex* t = findVertex(sinkCode);

    for (auto v : getVertexSet()){
        v->setVisited(false);
        for (auto e : v->getAdj()){
            e->setFlow(0);
            e->setRemoved(false);
        }
    }

    double maxFlow = 0;
    while (findAugPath(s,t, pumpingStation)){
        double f = minResAugPath(s,t);
        augmentFlowPath(s,t,f);
    }
    removeSuperSourceSink();

}