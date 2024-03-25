#include "../header/App.h"
#include "../header/UI.h"

#include <iostream>
#include <fstream>

void App::init() {
    std::string cities = "Cities_Madeira.csv";
    std::string reservoirs = "Reservoirs_Madeira.csv";
    std::string stations = "Stations_Madeira.csv";
    std::string pipes = "Pipes_Madeira.csv";
    std::string path = "../Dataset/DataSetSmall/";
    g = new Graph();
    displayChooseDataSet(reservoirs, stations, cities, pipes, path);
    FileParse::readFiles(g, cities, pipes, reservoirs, stations, path);
    g->edmondsKarp();
    domain();



    /*
    for (Vertex* v : a){
        if (v->getNode()->getCode().front() == 'C'){
            City* city = dynamic_cast<City*>(v->getNode());
            std::cout << city->getName() << "   " << city->getPopulation() << "   " << city->getDemand() << "\n";
        }
        if (v->getNode()->getCode().front() == 'P'){
            Station* city = dynamic_cast<Station*>(v->getNode());
            std::cout << city->getCode() << "\n";
        }
        if (v->getNode()->getCode().front() == 'R'){
            Reservoir* city = dynamic_cast<Reservoir*>(v->getNode());
            std::cout << city->getName() << "   " << city->getMunicipality() << "   " << city->getMaxDelivery() << "\n";
        }
    }

    std::cout << "\n";
    for (Vertex* v : g.getVertexSet()){
        if (v->getNode()->getCode().front() == 'C'){
            City* city = dynamic_cast<City*>(v->getNode());
            std::cout << city->getName() << " ";
            double count = 0;
            for (Edge* e : v->getIncoming()){
                if (v->getNode()->getCode().front() == 'C') count += e->getFlow();
            }
            std::cout << count << "\n";
        }
    }


    for (Vertex* v : g.getVertexSet()){
        double income = 0, leaving = 0;
        for (Edge* e : v->getAdj()){
            leaving += e->getFlow();
        }
        for (Edge* e : v->getIncoming()){
            income += e->getFlow();
        }
        if (income != leaving and v->getNode()->getCode().front() == 'R' and v->getNode()->getCode().front() == 'C'){
            std::cout << "Erro\n";
            break;
        }
    }
     */
}

void App::domain() {
    while (true){
        displayDomain();
        switch (askNumber(9)) {
            case 1:
                Basicmetrics();
                break;
            case 2:
                ReliabilitySensitivity();
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
        if (curr.avg < prev.avg or curr.maxDiff < prev.maxDiff or curr.variance < prev.variance){
            prev = curr;
        }
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
void::App::allCitiesWaterQuantity(){
    std::string s = "city listing";
    std::string file = getNewFileName(s);
    std::string path = getNewPath();
    if (!path.empty() and path.back() != '/') path += "/";
    std::string filePath = path + file;
    std::ofstream os(filePath,std::ios::trunc);
    for(Vertex* v : g->getVertexSet()){
        std::string code = v->getNode()->getCode();
        City* city = g->getCity(C_CODE, code ,0);
        if (city == nullptr) continue;
        os <<  "("  << city->getCode() << ", " << v->cityAmountOfWater() << ")\n";
    }
    os.close();
}
void::App::SpecificCityWaterQuantity(){
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
    std::string code = city->getCode();
    Vertex* v = g->findVertex(code);
    printCity(city,v->cityAmountOfWater());
}

void App::ReliabilitySensitivity() {
    while (true){
        displayReliabilitySensitivity();
        switch (askNumber(3)){
            case 1:
                removeReservoir();
                break;
            case 2:
                break;
            case 3:
                removePipelines();
                break;
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





        std::cout << "Want to remove another reservoir? ";
        bool answer = getYesNoAnswer();
        std::cout << "\n";
        if (!answer) break;
    }
}


void App::checkWaterDeficit() {
    std::set<std::pair<std::string,double>> result = g->checkWaterNeeds();
    for (std::pair<std::string,double> city : result) {
        std::cout << "(" << city.first << "," << " " << city.second << ")" << "\n";
    }
}

void App::removePipelines() {
    std::unordered_map<std::string , std::set<std::pair<Edge*,double>>> map;
    std::set<std::pair<std::string,double>> before = g->checkWaterNeeds();
    for (Vertex* v : g->getVertexSet()){
        for(Edge* edge : v->getAdj()){
            g->edmondsKarpRemovePipeline(edge);
            std::set<std::pair<std::string,double>> after = g->checkWaterNeeds();
            for(const std::pair<std::string ,double>  &pair : after){
                auto itr = before.find(pair);
                if(itr != before.end() and (pair.second <= itr->second)) continue;
                auto itr1 = map.find(pair.first);
                if(itr1 == map.end()){
                    map.insert(std::make_pair(pair.first,std::set<std::pair<Edge*,double>>()));
                    map[pair.first].insert(std::make_pair(edge,pair.second));
                }
                else{
                    itr1->second.insert(std::make_pair(edge,pair.second));
                }
            }
        }
    }
    printMap(map);
}

