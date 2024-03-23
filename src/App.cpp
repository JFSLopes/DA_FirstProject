#include "../header/App.h"
#include "../header/UI.h"

#include <iostream>
#include <fstream>

void App::init() {
    std::string cities = "Cities.csv";
    std::string reservoirs = "Reservoir.csv";
    std::string stations = "Stations.csv";
    std::string pipes = "Pipes.csv";
    std::string path = "../Dataset/LargeDataSet/";
    g = new Graph();
    displayChooseDataSet(reservoirs, stations, cities, pipes, path);
    FileParse::readFiles(g, cities, pipes, reservoirs, stations, path);
    g->edmondsKarp();
    domain();



    /*
    std::vector<Vertex*> a = g.getVertexSet();
    std::cout << "Max flow: " << g.edmondsKarp() << "\n";

    metrics prev = g.calculateMetrics();
    while(true){
        g.balanceLoad();
        metrics curr = g.calculateMetrics();
        if (curr.avg < prev.avg or curr.maxDiff < prev.maxDiff or curr.variance < prev.variance){
            prev = curr;
        }
        else break;
    }

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
                break;
            case 9:
                return;
            default:
                std::cout << "Invalid number. Enter a new one: ";
        }
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
                break;
            case 9:
                return;
            default:
                std::cout << "Invalid number. Enter a new one: ";
        }
    }
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
                std::cout << "Invalid number. Enter a new one: ";
        }
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
    try{
        id = (uint32_t )std::stoul(p.second);
    }
    catch (...){
        std::cout << "Invalid id.\n";
        return;
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


