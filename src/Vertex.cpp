#include "../header/Vertex.h"

Vertex::Vertex(Node* node) : node(node), path(nullptr) {}

Node* Vertex::getNode() const {
    return node;
}

std::vector<Edge *> Vertex::getAdj() const {
    return adj;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return incoming;
}

void Vertex::addEdge(Vertex* d, double w) {
    Edge* edge = new Edge(this, d, w);
    adj.push_back(edge);
    d->incoming.push_back(edge);
}