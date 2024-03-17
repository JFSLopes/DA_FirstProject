#include "../header/FileParse.h"
#include <iostream>
#include <sstream>

bool FileParse::readFiles(Graph& g, std::string &cities, std::string &pipes, std::string &reservoirs, std::string &stations,
                          std::string &path) {
    if (!path.empty()){
        cities = path + cities;
        pipes = path + pipes;
        reservoirs = path + reservoirs;
        stations = path + stations;
    }

    std::ifstream fileReservoirs(reservoirs);
    if (!fileReservoirs.is_open()){
        std::cout << "Trying to open the reservoirs file failed.\n";
        return false;
    }
    std::ifstream fileStations(stations);
    if (!fileStations.is_open()){
        std::cout << "Trying to open the stations file failed.\n";
        return false;
    }
    std::ifstream fileCities(cities);
    if (!fileCities.is_open()){
        std::cout << "Trying to open the cities file failed.\n";
        return false;
    }
    std::ifstream filePipes(pipes);
    if (!filePipes.is_open()){
        std::cout << "Trying to open the pipes file failed.\n";
        return false;
    }

    std::cout << "Reading reservoirs ...\n";
    readReservoirs(g, fileReservoirs);
    std::cout << "Reading stations ...\n";
    readStations(g, fileStations);
    std::cout << "Reading cities ...\n";
    readCities(g, fileCities);
    std::cout << "Reading pipes ...\n";
    readPipes(g, filePipes);
    return true;
}

void FileParse::readCities(Graph& g, std::ifstream &in) {
    ///skip header
    std::string line;
    std::getline(in, line);
    while (std::getline(in, line)){
        std::string name, ID, code, demand, population;
        std::istringstream iss(line);
        std::getline(iss, name, ',');
        std::getline(iss, ID, ',');
        std::getline(iss, code, ',');
        std::getline(iss, demand, ',');
        std::getline(iss, population);

        /// population comes with commas, so can be converted using a string to int
        uint32_t numPopulation = 0;
        for (char ch : population){
            if (ch >= '0' and ch <= '9'){
                numPopulation = numPopulation * 10 + (ch - '0');
            }
        }
        uint32_t numDemand = (uint32_t) std::stoul(demand);
        uint32_t id = (uint32_t) std::stoul(ID);
        Node* city = new City(id, numDemand, numPopulation, code, name);
        Vertex* vertex = new Vertex(city);
        g.addVertex(vertex);
    }
    in.close();
}

void FileParse::readStations(Graph &g, std::ifstream &in) {
    ///skip header
    std::string line;
    std::getline(in, line);
    while (std::getline(in, line)){
        std::string ID, code;
        std::istringstream iss(line);

        std::getline(iss, ID, ',');
        std::getline(iss, code);

        uint32_t id = (uint32_t) std::stoul(ID);
        Node* station = new Station(id, code);
        Vertex* vertex = new Vertex(station);
        g.addVertex(vertex);
    }
    in.close();
}

void FileParse::readReservoirs(Graph &g, std::ifstream &in) {
    ///skip header
    std::string line;
    std::getline(in, line);
    while (std::getline(in, line)){
        std::string name, municipality, ID, code;
        std::istringstream iss(line);

        std::getline(iss, name, ',');
        std::getline(iss, municipality, ',');
        std::getline(iss, ID, ',');
        std::getline(iss, code, ',');
        uint32_t maxDelivery;
        iss >> maxDelivery;

        uint32_t id = (uint32_t) std::stoul(ID);
        Node* reservoir = new Reservoir(name, municipality, code, id, maxDelivery);
        Vertex* vertex = new Vertex(reservoir);
        g.addVertex(vertex);
    }
    in.close();
}

void FileParse::readPipes(Graph &g, std::ifstream &in) {}