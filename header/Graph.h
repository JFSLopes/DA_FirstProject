#ifndef DA_FIRSTPROJECT_GRAPH_H
#define DA_FIRSTPROJECT_GRAPH_H

class Vertex;

#include <unordered_map>
#include "FileParse.h"
#include "Vertex.h"
#include "Reservoir.h"
#include "City.h"
#include "Station.h"

class Graph{
private:
    std::vector<Vertex*> vertexSet;

public:
    City* getCity(cityEnum type, std::string& str, uint32_t id) const;
    Station* getStation(stationEnum type, std::string& str, uint32_t id) const;
    Reservoir* getReservoir(reservoirEnum type, std::string& str, uint32_t id) const;
    const std::vector<Vertex*> getVertexSet() const;
    Vertex* findVertex(std::string& code) const;

    bool addVertex(Vertex* node);

    bool findAugPath(Vertex* source, Vertex* sink);
    double minResAugPath(Vertex* source, Vertex* sink);
    void augmentFlowPath(Vertex* source, Vertex* sink, double f);
    void createSuperSourceSink();
    double edmondsKarp();
};

#endif
