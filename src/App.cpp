#include "../header/App.h"
#include "../header/UI.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

void App::init() {
    while (true){
        std::string cities = "Cities.csv";
        std::string reservoirs = "Reservoir.csv";
        std::string stations = "Stations.csv";
        std::string pipes = "Pipes.csv";
        std::string path;
        g = new Graph();
        displayChooseDataSet(reservoirs, stations, cities, pipes, path);
        if (!FileParse::readFiles(g, cities, pipes, reservoirs, stations, path)){
            std::cout << "Something went wrong while reading the files. Make sure the names and path are correct.\n";
            continue;
        }
        bool close = domain();
        if (close) break;
    }
}

bool App::domain() {
    g->edmondsKarp();
    while (true){
        displayDomain();
        switch (askNumber(9)) {
            case 1:
                Basicmetrics();
                break;
            case 2:
                ReliabilitySensitivity();
                break;
            case 8:
                return false;
            case 9:
                return true;
            default:
                std::cout << "Invalid number.\n";
                break;
        }
        std::cout << "\n";
    }
}
void App::Basicmetrics() {
    while (true){
        displayBasicMetrics();
        switch (askNumber(9)) {
            case 1:
                allOrSpecific();
                break;
            case 2:
                checkWaterDeficit();
                break;
            case 3:
                balanceLoad();
                break;
            case 9:
                return;
            default:
                std::cout << "Invalid number.\n";
                break;
        }
        std::cout << "\n";
    }
}

void App::balanceLoad() {
    std::cout << "Initial metrics of the network: ";
    metrics prev = g->calculateMetrics();
    displayMetrics(prev);
    while(true){
        g->balanceLoad();
        metrics curr = g->calculateMetrics();

        if (curr.avg < prev.avg or curr.maxDiff < prev.maxDiff or curr.variance < prev.variance) prev = curr;
        else break;
    }
    std::cout << "Final metrics of the network: ";
    displayMetrics(prev);
}

void App::allOrSpecific(){
    while (true){
        displayAllOrSpecific();
        switch (askNumber(9)) {
            case 1:
                allCitiesWaterQuantity();
                break;
            case 2:
                SpecificCityWaterQuantity();
                break;
            case 9:
                return;
            default:
                std::cout << "Invalid number.\n";
                break;
        }
        std::cout << "\n";
    }
}
void App::allCitiesWaterQuantity(){
    std::string s = "city listing";
    std::string file = getNewFileName(s);
    std::string path = getNewPath();
    if (!path.empty() and path.back() != '/') path += "/";
    std::string filePath = path + file;
    std::ofstream os(filePath, std::ios::trunc);
    os << "Max Flow: " << g->edmondsKarp() << "\n";
    for(Vertex* v : g->getVertexSet()){
        std::string code = v->getNode()->getCode();
        City* city = g->getCity(C_CODE, code ,0);
        if (city == nullptr) continue;
        os <<  "("  << city->getCode() << ", " << v->cityAmountOfWater() << ")\n";
    }
    os.close();
}
void App::SpecificCityWaterQuantity(){
    std::pair<int,std::string> p = askCityCodeNameId();
    uint32_t id;
    if (p.first == 1) {
        try{
            id = (uint32_t )std::stoul(p.second);
        }
        catch (...){
            std::cout << "Invalid id.\n";
            return;
        }
    }
    City* city;
    switch (p.first) {
        case 1:
            city = g->getCity(C_ID,p.second,id);
            break;
        case 2:
            city = g->getCity(C_CODE,p.second,0);
            break;
        case 3:
            city = g->getCity(C_NAME,p.second,0);
            break;
    }
    if(city == nullptr){
        std::cout << "Invalid input.\n";
        return;
    }
    std::cout << "Max Flow: " << g->edmondsKarp() << "\n";
    std::string code = city->getCode();
    Vertex* v = g->findVertex(code);
    printCity(city,v->cityAmountOfWater());
}

void App::ReliabilitySensitivity() {
    while (true){
        displayReliabilitySensitivity();
        switch (askNumber(9)){
            case 1:
                removeReservoir();
                g->edmondsKarp();
                break;
            case 2: {
                std::string code = pumpingStationsRemoved();
                removePumpingStation(code);
                g->edmondsKarp();
                break;
            }
            case 3 : {
                std::vector<std::pair<std::string, std::string>> pipelines;
                askPipelines(pipelines);
                removePipelines(pipelines);
                g->edmondsKarp();
                break;
            }
            case 9:
                return;
            default:
                std::cout << "Invalid number.\n";
                break;
        }
        std::cout << "\n";
    }
}

