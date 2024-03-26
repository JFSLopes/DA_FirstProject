#ifndef DA_FIRSTPROJECT_GRAPH_H
#define DA_FIRSTPROJECT_GRAPH_H

class Vertex;

#include <queue>
#include <set>
#include "FileParse.h"
#include "Vertex.h"
#include "Reservoir.h"
#include "City.h"
#include "Station.h"

struct metrics {
    double avg;
    double variance;
    double maxDiff;
};

class Graph{
private:
    std::vector<Vertex*> vertexSet;

    void createSuperSourceSink(Vertex* removedReservoir = nullptr);
    void removeSuperSourceSink();
    void orderCitiesByCumulative(std::priority_queue<Vertex>& q) const;
    void findAllPaths(Vertex* s, Vertex* d, std::vector<Edge *>& path, std::vector<std::vector<Edge *>>& paths) const;

    /**
     * Return the minimal Capacity - flow difference on the path. It will be used to balance the load across the network
     * @param path
     * @return
     */
    double minimalDiffCapacityFlow(std::vector<Edge*>& path) const;
    void incrementFlow(std::vector<Edge*>& path, double flow);
    void simplerAlgorithm(std::vector<std::vector<Edge*>>& allPaths);

    void DFSVisit(Vertex* v, std::vector<Vertex*>& subGraph);
    void DFSVisitReverse(Vertex* v, std::vector<Vertex*>& subGraph);

public:
    bool incomeEdgesFull(std::vector<std::vector<Edge*>>& allPaths) const;
    void findAllPaths(Vertex *s, std::vector<Edge *> &path, std::vector<std::vector<Edge *>> &paths) const;
    City* getCity(cityEnum type, std::string& str, uint32_t id) const;
    Station* getStation(stationEnum type, std::string& str, uint32_t id) const;
    Reservoir* getReservoir(reservoirEnum type, std::string& str, uint32_t id) const;
    const std::vector<Vertex*> getVertexSet() const;
    Vertex* findVertex(std::string& code) const;

    bool addVertex(Vertex* node);
    void removeVertex(Vertex* v);

    bool findAugPath(Vertex* source, Vertex* sink, Vertex* removed = nullptr);
    bool findAugPathSubGraph(Vertex* source, Vertex* sink, std::vector<Vertex*>& subGraph);
    double minResAugPath(Vertex* source, Vertex* sink);
    void augmentFlowPath(Vertex* source, Vertex* sink, double f);
    double edmondsKarp();
    double edmondsKarpRemovePipeline(Edge* edge);
    void edmondsKarpRemoveReservoir(Vertex* reservoir);
    metrics calculateMetrics() const;
    std::set<std::pair<std::string, double>> checkWaterNeeds();

    void balanceLoad();

    void removeReservoir(Vertex* reservoir);
};

#endif
