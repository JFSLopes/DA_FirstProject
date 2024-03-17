#include "../header/App.h"

#include <iostream>

void App::init() {
    std::string cities = "../Dataset/DataSetSmall/Cities_Madeira.csv";
    std::string reservoirs = "../Dataset/DataSetSmall/Reservoirs_Madeira.csv";
    std::string stations = "../Dataset/DataSetSmall/Stations_Madeira.csv";
    std::string pipes = "../Dataset/DataSetSmall/Pipes_Madeira.csv";
    std::string path;

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
}
