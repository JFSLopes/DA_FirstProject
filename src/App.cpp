#include "../header/App.h"
#include "../header/UI.h"

#include <iostream>

void App::init() {
    std::string cities = "Cities.csv";
    std::string reservoirs = "Reservoir.csv";
    std::string stations = "Stations.csv";
    std::string pipes = "Pipes.csv";
    std::string path;

    displayChooseDataSet(reservoirs, stations, cities, pipes, path);

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
