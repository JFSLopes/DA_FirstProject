#ifndef DA_FIRSTPROJECT_FILEPARSE_H
#define DA_FIRSTPROJECT_FILEPARSE_H

class Graph;
class City;

#include "Graph.h"

#include <fstream>

namespace FileParse{
    bool readFiles(Graph* g, std::string& cities, std::string& pipes, std::string& reservoirs, std::string& stations, std::string& path);
    void readCities(Graph* g, std::ifstream& in);
    void readPipes(Graph* g, std::ifstream& in);
    void readReservoirs(Graph* g, std::ifstream& in);
    void readStations(Graph* g, std::ifstream& in);
}

#endif
