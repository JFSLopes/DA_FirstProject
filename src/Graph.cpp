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

Vertex* Graph::findAugPathSubGraph(Vertex *source, Vertex* removed) {

    if (source->getNode()->getCode().front() == 'P' and source->needing == 0) return nullptr;

    for (Vertex* v : vertexSet) v->setVisited(false);
    removed->setVisited(true);

    std::queue<Vertex*> q;
    q.push(source);
    source->setVisited(true);

    while(!q.empty()) {
        Vertex* v = q.front();
        q.pop();
        if (v->getNode()->getCode().front() == 'R') return v; /// Found a reservoir

        for (Edge* e : v->getIncoming()){
            Vertex* orig = e->getOrig();
            if (!orig->isVisited() && (e->getWeight() - e->getFlow() > 0)) {
                orig->setVisited(true);
                orig->setPath(e);
                q.push(orig);
            }
        }
    }
    return nullptr;
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

double Graph::minResAugPath1(Vertex *source, Vertex *sink) {
    double maxFlow = DBL_MAX;
    for (Vertex* v = source; v != sink;) {
        Edge* e = v->getPath();

        maxFlow = std::min(maxFlow, e->getWeight() - e->getFlow());
        v = e->getDest();
    }
    return maxFlow;
}

void Graph::augmentFlowPath(Vertex *source, Vertex *sink,double  f) {
    for(Vertex* v = sink ; v != source;){
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

void Graph::augmentFlowPath1(Vertex *source, Vertex *sink, double  f) {
    for(Vertex* v = source; v != sink;){
        Edge* e = v->getPath();
        e->setFlow(e->getFlow() + f);
        v = e->getDest();
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
void Graph::edmondsKarpRemovePipeline(std::vector<Edge*> edges) {
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
    for (auto e : edges){
        e->setRemoved(true);
    }
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
            /// Makes sure the flow of he edge connecting the super source to the removed reservoir is full. It will not be consider in the augmenting paths
            if (e->getDest() != reservoir) e->setFlow(0);
            e->setRemoved(false);
        }
    }
    DFSVisit(reservoir, subGraph);
    std::vector<Vertex*> aux(subGraph.begin(), subGraph.end());
    /// Complete the subGraph
    for (Vertex* v : aux){
        DFSVisitReverse(v, subGraph);
    }
    /*
    while (findAugPathSubGraph(s, t, subGraph)){
        double f = minResAugPath(s,t);
        augmentFlowPath(s,t,f);
    }
     */
    removeSuperSourceSink();

    std::set<std::pair<std::string,double>> after = checkWaterNeeds();
    Reservoir* ptr = dynamic_cast<Reservoir*>(reservoir->getNode());
    std::cout << "Removing reservoir " << reservoir->getNode()->getCode() << "-" << ptr->getName() << " affects the following cities:\n";
    if (after.empty()){
        std::cout << "No cities were affected. It was possible to redirect water from others reservoirs.\n";
        return;
    }
    for (auto pair : after){
        auto it = before.end();
        for (auto itr = before.begin(); itr != before.end(); itr++){
            if (itr->first == pair.first){
                it = itr;
                break;
            }
        }
        if((it != before.end()) and (pair.second <= it->second)) continue;
        std::string code = pair.first;
        City* city = getCity(C_CODE, code, 0);
        std::cout << code << ": " << city->getName() << " --> Old flow: " << city->getDemand() - it->second << "    |    New flow: " << city->getDemand() - pair.second << "\n";
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

        double maxDiff = DBL_MIN; /// Stores the maximal value that can be carried from the PS to the city for the path bestPath
        size_t bestPathIndex = 0;
        for (size_t index = 0; index < allPaths.size(); index++){
            double ans = minimalDiffCapacityFlow(allPaths[index]);
            if (ans > maxDiff){ /// Does not check the direct connection
                maxDiff = ans;
                bestPathIndex = index;
            }
        }
        if (allPaths[bestPathIndex].size() == 1) continue; /// Didn't find a new path

        double amountWater = maxDiff;
        if (e->getFlow() < maxDiff) amountWater = e->getFlow() ; /// limited by the pipe flow
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
    if (allPaths.empty()) return;
    std::set<std::pair<std::string,double>> before = checkWaterNeeds();

    for (Vertex* v : vertexSet){
        v->needing = 0;
        v->has = 0;
        v->setVisited(false);
        for (Edge* e : v->getAdj()){
            e->setRemoved(false);
            e->needs = 0;
        }
    }

    /// Get the stations connected to the cities

    std::vector<Vertex*> ps;
    for (const std::vector<Edge*>& path : allPaths){
        if (path.size() < 2) continue; /// Theoretical impossible, would imply a reservoir directly connected to a city
        Edge* edge = path[path.size() - 1];
        if (!edge->getRemoved()){
            Vertex* psToAdd = edge->getOrig();
            psToAdd->needing += edge->getFlow(); /// Water that needs to be reposta
            if (!psToAdd->isVisited()) ps.push_back(psToAdd);
            edge->needs = edge->getFlow();
            edge->setRemoved(true);
            psToAdd->setVisited(true);
        }
    }


    /// Set the edges weights.
    for (const std::vector<Edge*>& path : allPaths){
        double minFlow = DBL_MAX;

        for (Edge* e : path) minFlow = std::min(minFlow, e->getFlow());

        for (Edge* e : path) e->setFlow(e->getFlow() - minFlow);
    }



    for (Vertex* v : vertexSet){
        for (Edge* e : v->getAdj()) e->setRemoved(false);
    }
    /// Check if does not need all the water
    for (const std::vector<Edge*>& path : allPaths){
        if (path.size() < 2) continue; /// Theoretical impossible, would imply a reservoir directly connected to a city
        Edge* edge = path[path.size() - 1];
        if (!edge->getRemoved()){
            Vertex* psToAdd = edge->getOrig();
            psToAdd->needing -= edge->getFlow(); /// Water that needs to be reposta
            edge->needs -= edge->getFlow();
            edge->setRemoved(true);
        }
    }
    std::cout << "AQUI\n\n\n\n\n\n\n";
    for (Vertex* v : vertexSet){
        double in = 0, out = 0;
        for (Edge* e : v->getAdj()){
            if (e->getWeight() < e->getFlow()) std::cout << "Error1\n";
            out += e->getFlow();
        }
        for (Edge* e : v->getIncoming()){
            if (e->getWeight() < e->getFlow()) std::cout << "Error2\n";
            in += e->getFlow();
        }
        if (v->getNode()->getCode().front() == 'P' and in != out){
            std::cout << "Error3 -> " << v->getNode()->getCode() << ": " << in << " -> "<< out << "\n";
        }
    }

    Vertex* reservoir = allPaths[0][0]->getOrig();

    /// Find the reverse paths from the ps to a reservoir
    for (Vertex* station : ps){
        std::cout << "a\n";
        while (true){
            Vertex* aux = findAugPathSubGraph(station, reservoir);
            if (aux == nullptr) break;

            std::cout << "b\n";
            double flow = minResAugPath1(aux, station);

            if (flow > station->needing) flow = station->needing;
            std::cout << "c\n";
            augmentFlowPath1(aux, station, flow);
            station->needing -= flow;
            station->has += flow;
        }
    }

    std::cout << "AQUI\n\n\n\n\n\n\n";
    for (Vertex* v : vertexSet){
        double in = 0, out = 0;
        for (Edge* e : v->getAdj()){
            if (e->getWeight() < e->getFlow()) std::cout << "Error1\n";
            out += e->getFlow();
        }
        for (Edge* e : v->getIncoming()){
            if (e->getWeight() < e->getFlow()) std::cout << "Error2\n";
            in += e->getFlow();
        }
        if (v->getNode()->getCode().front() == 'P' and in != out){
            std::cout << "Error3 -> " << v->getNode()->getCode() << ": " << in << " -> "<< out << "\n";
        }
    }

    std::cout << "3\n";

    for (Vertex* v : vertexSet){
        for (Edge* e : v->getAdj()) e->setRemoved(false);
    }

    for (Vertex* v : ps){
        for (Edge* e : v->getAdj()){
            if (e->needs > 0){
                double waterToSend = v->has;
                if (waterToSend > e->needs) waterToSend = e->needs;
                e->setFlow(e->getFlow() + waterToSend);
                v->has -= waterToSend;
                e->needs -= waterToSend;
            }
        }
    }

    for (Vertex* v : ps) {
        for (Edge *e: v->getAdj()) {
            std::cout << e->getOrig()->getNode()->getCode() << " " << e->getDest()->getNode()->getCode() << " -> " << e->needs << "\n";
        }
    }

    /*
    for (const std::vector<Edge*>& path : allPaths) {
        if (path.size() < 2) continue; /// Theoretical impossible, would imply a reservoir directly connected to a city
        Edge *edge = path[path.size() - 1];
        if (!edge->getRemoved()) {
            Vertex *vertex = edge->getOrig();
            double waterToSend = vertex->has;
            if (waterToSend > edge->needs) waterToSend = edge->needs;
            edge->setFlow(edge->getFlow() + waterToSend);
            vertex->has -= waterToSend;
            edge->setRemoved(true);
        }
    }
     */

    std::cout << "4\n";
    for (Vertex* v : vertexSet){
        double in = 0, out = 0;
        for (Edge* e : v->getAdj()){
            if (e->getWeight() < e->getFlow()) std::cout << "Error1\n";
            out += e->getFlow();
        }
        for (Edge* e : v->getIncoming()){
            in += e->getFlow();
        }
        if (v->getNode()->getCode().front() == 'P' and in != out) std::cout << "Error3\n";
    }

    for (Vertex* v : ps) std::cout << v->getNode()->getCode() << " -> " << v->has << "   " << v->needing << "\n";



    std::set<std::pair<std::string,double>> after = checkWaterNeeds();
    bool flag = false;
    std::cout << "\nRemoving Reservoir: " << reservoir->getNode()->getCode() << " affects the following cities:\n";
    for ( std::pair<std::string,double> pair : after) {
        std::set<std::pair<std::string,double>>::iterator it = before.end();
        for (auto iter = before.begin(); iter != before.end(); iter++) {
            if (iter->first == pair.first) {
                it = iter;
                if (iter->second < pair.second) {
                    City* city = getCity(C_CODE,pair.first,0);
                    flag = true;
                    std::cout << pair.first << ": " << city->getName() << " --> Old flow: " << city->getDemand() - iter->second   <<  "    |    New flow: " << city->getDemand() - pair.second << "\n";
                }
            }
        }
        if (it == before.end()) {
            flag = true;
            City* city = getCity(C_CODE, pair.first, 0);
            std::cout << pair.first << ": " << city->getName() << " --> Old flow: " << city->getDemand()  <<  "    |    New flow: " << city->getDemand() - pair.second << "\n";
        }
    }
    if (!flag) {
        std::cout << " -> No city is affected.\n";
    }
    std::cout << "6\n";
    std::cout << "flow: " << edmondsKarp() << "\n"; /// recalculate all values
}

void Graph::removeReservoir(Vertex *reservoir) {
    for (Vertex* v : vertexSet) v->setVisited(false);
    std::vector<Edge*> path;
    std::vector<std::vector<Edge*>> allPaths;
    findAllPaths(reservoir, path, allPaths);
    simplerAlgorithm(allPaths);
    /*
    if (incomeEdgesFull(allPaths)){
        std::cout << "Running the simpler algorithm, no need for rerun Edmonds Karp.\n";
        simplerAlgorithm(allPaths);
    }
    else{
        std::cout << "Impossible to apply the simpler algorithm. Running Edmonds Karp from scratch.\n";
        edmondsKarpRemoveReservoir(reservoir);
    }
     */
}


void Graph::edmondsKarpRemovePumpingStation(Vertex* pumpingStation) {
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

    while (findAugPath(s,t, pumpingStation)){
        double f = minResAugPath(s,t);
        augmentFlowPath(s,t,f);
    }
    removeSuperSourceSink();

}
Edge* Graph::findEdge(const std::string& orig, const std::string& dest){
    for(auto v : getVertexSet()){
        for(auto e : v->getAdj()){
            if((v->getNode()->getCode() == orig) && (e->getDest()->getNode()->getCode() == dest))
                return e;
        }
    }
    return nullptr;
}