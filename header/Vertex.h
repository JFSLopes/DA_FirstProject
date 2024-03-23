#ifndef DA_FIRSTPROJECT_VERTEX_H
#define DA_FIRSTPROJECT_VERTEX_H

class Edge;

#include <vector>
#include "Edge.h"
#include "Node.h"

class Vertex{
private:
    Node* node;
    std::vector<Edge*> adj;
    std::vector<Edge*> incoming;
    bool visited;
    Edge* path;
public:
    Vertex(Node* node);

    Node* getNode() const;
    std::vector<Edge*> getAdj() const;
    std::vector<Edge*> getIncoming() const;
    Edge* getPath() const;
    Edge* edgeMoreFull() const;

    bool isVisited() const;
    void setVisited(bool visited);
    void setPath(Edge *path);

    void addEdge(Vertex* d, double w);
    double remainReservoirDelivery() const;
    double cityAmountOfWater() const;

    void removeEdges();
    void removeEdge(Vertex* target);

    bool operator<(const Vertex other) const;
};

#endif
