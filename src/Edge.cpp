#include "../header/Edge.h"

Edge::Edge(Vertex *orig, Vertex *dest, double weight) : orig(orig), dest(dest), weight(weight) {}

double Edge::getWeight() const {
    return weight;
}

double Edge::getFlow() const {
    return flow;
}

Vertex* Edge::getDest() const {
    return dest;
}
Vertex *Edge::getOrig() const {
    return orig;
}

void Edge::setFlow(uint32_t f) {
    flow = f;
}