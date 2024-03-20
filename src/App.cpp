#include "../header/App.h"

#include <iostream>

void App::init() {

    std::string cities = "Cities_Madeira.csv";
    std::string reservoirs = "Reservoirs_Madeira.csv";
    std::string stations = "Stations_Madeira.csv";
    std::string pipes = "Pipes_Madeira.csv";
    std::string path = "../Dataset/DataSetSmall/";

    Graph g;
    FileParse::readFiles(g, cities, pipes, reservoirs, stations, path);

    std::vector<Vertex*> a = g.getVertexSet();

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
    int count = 0;
    for (Vertex* v : g.getVertexSet()){
        for (Edge* e : v->getAdj()){
            count++;
            std::cout << e->getOrig()->getNode()->getCode() << " -> " << e->getDest()->getNode()->getCode() << "\n";
        }
    }
    std::cout << count << "\n";
}
