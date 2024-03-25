#ifndef DA_FIRSTPROJECT_EDGE_H
#define DA_FIRSTPROJECT_EDGE_H

class Vertex;

#include "Vertex.h"

class Edge{
private:
    Vertex* dest;
    Vertex* orig;
    double weight;
    double flow;
    bool removed;
public:
    Edge(Vertex* orig, Vertex* dest, double weight);

    Vertex* getDest() const;
    Vertex* getOrig() const;
    double getWeight() const;
    double getFlow() const;
    bool getRemoved() const;

    void setFlow(double f);
    void setRemoved(bool r);
};

#endif
