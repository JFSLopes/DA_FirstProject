#include "../header/App.h"
#include "../header/UI.h"

#include <iostream>

void App::init() {
    std::string cities = "Cities.csv";
    std::string reservoirs = "Reservoir.csv";
    std::string stations = "Stations.csv";
    std::string pipes = "Pipes.csv";
    std::string path = "../Dataset/LargeDataSet/";

    displayChooseDataSet(reservoirs, stations, cities, pipes, path);
    Graph g;
    FileParse::readFiles(g, cities, pipes, reservoirs, stations, path);
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