void App::removeReservoir() {
    while (true){
        std::pair<uint32_t, std::string> pair = askReservoirCodeNameID();
        Reservoir* reservoir;
        uint32_t id;
        if (pair.first == 1){
            try{
                id = (uint32_t) std::stoul(pair.second);
            }
            catch (...){
                std::cout << "Invalid id.\n";
                return;
            }
        }
        switch(pair.first){
            case 1:
                reservoir = g->getReservoir(R_ID, pair.second, id);
                break;
            case 2:
                reservoir = g->getReservoir(R_CODE, pair.second, 0);
                break;
            case 3:
                reservoir = g->getReservoir(R_NAME, pair.second, 0);
                break;
        }
        if(reservoir == nullptr){
            std::cout << "Invalid input.\n";
            continue;
        }
        std::string code = reservoir->getCode();
        Vertex* removed = g->findVertex(code);

        g->removeReservoir(removed);

        std::cout << "Want to remove another reservoir? ";
        bool answer = getYesNoAnswer();
        g->edmondsKarp();
        std::cout << "\n";
        if (!answer) break;
    }
}

void App::checkWaterDeficit() {
    std::set<std::pair<std::string,double>> result = g->checkWaterNeeds();
    for (std::pair<std::string,double> city : result) {
        std::cout << "(" << city.first << ", " << city.second << ")" << "\n";
    }
}

void App::askPipelines(std::vector<std::pair<std::string,std::string>> &pipelines){
    while(true){
        pipelinesRemoved(pipelines);
        std::cout << "Do you want to remove another pipeline: \n";
        bool answer = getYesNoAnswer();
        if (!answer) return;
    }

}

void App::removePipelines(std::vector<std::pair<std::string,std::string>> &pipelines)  {
    std::vector<Edge*> edges;
    std::set<std::pair<std::string,double>> before = g->checkWaterNeeds();
    for(auto const p : pipelines){
        Edge *edge = g->findEdge(p.first, p.second);
        if(edge == nullptr){
            std::cout << "Invalid input. \n";
            return;
        }
        edges.push_back(edge);
    }


    g->edmondsKarpRemovePipeline(edges);
    std::cout << std::left << std::setw(25) << " " << std::setw(12) << "Old Flow" << std::setw(12) << "New Flow" << std::setw(12) << "Diff" << "\n";
    std::set<std::pair<std::string,double>> after = g->checkWaterNeeds();
    std::set<std::pair<std::string,double>> affected;
    for(const std::pair<std::string ,double>  &pair : after){
        auto it = before.end();
        for (auto itr = before.begin(); itr != before.end(); itr++){
            if (itr->first == pair.first){
                it = itr;
                break;
            }
        }
        if((it != before.end()) and (pair.second <= it->second)) continue;

        affected.insert(std::make_pair(pair.first, pair.second));
    }
    for(auto p: affected){
        City *city = g->getCity(C_CODE, p.first, 0);
        double f = 0;
        for(const auto& old : before){
            if(old.first == p.first)
                f = old.second;
        }
        std::string name = p.first + ": " + city->getName();
        double old = city->getDemand() - f;
        double newFlow = city->getDemand() - p.second;
        std::cout << std::left << std::setw(25) << name
                  << std::setw(12) << old
                  << std::setw(12) << newFlow
                  << std::setw(12) << old - newFlow << "\n";
    }
}

void App::removePumpingStation(std::string &code) {
    std::set<std::pair<std::string,double>> before = g->checkWaterNeeds();
    Vertex* vertex;
    bool invalid = true;
    for(auto v : g->getVertexSet()){
        if(v->getNode()->getCode() == code){
            vertex = v;
            invalid = false;
        }
    }
    if(invalid){
        std::cout << "Invalid input.\n";
        return;
    }
    g->edmondsKarpRemovePumpingStation(vertex);
    std::set<std::pair<std::string,double>> after = g->checkWaterNeeds();
    bool flag = false;
    std::cout << "\nRemoving Pumping Station: " << vertex->getNode()->getCode() << " affects the following cities:\n";
    std::cout << std::left << std::setw(25) << " " << std::setw(12) << "Old Flow" << std::setw(12) << "New Flow" << std::setw(12) << "Diff" << "\n";
    for ( std::pair<std::string,double> pair : after) {
        std::set<std::pair<std::string,double>>::iterator it = before.end();
        for (auto iter = before.begin(); iter != before.end(); iter++) {
            if (iter->first == pair.first) {
                it = iter;
                if (iter->second < pair.second) {
                    City* city = g->getCity(C_CODE,pair.first,0);
                    flag = true;
                    std::string name = pair.first + ": " + city->getName();
                    double old = city->getDemand() - it->second;
                    double newFlow = city->getDemand() - pair.second;
                    std::cout << std::left << std::setw(25) << name
                              << std::setw(12) << old
                              << std::setw(12) << newFlow
                              << std::setw(12) << old - newFlow << "\n";
                }
            }
        }
        if (it == before.end()) {
            flag = true;
            City* city = g->getCity(C_CODE,pair.first,0);
            std::string name = pair.first + ": " + city->getName();
            double old = city->getDemand();
            double newFlow = city->getDemand() - pair.second;
            std::cout << std::left << std::setw(25) << name
                      << std::setw(12) << old
                      << std::setw(12) << newFlow
                      << std::setw(12) << old - newFlow << "\n";
        }
    }
    if (!flag) {
        std::cout << "No city is affected.\n";
    }
}